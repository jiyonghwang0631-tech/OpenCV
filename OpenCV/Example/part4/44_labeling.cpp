#include <iostream>
#include <opencv2/opencv.hpp>
#include "colors.hpp"

using namespace std;
using namespace cv;

int main()
{
    
    const String folderPath =  "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";
    Mat img = imread(folderPath + "milkdrop.bmp", IMREAD_GRAYSCALE);
    Mat img2, img3, img4, img5;
    threshold(img, img2, 128, 255, THRESH_OTSU);
    erode(img2, img3, Mat(), Point(-1, -1), 5);
    dilate(img2, img4, Mat());
    morphologyEx(img2, img5, MORPH_OPEN, Mat(), Point(-1, -1), 5);

    Mat labels;
    int cnt = connectedComponents(img4, labels);
    cout << "number of labels : " << cnt << endl;
    Mat stats, centroids;
    cnt = connectedComponentsWithStats(img4, labels, stats, centroids);
    for (int i = 1 ; i < cnt ; ++i)
    {
        int *p = stats.ptr<int>(i);
        if(p[4]<20)
            continue;
        rectangle(img4, Rect(p[0], p[1], p[2], p[3]), Scalar(128));
        circle(img4, Point(centroids.ptr<int>(i)[0], centroids.ptr<int>(i)[1]), 5, Scalar(128), -1);    
    }
    imshow("milkdrop", img);
    imshow("threshold_binary", img2);    
    imshow("adaptive", img3);
    imshow("dialate", img4);
    imshow("morphology", img5);
    waitKey();

    return 0;
}