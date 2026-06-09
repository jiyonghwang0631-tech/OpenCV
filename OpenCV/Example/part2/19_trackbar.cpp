#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void on_level_change(int pose, void *data);

int main()
{
    const String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";
    Mat img = imread(folderPath + "lenna.bmp");
    namedWindow("img");
    int pos = 0;
    createTrackbar("level", "img", &pos, 255, on_level_change, (void *)&img);

    while (true)
    {
        imshow("img", img);
        cout << pos << endl;
        if (waitKey(30) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}

void on_level_change(int pos, void *data)
{
    Mat *img = (Mat *)data;
    img->setTo(Scalar(pos, 0, 0));
}
