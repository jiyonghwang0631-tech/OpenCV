#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

void on_mouse(int, int, int, int, void *);

int main()
{
    Mat img = imread(folderPath + "lenna.bmp");
    namedWindow("img");
    setMouseCallback("img", on_mouse, (void *) & img);


    while (true)
    {
        imshow("img", img);
        if (waitKey(30) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}

void on_mouse(int event, int x, int y, int flags, void *data)
{
    Mat *img = (Mat *)data;
    static int number;
    cout << " Mouse Event 발생 !!" << number++ << endl;
    static Point pt0ld;
    static bool pushed;
    switch(event)
    {
        case EVENT_LBUTTONDOWN:
            pt0ld = Point(x,y);
            pushed = true;
            break;
        case EVENT_LBUTTONUP:
            pushed = false;
            break;
        case EVENT_MOUSEMOVE:
            if(pushed)
            {
                line(*img, pt0ld, Point(x, y), Color::Red, 2);
                pt0ld = Point(x, y);
            }

            break;
    }
}