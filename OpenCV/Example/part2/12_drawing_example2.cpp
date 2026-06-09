#include "../part1/colors.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void drawBackground(Mat &img)
{
    rectangle(img, Rect(0, 0, 600, 260), Scalar(235, 205, 135), FILLED);
    rectangle(img, Rect(0, 260, 600, 140), Scalar(90, 170, 80), FILLED);
    rectangle(img, Rect(0, 320, 600, 80), Scalar(95, 95, 95), FILLED);

    circle(img, Point(500, 70), 35, Color::Yellow, FILLED, LINE_AA);

    ellipse(img, Point(105, 70), Size(45, 20), 0, 0, 360, Color::White, FILLED, LINE_AA);
    ellipse(img, Point(145, 70), Size(45, 22), 0, 0, 360, Color::White, FILLED, LINE_AA);
    ellipse(img, Point(125, 55), Size(35, 18), 0, 0, 360, Color::White, FILLED, LINE_AA);

    Point mountain1[] = {Point(0, 260), Point(140, 120), Point(280, 260)};
    Point mountain2[] = {Point(180, 260), Point(340, 110), Point(520, 260)};
    Point mountain3[] = {Point(360, 260), Point(500, 145), Point(600, 260)};
    fillConvexPoly(img, mountain1, 3, Scalar(115, 140, 105), LINE_AA);
    fillConvexPoly(img, mountain2, 3, Scalar(105, 130, 115), LINE_AA);
    fillConvexPoly(img, mountain3, 3, Scalar(120, 150, 110), LINE_AA);

    for (int x = 35; x <= 560; x += 95)
    {
        rectangle(img, Rect(x + 13, 235, 14, 45), Scalar(45, 90, 120), FILLED, LINE_AA);
        circle(img, Point(x + 20, 225), 28, Scalar(40, 125, 55), FILLED, LINE_AA);
    }

    line(img, Point(0, 360), Point(600, 360), Color::White, 2, LINE_AA);
    for (int x = 20; x < 600; x += 80)
    {
        line(img, Point(x, 340), Point(x + 40, 340), Color::Yellow, 3, LINE_AA);
    }
}

static void drawPerson(Mat &img, Point foot, int t)
{
    double phase = sin(t * 0.25);
    int armSwing = static_cast<int>(phase * 22);
    int legSwing = static_cast<int>(phase * 24);

    Point hip(foot.x, foot.y - 70);
    Point neck(foot.x, foot.y - 125);
    Point head(foot.x, foot.y - 150);

    line(img, hip, neck, Color::Blue, 8, LINE_AA);
    circle(img, head, 18, Scalar(80, 180, 230), FILLED, LINE_AA);
    circle(img, Point(head.x + 6, head.y - 4), 2, Color::Black, FILLED, LINE_AA);
    line(img, Point(head.x + 5, head.y + 8), Point(head.x + 14, head.y + 6), Color::Red, 2, LINE_AA);

    Point leftShoulder(neck.x - 7, neck.y + 15);
    Point rightShoulder(neck.x + 7, neck.y + 15);
    Point leftHand(neck.x - 35 - armSwing, neck.y + 50);
    Point rightHand(neck.x + 35 + armSwing, neck.y + 50);
    line(img, leftShoulder, leftHand, Color::Orange, 5, LINE_AA);
    line(img, rightShoulder, rightHand, Color::Orange, 5, LINE_AA);

    Point leftFoot(foot.x - 22 + legSwing, foot.y);
    Point rightFoot(foot.x + 22 - legSwing, foot.y);
    line(img, hip, leftFoot, Color::Purple, 6, LINE_AA);
    line(img, hip, rightFoot, Color::Purple, 6, LINE_AA);

    line(img, Point(leftFoot.x - 10, leftFoot.y), Point(leftFoot.x + 12, leftFoot.y), Color::Black, 4, LINE_AA);
    line(img, Point(rightFoot.x - 10, rightFoot.y), Point(rightFoot.x + 12, rightFoot.y), Color::Black, 4, LINE_AA);
}

int main()
{
    Mat background(400, 600, CV_8UC3);
    drawBackground(background);

    namedWindow("Walking Person", WINDOW_AUTOSIZE);

    int t = 0;
    while (true)
    {
        Mat img = background.clone();
        int x = -60 + (t * 3) % 720;
        drawPerson(img, Point(x, 320), t);

        imshow("Walking Person", img);

        int key = waitKey(1000 / 30);
        if (key == 27 || key == 'q' || getWindowProperty("Walking Person", WND_PROP_VISIBLE) < 1)
            break;

        t++;
    }

    destroyAllWindows();
    return 0;
}
