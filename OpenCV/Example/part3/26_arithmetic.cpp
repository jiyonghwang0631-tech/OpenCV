#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    const String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";
    Mat img = imread(folderPath + "lenna256.bmp", IMREAD_GRAYSCALE);
    Mat img2 = imread(folderPath + "square.bmp", IMREAD_GRAYSCALE);
    Mat dst1, dst2, dst3, dst4, dst5, dst6, dst7, dst8;

    bitwise_and(img, img2, dst1);
    bitwise_or(img, img2, dst2);
    bitwise_xor(img, img2, dst3);
    bitwise_not(img, dst4);
    add(img, img2, dst5);
    addWeighted(img, 0.9, img2, 0.1, 0, dst6);
    subtract(img, img2, dst7);
    absdiff(img, img2, dst8);

    vector<pair<string, Mat>> images = 
    {
        {"lenna", img},
        {"square", img2},
        {"and", dst1},
        {"or", dst2},
        {"xor", dst3},
        {"not", dst4},
        {"add", dst5},
        {"addWeighted", dst6},
        {"subtract", dst7},
        {"absdiff", dst8},
    };

    for (auto [name, image] : images)
    {
        imshow(name, image);
    }

    waitKey();

    return 0;
}