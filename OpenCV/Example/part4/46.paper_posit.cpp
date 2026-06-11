// → HSV 변환
// → 노란색 테이프 threshold
// → morphology로 노이즈 제거
// → 테이프 contour 검출
// → approxPolyDP로 테이프 4점 검출
// → 노란색 테이프 기준 homography 생성
// → 종이 부분 찾기( 노란색 테이프 주위의 색 검출 후 inrange 적용)
// → findContours
// → 종이 contour / polygon 검출
// → 종이 contour를 homography로 변환
// → contourArea로 비율 넓이 계산
// 비정형의 노트의 넓이를 카메라로 계산하기
// 관련된 정보는 모두 화면에 putText 로 출력
#include "colors.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static vector<Point2f> orderPoints(const vector<Point> &pts)
{
    vector<Point2f> p;
    for (auto &pt : pts)
        p.push_back(Point2f((float)pt.x, (float)pt.y));

    vector<Point2f> ordered(4);

    double minSum = 1e18, maxSum = -1e18;
    double minDiff = 1e18, maxDiff = -1e18;

    for (auto &pt : p)
    {
        double sum = pt.x + pt.y;
        double diff = pt.x - pt.y;

        if (sum < minSum)
        {
            minSum = sum;
            ordered[0] = pt;
        }

        if (sum > maxSum)
        {
            maxSum = sum;
            ordered[2] = pt;
        }

        if (diff > maxDiff)
        {
            maxDiff = diff;
            ordered[1] = pt;
        }

        if (diff < minDiff)
        {
            minDiff = diff;
            ordered[3] = pt;
        }
    }

    return ordered;
}

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

    Mat frame;

    while (true)
    {
        cap >> frame;

        if (frame.empty())
            break;

        Mat display = frame.clone();

        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // =====================================================
        // 1. 노란색 테이프 검출
        // =====================================================
        Mat yellowMask;
        inRange(hsv,
                Scalar(20, 80, 80),
                Scalar(40, 255, 255),
                yellowMask);

        Mat kernel5 = getStructuringElement(MORPH_RECT, Size(5, 5));
        morphologyEx(yellowMask, yellowMask, MORPH_OPEN, kernel5);
        morphologyEx(yellowMask, yellowMask, MORPH_CLOSE, kernel5);

        vector<vector<Point>> tapeContours;
        findContours(yellowMask, tapeContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        vector<Point> tapePoly;
        vector<Point> tapeContour;
        double maxTapeArea = 0.0;

        for (auto &c : tapeContours)
        {
            double area = contourArea(c);

            if (area < 300)
                continue;

            vector<Point> approx;
            approxPolyDP(c, approx, arcLength(c, true) * 0.02, true);

            if (approx.size() == 4 && area > maxTapeArea)
            {
                maxTapeArea = area;
                tapePoly = approx;
                tapeContour = c;
            }
        }

        Mat paperMask = Mat::zeros(frame.size(), CV_8UC1);

        if (tapePoly.size() == 4)
        {
            // =====================================================
            // 2. 테이프 주변 영역 만들기
            //    테이프 bounding box를 크게 확장해서 주변 종이 색 샘플링
            // =====================================================
            Rect tapeBox = boundingRect(tapePoly);

            int margin = 35;

            Rect sampleBox(
                max(0, tapeBox.x - margin),
                max(0, tapeBox.y - margin),
                min(frame.cols - max(0, tapeBox.x - margin), tapeBox.width + margin * 2),
                min(frame.rows - max(0, tapeBox.y - margin), tapeBox.height + margin * 2));

            // sampleMask: 테이프 주변 영역
            Mat sampleMask = Mat::zeros(frame.size(), CV_8UC1);
            rectangle(sampleMask, sampleBox, Scalar(255), -1);

            // 테이프 자체는 샘플에서 제외
            Mat tapeOnlyMask = Mat::zeros(frame.size(), CV_8UC1);
            drawContours(tapeOnlyMask, vector<vector<Point>>{tapeContour}, 0, Scalar(255), -1);

            dilate(tapeOnlyMask,
                   tapeOnlyMask,
                   getStructuringElement(MORPH_RECT, Size(9, 9)));

            sampleMask.setTo(Scalar(0), tapeOnlyMask);

            // =====================================================
            // 3. 샘플 픽셀들의 HSV 평균/표준편차 계산
            // =====================================================
            Scalar meanHSV, stdHSV;
            meanStdDev(hsv, meanHSV, stdHSV, sampleMask);

            double hMean = meanHSV[0];
            double sMean = meanHSV[1];
            double vMean = meanHSV[2];

            double hStd = stdHSV[0];
            double sStd = stdHSV[1];
            double vStd = stdHSV[2];

            // 너무 좁거나 넓지 않게 범위 제한
            int hRange = cvRound(max(8.0, min(25.0, hStd * 2.5)));
            int sRange = cvRound(max(30.0, min(90.0, sStd * 2.5)));
            int vRange = cvRound(max(30.0, min(90.0, vStd * 2.5)));

            int hLow = max(0, cvRound(hMean) - hRange);
            int hHigh = min(179, cvRound(hMean) + hRange);

            int sLow = max(0, cvRound(sMean) - sRange);
            int sHigh = min(255, cvRound(sMean) + sRange);

            int vLow = max(0, cvRound(vMean) - vRange);
            int vHigh = min(255, cvRound(vMean) + vRange);

            // =====================================================
            // 4. 테이프 주변에서 추정한 종이 색으로 inRange
            // =====================================================
            inRange(hsv,
                    Scalar(hLow, sLow, vLow),
                    Scalar(hHigh, sHigh, vHigh),
                    paperMask);

            // 노란색 테이프는 종이 마스크에 포함되지 않게 제거
            paperMask.setTo(Scalar(0), yellowMask);

            morphologyEx(paperMask, paperMask, MORPH_OPEN, kernel5);
            morphologyEx(paperMask, paperMask, MORPH_CLOSE,
                         getStructuringElement(MORPH_RECT, Size(15, 15)));

            // 작은 구멍 메우기
            dilate(paperMask, paperMask, getStructuringElement(MORPH_RECT, Size(5, 5)));
            erode(paperMask, paperMask, getStructuringElement(MORPH_RECT, Size(5, 5)));

            // =====================================================
            // 5. 종이 contour 찾기
            // =====================================================
            vector<vector<Point>> paperContours;
            findContours(paperMask, paperContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

            vector<Point> bestPaperContour;
            vector<Point> bestPaperPoly;
            double maxPaperArea = 0.0;

            for (auto &c : paperContours)
            {
                double area = contourArea(c);

                if (area < 3000)
                    continue;

                // 테이프 중심이 포함된 contour를 우선 선택
                Point2f tapeCenter(
                    tapeBox.x + tapeBox.width / 2.0f,
                    tapeBox.y + tapeBox.height / 2.0f);

                double inside = pointPolygonTest(c, tapeCenter, false);

                if (inside >= 0 && area > maxPaperArea)
                {
                    vector<Point> approx;
                    approxPolyDP(c, approx, arcLength(c, true) * 0.02, true);

                    maxPaperArea = area;
                    bestPaperContour = c;
                    bestPaperPoly = approx;
                }
            }

            // 테이프 중심이 포함된 contour를 못 찾으면 가장 큰 contour 사용
            if (bestPaperContour.empty())
            {
                for (auto &c : paperContours)
                {
                    double area = contourArea(c);

                    if (area > maxPaperArea)
                    {
                        vector<Point> approx;
                        approxPolyDP(c, approx, arcLength(c, true) * 0.02, true);

                        maxPaperArea = area;
                        bestPaperContour = c;
                        bestPaperPoly = approx;
                    }
                }
            }

            // =====================================================
            // 6. 테이프 5cm x 5cm 기준으로 종이 넓이 계산
            // =====================================================
            if (!bestPaperContour.empty())
            {
                vector<Point2f> tapePts = orderPoints(tapePoly);

                vector<Point2f> realTapePts = {
                    Point2f(0.0f, 0.0f),
                    Point2f(5.0f, 0.0f),
                    Point2f(5.0f, 5.0f),
                    Point2f(0.0f, 5.0f)};

                Mat H = getPerspectiveTransform(tapePts, realTapePts);

                vector<Point2f> paperPts;
                for (auto &p : bestPaperContour)
                    paperPts.push_back(Point2f((float)p.x, (float)p.y));

                vector<Point2f> paperCmPts;
                perspectiveTransform(paperPts, paperCmPts, H);

                double paperAreaCm2 = contourArea(paperCmPts);

                polylines(display, tapePoly, true, Color::Red, 2);
                rectangle(display, sampleBox, Color::Yellow, 2);
                polylines(display, bestPaperPoly, true, Color::Blue, 3);

                putText(display,
                        format("Paper HSV: H[%d,%d] S[%d,%d] V[%d,%d]",
                               hLow, hHigh, sLow, sHigh, vLow, vHigh),
                        Point(20, 35),
                        FONT_HERSHEY_SIMPLEX,
                        0.55,
                        Color::Red,
                        2);

                putText(display,
                        format("Paper area: %.2f cm^2", paperAreaCm2),
                        Point(20, 70),
                        FONT_HERSHEY_SIMPLEX,
                        0.8,
                        Color::Red,
                        2);
            }
            else
            {
                polylines(display, tapePoly, true, Color::Red, 2);
                rectangle(display, sampleBox, Color::Yellow, 2);

                putText(display,
                        "Tape found, paper contour not found",
                        Point(20, 40),
                        FONT_HERSHEY_SIMPLEX,
                        0.7,
                        Color::Red,
                        2);
            }

            imshow("sampleMask", sampleMask);
        }
        else
        {
            putText(display,
                    "Yellow tape not found",
                    Point(20, 40),
                    FONT_HERSHEY_SIMPLEX,
                    0.8,
                    Color::Red,
                    2);
        }

        imshow("display", display);
        imshow("yellowMask", yellowMask);
        imshow("paperMask", paperMask);

        if (waitKey(30) == 27)
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}