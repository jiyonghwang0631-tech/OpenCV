#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0, CAP_V4L2);
    if (!cap.isOpened())
    {
        cerr << "카메라를 열 수 없습니다." << endl;
        return -1;
    }

    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);

    Ptr<Feature2D> feature = ORB::create();
    vector<KeyPoint> keypoints;
    vector<Point2f> corners;
    Mat img, img1, img2, gray_img, desc;
    while (true)
    {
        if (!cap.read(img) || img.empty())
        {
            cerr << "카메라 프레임을 읽을 수 없습니다." << endl;
            break;
        }

        img1 = img.clone();
        img2 = img.clone();

        // FAST
        cvtColor(img, gray_img, COLOR_BGR2GRAY);
        FAST(gray_img, keypoints, 60, true);
        for (const KeyPoint &k : keypoints)
        {
            circle(
                img,
                Point(cvRound(k.pt.x), cvRound(k.pt.y)),
                5,
                Color::Red,
                2);
        }
        imshow("img", img);

        // goodFeature
        goodFeaturesToTrack(gray_img, corners, 1000, 0.01, 10);
        for (const Point2f &p : corners)
        {
            circle(
                img1,
                Point(cvRound(p.x), cvRound(p.y)),
                5,
                Color::Red,
                2);
        }
        imshow("img1", img1);

        // ORB
        // feature->detect(img, keypoints);
        // feature->compute(img, keypoints, dst);
        feature->detectAndCompute(img2, noArray(), keypoints, desc);
        drawKeypoints(img2, keypoints, img2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        imshow("img2", img2);
        if (waitKey(33) == 27)
            break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
