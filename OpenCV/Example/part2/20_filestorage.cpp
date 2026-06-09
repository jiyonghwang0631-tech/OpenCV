#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    const String folderPath =  "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";
    String name = "Hwang Ji Yong";
    int age = 18;
    Point pt1(100, 200);
    vector<float> scores = {3.14, 6.66, 9.14};
    Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

    FileStorage fs;
    fs.open(folderPath + "mydata.xml", FileStorage::WRITE);
    fs << "name" << name;
    fs << "age" << age;
    fs << "point" << pt1;
    fs << "scores" << scores;
    fs << "data" << mat1;

    fs.release();

    return 0;
}