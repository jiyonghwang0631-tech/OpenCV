#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    const String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";
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

    vector<Vec2f> lines;
    Point pt1, pt2;
    float rho, theta, sin_t, cos_t, y0, x0, alpha;

    while (true)
    {
        cap >> frame;
        Canny(frame, edge, low_th, high_th);
        HoughLines(edge, lines, 1, CV_PI / 180, h_thresh);
        for (size_t i = 0; i < lines.size(); ++i)
        {
            rho = lines[i][0];
            theta = lines[i][1];
            cos_t = cos(theta);
            sin_t = sin(theta);
            x0 = rho * cos_t;
            y0 = rho * sin_t;
            alpha = 1000;
            pt1.x = cvRound(x0 - alpha * sin_t);
            pt1.y = cvRound(y0 + alpha * cos_t);
            pt2.x = cvRound(x0 + alpha * sin_t);
            pt2.y = cvRound(y0 - alpha * cos_t);
            line(frame, pt1, pt2, Color::Red, 2, LINE_AA);
        }
        if (waitKey(30) == 27)
            break;
        imshow("frame_ori", frame);
        imshow("frame", edge);
    }
    cap.release();
    destroyAllWindows();
    return 0;
}