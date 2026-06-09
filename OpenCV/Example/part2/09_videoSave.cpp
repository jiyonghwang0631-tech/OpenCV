#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2026/opencv_ex/data/";

int main()
{
    VideoCapture cap(0, CAP_V4L2);

    if (!cap.isOpened())
    {
        cerr << "카메라를 열수 없습니다." << endl;
    }

    // MJPG
    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);

    // 출력 설정
    int w = 640;
    int h = 480;
    double fps = 30.0;
    int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');

    VideoWriter outVideo(folderPath + "flip_roi_inverse.avi", fourcc, fps, Size(w, h));


    Mat frame;
    int x = (540 - 200) / 2;
    int y = (480 - 200) / 2;
    int move_x = 0;
    for (int i = 0; i < 1000; ++i)
    {
        cap >> frame;
        flip(frame, frame, 1);
        Mat roi = frame(Rect(move_x, y, 200, 200));
        roi = ~roi;
        rectangle(frame, Rect(move_x, y, 200, 200), Color::Red, 2);
        if (waitKey(30) == 27)
            break;
        outVideo << frame;
        imshow("frame", frame);
        move_x += 1;
        if (move_x > 340){
            move_x = 0;
        }
    }
    cap.release();
    outVideo.release();
    destroyAllWindows();
    return 0;
}