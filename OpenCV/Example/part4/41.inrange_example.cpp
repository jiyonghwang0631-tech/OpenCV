#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0, CAP_V4L2);
    if (!cap.isOpened())
    {
        cerr << "카메라를 열 수 없습니다." << endl;
        return -1;
    }

    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);

    const Scalar lowerYellow(20, 100, 100);
    const Scalar upperYellow(35, 255, 255);
    int minimumArea = 1000;

    namedWindow("frame");
    namedWindow("mask");

    createTrackbar("minimum area", "mask", nullptr, 50000);

    setTrackbarPos("minimum area", "mask", minimumArea);

    Mat frame, hsv, mask;
    const Mat kernel =
        getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

    while (true)
    {
        if (!cap.read(frame) || frame.empty())
        {
            cerr << "카메라 프레임을 읽을 수 없습니다." << endl;
            break;
        }

        minimumArea = getTrackbarPos("minimum area", "mask");

        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, lowerYellow, upperYellow, mask);

        morphologyEx(mask, mask, MORPH_OPEN, kernel);
        morphologyEx(mask, mask, MORPH_CLOSE, kernel);

        vector<vector<Point>> contours;
        findContours(mask.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        double largestArea = 0.0;
        Rect objectBox;

        for (const vector<Point> &contour : contours)
        {
            double area = contourArea(contour);
            if (area > largestArea)
            {
                largestArea = area;
                objectBox = boundingRect(contour);
            }
        }

        if (largestArea >= minimumArea)
        {
            rectangle(frame, objectBox, Scalar(0, 0, 255), 2);
            putText(
                frame,
                "yellow area: " + to_string(static_cast<int>(largestArea)),
                Point(objectBox.x, max(20, objectBox.y - 10)),
                FONT_HERSHEY_SIMPLEX,
                0.6,
                Scalar(0, 0, 255),
                2);
        }

        imshow("frame", frame);
        imshow("mask", mask);

        int key = waitKey(30);
        if (key == 27 || key == 'q')
            break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
