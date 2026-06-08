#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

int main()
{
    cout << "hello, world" << endl;
    Mat img = imread(folderPath + "images.jpg");
    //Mat img = Mat::zeros(480, 640, CV_8UC3);
    Size size(640, 480);
    resize(img, img, size);
    imshow("lenna", img);
    waitKey();

    return 0;
}