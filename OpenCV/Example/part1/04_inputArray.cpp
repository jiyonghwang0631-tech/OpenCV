#include <iostream>
#include <opencv2/opencv.hpp>
#include "colors.hpp"

using namespace std;
using namespace cv;

String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

void printMat(InputArray _mat, OutputArray _output);

int main()
{
    Mat img = Mat(10, 20, CV_8UC1, Scalar(125));

    Mat mat2;
    printMat(img, mat2);
    cout << mat2 <<endl;

    return 0;
}

void printMat(InputArray _mat, OutputArray _output)
{
    Mat img = _mat.getMat();
    cout << img << endl;
    Mat img2 = img + 3;
    img2.copyTo(_output);
}