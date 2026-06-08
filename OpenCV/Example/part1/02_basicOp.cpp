#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

cv::String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

//string folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

int main()
{
    Point_<int> p1(1,3);
    Point_<float> p2(3.14, 4.31);
    Point_<int> p3(5, 8);

    cout << p1 << p2 << endl;
    cout << p1 + p3 << endl;

    Point p4(1, 2);     // point_<int>
    Point2i p5(3, 4);   // point_<int>
    Point2f p6(3.11, 2.11); 


    cout << p4 << p5 << p6 << endl;

    Size sz1;
    Size2i sz2(10, 20); 
    sz1.width = 10;         // private 변수가 아니다.
    sz1.height = 20;
    
    Size2f sz3(3.14, 6.78);
    cout << "sz1.area()" << sz1.area() << "sz1.aspectRatio()" << sz1.aspectRatio() << endl;
    
    Rect rc1;
    Rect rc2(10, 10, 20, 20);
    Rect rc3 = rc1 + Size(50, 40);
    Rect rc4 = rc2 + Point(10, 10);
    Rect rc5 = rc3 & rc4;
    Rect rc6 = rc3 | rc4;

    cout << "rc3: " << rc3 << endl;
    cout << "rc4: " << rc4 << endl;
    cout << "rc5: " << rc5 << endl;
    cout << "rc6: " << rc6 << endl;
    cout << rc6.contains(p1);

    Mat img = Mat::zeros(Size(100,100), CV_8SC3);
    rectangle(img, rc3, (255, 255, 255));
    rectangle(img, rc4, (255, 255, 255));
    rectangle(img, rc5, (255, 0, 0));
    rectangle(img, rc6, (0, 255, 255));

    imshow("img", img);
    waitKey(0);  
    return 0;

}
