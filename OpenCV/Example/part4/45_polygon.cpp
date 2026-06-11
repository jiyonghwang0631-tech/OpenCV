#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
const String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";
void setLabel(Mat &img, const vector<Point> &pts, const String &label)
{
    Rect rc = boundingRect(pts);
    RotatedRect rc2 = minAreaRect(pts);
    Point2f center;
    float radius;
    minEnclosingCircle(pts, center, radius);
    rectangle(img, rc, Scalar(0, 0, 255), 1);
    // draw rc2 in img
    Point2f vertices[4];
    rc2.points(vertices);
    for (int i = 0; i < 4; i++)
        line(img, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 3);
    // draw circle in img
    circle(img, center, cvRound(radius), Scalar(255, 0, 0), 2);
    putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
}

int main(int argc, char *argv[])
{
    Mat img = imread(folderPath + "polygon.bmp", IMREAD_COLOR);

    if (img.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    for (vector<Point> pts : contours)
    {
        if (contourArea(pts) < 400)
            continue;

        vector<Point> approx;
        approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

        int vtc = (int)approx.size();

        if (vtc == 3)
        {
            setLabel(img, pts, "TRI");
        }
        else if (vtc == 4)
        {
            setLabel(img, pts, "RECT");
        }
        else
        {
            double len = arcLength(pts, true);
            double area = contourArea(pts);
            double ratio = 4. * CV_PI * area / (len * len);

            if (ratio > 0.85)
            {
                setLabel(img, pts, "CIR");
            }
        }
    }

    imshow("img", img);

    waitKey();
    return 0;
}