#include "../part1/colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

int main()
{
    Mat img(400, 600, CV_8UC3, Color::White);

    int a = 0, b = 0, c = 0;

    while (true)
    {
        img.setTo(Color::White); // 배경 그리기
        putText(img, "Hi.", Point(20 + a, 50), FONT_HERSHEY_SIMPLEX, 2, Color::Red);
        putText(img, "Bye.", Point(20 + a, 100), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 2, Color::Red);
        putText(img, "Ni Hao.", Point(20 + a, 150), FONT_HERSHEY_DUPLEX, 3, Color::Blue);
        putText(img, "Zai Jian.", Point(20 + a, 200), FONT_HERSHEY_PLAIN, 4, Color::Black);

        imshow("img", img);
        if (waitKey(33) == 27)
            break;
        a += 1;
        b -= 1;
        c += 3;
    }
    destroyAllWindows();
    return 0;
}
