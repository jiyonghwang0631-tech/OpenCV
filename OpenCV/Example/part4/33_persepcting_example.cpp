// 이 코드를 while(true) 를 해서 물결 모양의 효과를 내게 만들어줘

#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    const String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";


    Mat img = imread(folderPath + "lenna.bmp");

    if (img.empty())
    {
        cerr << "이미지 불러오기 실패!" << endl;
        return -1;
    }

    int w = img.cols;
    int h = img.rows;

    Point2f srcPts[4];

    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(w - 1, 0);
    srcPts[2] = Point2f(w - 1, h - 1);
    srcPts[3] = Point2f(0, h - 1);

    int frame = 0;

    while (true)
    {
        Point2f dstPts[4];

        float t = frame * 0.08f;

        float waveTop = 40.0f * sin(t);
        float waveBottom = 40.0f * sin(t + CV_PI);
        float waveLeft = 30.0f * sin(t + CV_PI / 2);
        float waveRight = 30.0f * sin(t + CV_PI * 1.5);

        dstPts[0] = Point2f(0 + waveLeft, 0 + waveTop);
        dstPts[1] = Point2f(w - 1 + waveRight, 0 - waveTop);
        dstPts[2] = Point2f(w - 1 - waveRight, h - 1 + waveBottom);
        dstPts[3] = Point2f(0 - waveLeft, h - 1 - waveBottom);

        Mat M = getPerspectiveTransform(srcPts, dstPts);

        Mat dst;
        warpPerspective(
            img,
            dst,
            M,
            img.size(),
            INTER_LINEAR,
            BORDER_CONSTANT,
            Scalar(0, 0, 0));

        imshow("img", img);
        imshow("wave perspective", dst);

        int key = waitKey(30);
        if (key == 27)
            break;

        frame++;
    }

    destroyAllWindows();

    return 0;
}