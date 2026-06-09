#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2026/opencv_ex/data/";

int main()
{
    Mat img(400, 600, CV_8UC3, Color::White);

    int a = 0, b = 0, c = 0;
    while (true)
    {
        Mat img2 = img.clone();
        line(img2, Point(50, 50), Point(200 + a, 100 + b), Color::Blue, 3);
        imshow("img", img2);
        if(waitKey(1000/30) == 27)
            break;
        a += 1;
        b += 2;
    }
    destroyAllWindows();
    return 0;
}