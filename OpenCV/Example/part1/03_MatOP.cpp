#include <iostream>
#include <opencv2/opencv.hpp>
#include "colors.hpp"



using namespace std;
using namespace cv;

String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

int main()
{
    Mat img;
    Mat img2(100, 200, CV_8UC1);
    Mat img3(100, 200, CV_8UC3, Scalar(0, 0, 255));
    Mat img4(Size(600, 800), CV_8UC3);


    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Mat mat5(2, 5, CV_32FC1, data);
    
    //float *data2 = new float[10];
    vector<float> *data2 = new vector<float>(10);
    // for (int i = 0; i < 10; i+1)
    // {
    //     data[i] = static_cast<float>(i + 1);
    // }
    //vector<float> data3(10);
    //int i = 0;
    for (auto x : *data2)
    {
        x = 100.0;
    }
    Mat mat6(2, 5, CV_32FC1,data2);
 
    cout << "mat5 : "  << mat5 << endl;
    cout << "mat6 : "  << mat6 << endl;


    return 0;
}