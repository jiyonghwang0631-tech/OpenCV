#include <iostream>
#include <opencv2/opencv.hpp>
#include "colors.hpp"

using namespace std;
using namespace cv;

String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

void printMat(InputArray _mat, OutputArray _output);

int main()
{
    Mat img1 = imread(folderPath + "dog.bmp");
    
    Mat img2 = img1;
    Mat img3;
    img3 = img1;

    Mat img4 = img1.clone();
    Mat img5;
    img1.copyTo(img5);

    img1.setTo(Color::Yellow);
    
    Rect roi(220, 120, 200, 200);
    Mat img6 = img4(roi);
    img6.setTo(Color::Black);

    imshow("img1", img1);
    imshow("img2", img2);
    imshow("img3", img3);
    imshow("img4", img4);
    imshow("img5", img5);
    waitKey();
    destroyAllWindows();
    
    return 0;
}
