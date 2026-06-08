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
    }
    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);
        
    Mat frame;
    for (int i = 0; i < 1000; ++i)
    {
        cap >> frame;
        if(waitKey(30) == 27)
            break;
        imshow("frame", frame);
    }

    cap.release();
    destroyAllWindows();
    return 0;

}
