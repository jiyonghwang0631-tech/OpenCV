// wget https://huggingface.co/camenduru/openpose/resolve/5e17f6ad43ab415a0114537541a8d37d2503424f/models/hand/pose_iter_102000.caffemodel

#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace cv::dnn;

const int POSE_PAIRS[20][2] =
    {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, // thumb
        {0, 5},
        {5, 6},
        {6, 7},
        {7, 8}, // index
        {0, 9},
        {9, 10},
        {10, 11},
        {11, 12}, // middle
        {0, 13},
        {13, 14},
        {14, 15},
        {15, 16}, // ring
        {0, 17},
        {17, 18},
        {18, 19},
        {19, 20} // small
};

const String folderPath =
    "/home/korea_hrd_1_2/OpenCV/OpenCV/Example/part6/classify/YOLOx/";

string protoFile = folderPath + "pose_deploy.prototxt";
string weightsFile = folderPath + "pose_iter_102000.caffemodel";

int nPoints = 22;

int main(int argc, char **argv)
{
    float thresh = 0.01;

    VideoCapture cap(0, CAP_V4L2);

    cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 30);

    if (!cap.isOpened())
    {
        cerr << "Unable to connect to camera" << endl;
        return 1;
    }

    Mat frame;
    int frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    float aspect_ratio = frameWidth / (float)frameHeight;
    int inHeight = 184;
    int inWidth = (int(aspect_ratio * inHeight) * 8) / 8;

    cout << "inWidth = " << inWidth << " ; inHeight = " << inHeight << endl;

    Net net = readNetFromCaffe(protoFile, weightsFile);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);

    vector<Point> points(nPoints, Point(-1, -1));
    const int inferenceInterval = 2;
    int frameCount = 0;
    double inferenceTime = 0.0;

    while (1)
    {
        if (!cap.read(frame) || frame.empty())
        {
            cerr << "Unable to read camera frame" << endl;
            break;
        }

        if (frameCount % inferenceInterval == 0)
        {
            int64 startTick = getTickCount();
            Mat inpBlob = blobFromImage(
                frame,
                1.0 / 255,
                Size(inWidth, inHeight),
                Scalar(),
                false,
                false);

            net.setInput(inpBlob);
            Mat output = net.forward();

            int H = output.size[2];
            int W = output.size[3];

            fill(points.begin(), points.end(), Point(-1, -1));
            for (int n = 0; n < nPoints; n++)
            {
                Mat probMap(H, W, CV_32F, output.ptr(0, n));
                Point maxLoc;
                double prob;
                minMaxLoc(probMap, nullptr, &prob, nullptr, &maxLoc);

                if (prob > thresh)
                {
                    points[n] = Point(
                        cvRound(maxLoc.x * frameWidth / static_cast<double>(W)),
                        cvRound(maxLoc.y * frameHeight / static_cast<double>(H)));
                }
            }

            inferenceTime =
                (getTickCount() - startTick) / getTickFrequency();
        }

        int nPairs = sizeof(POSE_PAIRS) / sizeof(POSE_PAIRS[0]);

        for (int n = 0; n < nPairs; n++)
        {
            // lookup 2 connected body/hand parts
            Point partA = points[POSE_PAIRS[n][0]];
            Point partB = points[POSE_PAIRS[n][1]];

            if (partA.x <= 0 || partA.y <= 0 || partB.x <= 0 || partB.y <= 0)
                continue;

            line(frame, partA, partB, Scalar(0, 255, 255), 3, LINE_AA);
            circle(frame, partA, 4, Scalar(0, 0, 255), -1, LINE_AA);
            circle(frame, partB, 4, Scalar(0, 0, 255), -1, LINE_AA);
        }

        putText(
            frame,
            format("inference: %.0f ms", inferenceTime * 1000.0),
            Point(20, 35),
            FONT_HERSHEY_SIMPLEX,
            0.7,
            Scalar(0, 255, 0),
            2,
            LINE_AA);

        imshow("Output-Skeleton", frame);
        ++frameCount;

        char key = waitKey(1);
        if (key == 27)
            break;
    }
    cap.release();
    destroyAllWindows();

    return 0;
}
