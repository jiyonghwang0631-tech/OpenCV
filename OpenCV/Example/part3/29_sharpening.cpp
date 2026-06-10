#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void blur_ex(Mat &img);

int main()
{
    const String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";
    VideoCapture cap(0, CAP_V4L2);

    if (!cap.isOpened())
    {
        cerr << "카메라를 열수 없습니다." << endl;
    }

    // MJPG
    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);
    int pos = 1;
    namedWindow("frame");
    createTrackbar("blur", "frame", &pos, 30);

    Mat frame;
    Mat blurM, dst;
    for (int i = 0; i < 1000; ++i)
    {
        cap >> frame;
        if (waitKey(30) == 27)
            break;

        GaussianBlur(frame, blurM, Size(0, 0), double(pos));
        dst = (1 + (float)pos * 0.1) * frame - (float)pos * 0.1 * blurM;
        imshow("frame", frame);
    }
    cap.release();
    destroyAllWindows();
    return 0;
}

void blur_ex(Mat &img)
{
    float data[] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; // 커널의 데이터 중요!
    Mat blur(3, 3, CV_32FC1, data);
    blur = blur / 9.0;

    // Mat dst = Mat::zeros(img.size(), img.type());
    filter2D(img, img, -1, blur, Point(-1, -1), 0, BORDER_REPLICATE);
}