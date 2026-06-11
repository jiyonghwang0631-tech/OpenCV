#include <iostream>
#include <opencv2/opencv.hpp>
#include "colors.hpp"

using namespace std;
using namespace cv;

int main()
{
    
    const String folderPath =  "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";
    Mat img = imread(folderPath + "sudoku.jpg", IMREAD_GRAYSCALE);
    Mat img2, img3;
    threshold(img, img2, 128, 255, THRESH_BINARY);
    adaptiveThreshold(img, img3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 35, 5);
    imshow("sudoku", img);
    imshow("threshold_binary", img2);    
    imshow("adaptive", img3);
    waitKey();

    return 0;
}