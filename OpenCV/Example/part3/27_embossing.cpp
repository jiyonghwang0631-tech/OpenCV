#include <iostream>
#include <opencv2/opencv.hpp>
#include "colors.hpp"

using namespace std;
using namespace cv;

void filter_embossing(Mat &img);

String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";


int main()
{
    VideoCapture cap(0, CAP_V4L2);
    
    if (!cap.isOpened())
    {
        cerr << "카메라를 열수 없습니다." << endl;
    }
    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);
        
    Mat frame;
    for (int i = 0; i < 1000; ++i)
    {
        cap >> frame;
        if(waitKey(30) == 27)
            break;
        filter_embossing(frame);
        imshow("frame", frame);
    }

    cap.release();
    destroyAllWindows();
    return 0;

}

void filter_embossing(Mat &img)
{
    float data[] = {-1, -1, 0, -1, 0, 1, 0, 1, 1}; //커널의 데이터 중요!
    Mat emboss(3, 3, CV_32FC1, data);
    
    //Mat dst = Mat::zeros(img.size(), img.type());
    filter2D(img, img, -1, emboss, Point(-1,-1), 0, BORDER_REPLICATE);
}
