#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    const String folderPath ="/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

    Mat img = imread(folderPath + "lenna.bmp");
    Point2f srcPts[4];
    Point2f dstPts[4];
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(1, 0);
    srcPts[2] = Point2f(1, 1);
    srcPts[3] = Point2f(0, 1);
    dstPts[0] = Point2f(0, 0.1);
    dstPts[1] = Point2f(0.8, 0.7);
    dstPts[2] = Point2f(0.65, 0.85);
    dstPts[3] = Point2f(0.2, 0.9);

    Mat M = getPerspectiveTransform(srcPts, dstPts);

    Mat dst;
    warpPerspective(img, dst, M, img.size());

    imshow("img", img);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
    return 0;
}