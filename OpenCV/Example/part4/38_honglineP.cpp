#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    const String folderPath = "/home/aa/kuBig2026/opencv_ex/data/";
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

    Mat frame, edge;
    int low_th, high_th, h_thresh;
    namedWindow("frame");
    createTrackbar("lowthreshould", "frame", &low_th, 255);
    createTrackbar("highthreshould", "frame", &high_th, 255);
    createTrackbar("hough_thresh", "frame", &h_thresh, 255);

    vector<Vec4f> lines;

    while (true)
    {
        cap >> frame;
        Canny(frame, edge, low_th, high_th);
        HoughLinesP(edge, lines, 1, CV_PI / 180, h_thresh, 10, 20);
        for (size_t i = 0; i < lines.size(); i++)
            line(frame, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Color::Red, 2, LINE_AA);
        if (waitKey(30) == 27)
            break;
        imshow("frame_ori", frame);
        imshow("frame", edge);
    }
    cap.release();
    destroyAllWindows();
    return 0;
}