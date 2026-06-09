#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

int main()
{
    Mat img = imread(folderPath + "lenna.bmp");
    namedWindow("img");

    auto start_tick = getTickCount();
    int keycode;
    TickMeter tm1;
    TickMeter tm2;
    int fps = 55;
    int needed_tick_ms;
    while (true)
    {
        tm1.start();
        tm2.start();
        // 필요한 코드 ( 오래걸리는)

        imshow("img", img);
        tm1.stop();
        double elased_ms = tm1.getTimeMilli();
        needed_tick_ms = cvRound(1000.0/fps - elased_ms);
        keycode = waitKey(needed_tick_ms);
        if (keycode == 27)
            break;
        if (keycode == 'v' || keycode == 'V')
            img = ~img;
        if (keycode != -1)
        {
            cout << "keycode: " << keycode << endl;
        }
        // cout << "frequency: " << getTickFrequency() << endl;
        cout << "fps: " << getTickFrequency()/(getTickCount() - start_tick) << endl;
    }
    destroyAllWindows();
    return 0;
}