#include "colors.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img(400, 600, CV_8UC3, Color::Black);

    int t = 0;

    while (true)
    {
        Mat img2 = img.clone();

        // -----------------------------
        // 배경 반짝이 / 별
        // -----------------------------
        for (int i = 0; i < 25; i++)
        {
            int x = (i * 73 + t * 3) % 600;
            int y = (i * 41 + t * 2) % 220;

            if ((i + t / 5) % 3 == 0)
                drawMarker(img2, Point(x, y), Color::Yellow, MARKER_STAR, 12, 1, LINE_AA);
            else if ((i + t / 5) % 3 == 1)
                circle(img2, Point(x, y), 3, Color::Cyan, FILLED, LINE_AA);
            else
                rectangle(img2, Rect(x, y, 6, 6), Color::Magenta, FILLED, LINE_AA);
        }

        // -----------------------------
        // 폭죽 효과
        // -----------------------------
        Point fire1(120, 90);
        Point fire2(480, 90);
        int r = 20 + (t * 2) % 60;

        for (int i = 0; i < 12; i++)
        {
            double angle = CV_2PI * i / 12.0;

            Point p1(
                fire1.x + (int)(cos(angle) * r),
                fire1.y + (int)(sin(angle) * r));

            Point p2(
                fire2.x + (int)(cos(angle) * (r - 10)),
                fire2.y + (int)(sin(angle) * (r - 10)));

            line(img2, fire1, p1, Color::Red, 2, LINE_AA);
            line(img2, fire2, p2, Color::Orange, 2, LINE_AA);

            drawMarker(img2, p1, Color::Yellow, MARKER_STAR, 8, 1, LINE_AA);
            drawMarker(img2, p2, Color::Cyan, MARKER_STAR, 8, 1, LINE_AA);
        }

        // -----------------------------
        // 케이크 받침
        // -----------------------------
        ellipse(img2, Point(300, 330), Size(180, 35), 0, 0, 360, Color::White, FILLED, LINE_AA);
        ellipse(img2, Point(300, 330), Size(180, 35), 0, 0, 360, Color::Blue, 3, LINE_AA);

        // -----------------------------
        // 케이크 1층
        // -----------------------------
        rectangle(img2, Rect(170, 230, 260, 100), Color::Pink, FILLED, LINE_AA);
        rectangle(img2, Rect(170, 230, 260, 100), Color::White, 3, LINE_AA);

        // 크림 장식
        for (int x = 185; x <= 415; x += 30)
        {
            circle(img2, Point(x, 230), 14, Color::White, FILLED, LINE_AA);
        }

        // 케이크 무늬
        for (int x = 190; x <= 390; x += 40)
        {
            line(img2, Point(x, 250), Point(x + 20, 310), Color::Red, 2, LINE_AA);
            line(img2, Point(x + 20, 250), Point(x, 310), Color::Yellow, 2, LINE_AA);
        }

        // -----------------------------
        // 케이크 2층
        // -----------------------------
        rectangle(img2, Rect(220, 170, 160, 70), Color::Orange, FILLED, LINE_AA);
        rectangle(img2, Rect(220, 170, 160, 70), Color::White, 3, LINE_AA);

        for (int x = 235; x <= 365; x += 25)
        {
            circle(img2, Point(x, 170), 12, Color::White, FILLED, LINE_AA);
        }

        // -----------------------------
        // 초
        // -----------------------------
        int flameMove = (t % 10 < 5) ? 0 : 4;

        for (int x = 240; x <= 360; x += 30)
        {
            // 초 몸통
            rectangle(img2, Rect(x, 120, 12, 50), Color::Cyan, FILLED, LINE_AA);
            rectangle(img2, Rect(x, 120, 12, 50), Color::White, 1, LINE_AA);

            // 초 무늬
            line(img2, Point(x, 130), Point(x + 12, 140), Color::Blue, 1, LINE_AA);
            line(img2, Point(x, 145), Point(x + 12, 155), Color::Blue, 1, LINE_AA);

            // 불꽃
            ellipse(
                img2,
                Point(x + 6, 110 - flameMove),
                Size(8, 15),
                0,
                0,
                360,
                Color::Yellow,
                FILLED,
                LINE_AA);

            ellipse(
                img2,
                Point(x + 6, 113 - flameMove),
                Size(4, 8),
                0,
                0,
                360,
                Color::Red,
                FILLED,
                LINE_AA);
        }

        // -----------------------------
        // 하트 모양 풍선 비슷한 효과
        // -----------------------------
        int balloonY = 250 - (t % 160);

        circle(img2, Point(70, balloonY), 18, Color::Red, FILLED, LINE_AA);
        circle(img2, Point(95, balloonY), 18, Color::Red, FILLED, LINE_AA);
        ellipse(img2, Point(82, balloonY + 18), Size(28, 35), 0, 0, 360, Color::Red, FILLED, LINE_AA);
        line(img2, Point(82, balloonY + 50), Point(75, balloonY + 110), Color::White, 1, LINE_AA);

        circle(img2, Point(505, balloonY + 40), 18, Color::Cyan, FILLED, LINE_AA);
        circle(img2, Point(530, balloonY + 40), 18, Color::Cyan, FILLED, LINE_AA);
        ellipse(img2, Point(517, balloonY + 58), Size(28, 35), 0, 0, 360, Color::Cyan, FILLED, LINE_AA);
        line(img2, Point(517, balloonY + 90), Point(525, balloonY + 150), Color::White, 1, LINE_AA);

        // -----------------------------
        // 생일 축하 느낌의 왕관 / 축하 장식
        // -----------------------------
        line(img2, Point(260, 80), Point(280, 45), Color::Yellow, 3, LINE_AA);
        line(img2, Point(280, 45), Point(300, 80), Color::Yellow, 3, LINE_AA);
        line(img2, Point(300, 80), Point(320, 45), Color::Yellow, 3, LINE_AA);
        line(img2, Point(320, 45), Point(340, 80), Color::Yellow, 3, LINE_AA);
        line(img2, Point(260, 80), Point(340, 80), Color::Yellow, 3, LINE_AA);

        circle(img2, Point(280, 45), 5, Color::Red, FILLED, LINE_AA);
        circle(img2, Point(320, 45), 5, Color::Cyan, FILLED, LINE_AA);
        circle(img2, Point(300, 80), 5, Color::Magenta, FILLED, LINE_AA);

        // -----------------------------
        // 위로 올라가는 축하 화살표
        // -----------------------------
        int arrowY = 390 - (t * 3 % 180);

        arrowedLine(img2, Point(35, arrowY + 40), Point(35, arrowY), Color::Yellow, 2, LINE_AA);
        arrowedLine(img2, Point(565, arrowY + 40), Point(565, arrowY), Color::Yellow, 2, LINE_AA);

        imshow("Happy Birthday Effect", img2);

        if (waitKey(1000 / 30) == 27)
            break;

        t++;
    }

    destroyAllWindows();
    return 0;
}