// 비행기가 직선으로 더 많이 움직여야 한다 아주 멀어져서 점처럼 보였다가 커지는 구간도 넣고 360도로 회전할 수 있는 구간도 넣어줘
// 거리와 위치 방향에 대한 정보를 tvec rvec 을 분석해서 puttext 로 넣어줘 배경 화면은 두배 resize를 해서 화면을 더 넓혀줘

#include "colors.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    const String folderPath = "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part1/data/";

    Mat airplane = imread(folderPath + "airplane.bmp");
    Mat maskAirPlane = imread(folderPath + "mask_plane.bmp", IMREAD_GRAYSCALE);
    Mat sky = imread(folderPath + "field.bmp");

    if (airplane.empty() || maskAirPlane.empty() || sky.empty())
    {
        cerr << "이미지 파일을 불러올 수 없습니다." << endl;
        return -1;
    }

    // 배경 화면 2배 확대
    resize(sky, sky, Size(), 2.0, 2.0, INTER_LINEAR);

    // 비행기 기본 크기 조절
    resize(airplane, airplane, Size(), 0.5, 0.5, INTER_AREA);
    resize(maskAirPlane, maskAirPlane, Size(), 0.5, 0.5, INTER_NEAREST);

    int skyW = sky.cols;
    int skyH = sky.rows;

    int planeW = airplane.cols;
    int planeH = airplane.rows;

    Point2f srcPts[4] = {
        Point2f(0, 0),
        Point2f((float)planeW - 1, 0),
        Point2f((float)planeW - 1, (float)planeH - 1),
        Point2f(0, (float)planeH - 1)};

    // solvePnP용 3D 물체 좌표
    // 비행기 이미지를 z=0 평면 위의 사각형 물체라고 가정
    vector<Point3f> objectPts = {
        Point3f(-planeW / 2.0f, -planeH / 2.0f, 0.0f),
        Point3f(planeW / 2.0f, -planeH / 2.0f, 0.0f),
        Point3f(planeW / 2.0f, planeH / 2.0f, 0.0f),
        Point3f(-planeW / 2.0f, planeH / 2.0f, 0.0f)};

    // 가상의 카메라 내부 파라미터
    double fx = skyW;
    double fy = skyW;
    double cxCam = skyW / 2.0;
    double cyCam = skyH / 2.0;

    Mat cameraMatrix = (Mat_<double>(3, 3) << fx, 0, cxCam,
                        0, fy, cyCam,
                        0, 0, 1);

    Mat distCoeffs = Mat::zeros(4, 1, CV_64F);

    int frameCount = 0;

    while (true)
    {
        Mat frame = sky.clone();

        int phase = frameCount % 720;

        float cx = skyW / 2.0f;
        float cy = skyH / 2.0f;
        float scale = 1.0f;
        float angle = 0.0f;
        float perspective = 0.0f;

        if (phase < 220)
        {
            // 직선 이동
            float p = phase / 219.0f;

            cx = -planeW + p * (skyW + planeW * 2);
            cy = skyH * 0.45f;

            scale = 0.75f;
            angle = 0.0f;
            perspective = 0.12f * sin(p * CV_PI);
        }
        else if (phase < 360)
        {
            // 멀어지는 구간
            float p = (phase - 220) / 139.0f;

            cx = skyW * 0.5f;
            cy = skyH * 0.45f - p * skyH * 0.20f;

            scale = 0.75f * (1.0f - p) + 0.04f * p;
            angle = 0.0f;
            perspective = 0.25f * p;
        }
        else if (phase < 500)
        {
            // 가까워지는 구간
            float p = (phase - 360) / 139.0f;

            cx = skyW * 0.5f + p * skyW * 0.20f;
            cy = skyH * 0.25f + p * skyH * 0.25f;

            scale = 0.04f * (1.0f - p) + 0.85f * p;
            angle = 0.0f;
            perspective = 0.25f * (1.0f - p);
        }
        else
        {
            // 360도 회전
            float p = (phase - 500) / 219.0f;

            cx = skyW * 0.5f + sin(p * 2.0f * CV_PI) * skyW * 0.18f;
            cy = skyH * 0.50f + cos(p * 2.0f * CV_PI) * skyH * 0.10f;

            scale = 0.80f;
            angle = p * 360.0f;
            perspective = 0.18f * sin(p * 2.0f * CV_PI);
        }

        float w = planeW * scale;
        float h = planeH * scale;

        float rad = angle * CV_PI / 180.0f;
        float cosA = cos(rad);
        float sinA = sin(rad);

        float topW = w * (1.0f - perspective);
        float bottomW = w * (1.0f + perspective);

        Point2f localPts[4] = {
            Point2f(-topW / 2.0f, -h / 2.0f),
            Point2f(topW / 2.0f, -h / 2.0f),
            Point2f(bottomW / 2.0f, h / 2.0f),
            Point2f(-bottomW / 2.0f, h / 2.0f)};

        Point2f dstPts[4];

        for (int i = 0; i < 4; i++)
        {
            float x = localPts[i].x;
            float y = localPts[i].y;

            dstPts[i].x = cx + x * cosA - y * sinA;
            dstPts[i].y = cy + x * sinA + y * cosA;
        }

        Mat M = getPerspectiveTransform(srcPts, dstPts);

        Mat warpedPlane;
        Mat warpedMask;

        warpPerspective(
            airplane,
            warpedPlane,
            M,
            sky.size(),
            INTER_LINEAR,
            BORDER_CONSTANT,
            Scalar(0, 0, 0));

        warpPerspective(
            maskAirPlane,
            warpedMask,
            M,
            sky.size(),
            INTER_NEAREST,
            BORDER_CONSTANT,
            Scalar(0));

        warpedPlane.copyTo(frame, warpedMask);

        // perspective 사각형 표시
        for (int i = 0; i < 4; i++)
        {
            line(frame, dstPts[i], dstPts[(i + 1) % 4], Color::Red, 2);
            circle(frame, dstPts[i], 4, Color::Yellow, -1);
        }

        // solvePnP로 rvec, tvec 계산
        vector<Point2f> imagePts = {
            dstPts[0],
            dstPts[1],
            dstPts[2],
            dstPts[3]};

        Mat rvec, tvec;
        bool ok = solvePnP(
            objectPts,
            imagePts,
            cameraMatrix,
            distCoeffs,
            rvec,
            tvec,
            false,
            SOLVEPNP_ITERATIVE);

        if (ok)
        {
            Mat R;
            Rodrigues(rvec, R);

            double tx = tvec.at<double>(0);
            double ty = tvec.at<double>(1);
            double tz = tvec.at<double>(2);

            double distance = sqrt(tx * tx + ty * ty + tz * tz);

            double r00 = R.at<double>(0, 0);
            double r10 = R.at<double>(1, 0);
            double r20 = R.at<double>(2, 0);
            double r21 = R.at<double>(2, 1);
            double r22 = R.at<double>(2, 2);

            double yaw = atan2(r10, r00) * 180.0 / CV_PI;
            double pitch = atan2(-r20, sqrt(r21 * r21 + r22 * r22)) * 180.0 / CV_PI;
            double roll = atan2(r21, r22) * 180.0 / CV_PI;

            putText(frame,
                    format("tvec x: %.1f  y: %.1f  z: %.1f", tx, ty, tz),
                    Point(30, 40),
                    FONT_HERSHEY_SIMPLEX,
                    0.8,
                    Color::Yellow,
                    2);

            putText(frame,
                    format("distance: %.1f", distance),
                    Point(30, 75),
                    FONT_HERSHEY_SIMPLEX,
                    0.8,
                    Color::Yellow,
                    2);

            putText(frame,
                    format("rvec: [%.2f, %.2f, %.2f]",
                           rvec.at<double>(0),
                           rvec.at<double>(1),
                           rvec.at<double>(2)),
                    Point(30, 110),
                    FONT_HERSHEY_SIMPLEX,
                    0.8,
                    Color::Yellow,
                    2);

            putText(frame,
                    format("yaw: %.1f  pitch: %.1f  roll: %.1f",
                           yaw, pitch, roll),
                    Point(30, 145),
                    FONT_HERSHEY_SIMPLEX,
                    0.8,
                    Color::Yellow,
                    2);
        }

        imshow("sky", frame);

        int key = waitKey(30);
        if (key == 27)
            break;

        frameCount++;
    }

    destroyAllWindows();

    return 0;
}