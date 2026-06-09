// 마우스를 따라 다니는 사각형 박스를 만드세요.
// 마우스 오른쪽 버튼을 누르면 사각형 박스의 색깔이 랜덤으로 변경되도록 하세요.
// 왼쪽버튼을 누르고 움직이는 선(사각형 박스의 색깔과 같은) 선이 그어지도록 하세요.
// 휠 버튼을 누르면 (스포이드 기능) 마우스 위치의 픽셀 정보를 사각형 박스이 색깔을 변화 시키세요.
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct MouseState
{
    Mat canvas;
    Point mousePosition{0, 0};
    Point previousPosition{0, 0};
    Scalar color{0, 0, 255};
    bool drawing{false};
};

void onMouse(int event, int x, int y, int flags, void *userdata)
{
    MouseState *state = static_cast<MouseState *>(userdata);
    Point currentPosition(x, y);
    state->mousePosition = currentPosition;

    switch (event)
    {
        case EVENT_LBUTTONDOWN:
            state->drawing = true;
            state->previousPosition = currentPosition;
            break;

        case EVENT_MOUSEMOVE:
            if (state->drawing && (flags & EVENT_FLAG_LBUTTON))
            {
                line(
                    state->canvas,
                    state->previousPosition,
                    currentPosition,
                    state->color,
                    3,
                    LINE_AA);
                state->previousPosition = currentPosition;
            }
            break;

        case EVENT_LBUTTONUP:
            state->drawing = false;
            break;

        case EVENT_RBUTTONDOWN:
        {
            RNG &rng = theRNG();
            state->color = Scalar(
                rng.uniform(0, 256),
                rng.uniform(0, 256),
                rng.uniform(0, 256));
            break;
        }

        case EVENT_MBUTTONDOWN:
            if (x >= 0 && x < state->canvas.cols && y >= 0 && y < state->canvas.rows)
            {
                Vec3b pixel = state->canvas.at<Vec3b>(y, x);
                state->color = Scalar(pixel[0], pixel[1], pixel[2]);

                cout << "BGR: "
                     << static_cast<int>(pixel[0]) << ", "
                     << static_cast<int>(pixel[1]) << ", "
                     << static_cast<int>(pixel[2]) << '\n';
            }
            break;
    }
}

int main()
{
    const String folderPath =
        "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

    MouseState state;
    state.canvas = imread(folderPath + "lenna.bmp");

    if (state.canvas.empty())
    {
        cerr << "이미지를 열 수 없습니다." << endl;
        return -1;
    }

    const String windowName = "Mouse Example";
    namedWindow(windowName, WINDOW_AUTOSIZE);
    setMouseCallback(windowName, onMouse, &state);

    while (true)
    {
        Mat display = state.canvas.clone();

        const int boxSize = 40;
        int boxX = max(0, min(state.mousePosition.x - boxSize / 2, display.cols - boxSize));
        int boxY = max(0, min(state.mousePosition.y - boxSize / 2, display.rows - boxSize));
        rectangle(
            display,
            Rect(boxX, boxY, boxSize, boxSize),
            state.color,
            3,
            LINE_AA);

        imshow(windowName, display);

        int key = waitKey(30);
        if (key == 27 || key == 'q' ||
            getWindowProperty(windowName, WND_PROP_VISIBLE) < 1)
        {
            break;
        }
    }

    destroyAllWindows();
    return 0;
}
