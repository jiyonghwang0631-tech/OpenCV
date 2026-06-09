#include <iostream>
#include <opencv2/opencv.hpp>
#include "colors.hpp"

using namespace std;
using namespace cv;

String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";


int main()
{
    VideoCapture cap(0, CAP_V4L2);
    
    if (!cap.isOpened())
    {
        cerr << "카메라를 열수 없습니다." << endl;
        return -1;
    }
    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);
        

    int w = 540;
    int h = 480;
    double fps = 30.0;
    int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');

    VideoWriter outvideo(folderPath + "flip_roi_inverse.avi", fourcc, fps, Size(w, h));
    if (!outvideo.isOpened())
    {
        cerr << "동영상 저장 파일을 열 수 없습니다." << endl;
        return -1;
    }


    Mat frame;
    namedWindow("frame", WINDOW_AUTOSIZE);
    int x = (520 - 200) / 2;
    int y = (480 - 200) / 2;
    int move_x = 0;
    for (int i = 0; i < 1000; ++i)
    {
        cap >> frame;
        if (frame.empty())
        {
            cerr << "프레임을 읽을 수 없습니다." << endl;
            break;
        }

        flip(frame, frame, 1);
        Mat roi = frame(Rect(x, y, 200, 200));
        roi = ~roi;
        rectangle(frame, Rect(x, y, 200, 200), Color::Red, 2);
        imshow("frame", frame);
        outvideo.write(frame(Rect(0, 0, w, h)));

        int key = waitKey(30);
        if (key == 27 || key == 'q' || getWindowProperty("frame", WND_PROP_VISIBLE) < 1)
            break;

        move_x += 1;
        if (move_x >340)
        {
            move_x = 0;
        }
    }

    cap.release();
    outvideo.release();
    destroyAllWindows();
    return 0;

}
