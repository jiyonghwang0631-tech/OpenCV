# 2026 - 06 - 08
------------------------------------------------------------------------------------------------------------------------
openCV 소개, 설치 방법 설명
라이브러리 설명
기본 클래스 (Point_, Size_, Rect_ ) 설명
모던 cpp 기법 소개(범위 기반 for문, auto 키워드) 및 예제 설명
inputarray, outputarray 설명
assign 얕은 복사, clone, copyTo 깊은 복사 설명


light spectrum (빛)
 - UV (자외선)
 - VI (가시광선)
 - IR (적외선)

BYTE , uint8(표준) , uchar (그레이스케일 픽셀을 다루는 단위)

0 ~ 255

0 에 가까울수록 어둡다

파일 형식
- 압축의 형식에 따라 다르다. (jpg, bmp, png, gif)

데미안 설치
- sudo apt update
- sudo apt upgrade
- sudo apt install libopencv-dev python3-opencv
- pip install opencv-python

- sudo apt install -y \
   gstreamer1.0-tools \
   gstreamer1.0-plugins-base \
   gstreamer1.0-plugins-good \
   gstreamer1.0-plugins-bad \
   gstreamer1.0-plugins-ugly \
   gstreamer1.0-libav

- sudo apt update
- sudo apt install pkg-config libopencv-dev
- pkg-config --modversion opencv4
- pkg-config --cflags --libs opencv4

소스코드 설치
https://sunkyoo.github.io/opencv4cvml/OpenCV4Linux.html


gst-launch-1.0 v4l2src device=/dev/video0 ! \
  image/jpeg,width=640,height=480,framerate=30/1 ! \
  jpegdec ! videoconvert ! autovideosink sync=false

gst-launch-1.0 v4l2src device=/dev/video0 ! \
  video/x-h264,width=1280,height=720,framerate=30/1 ! \
  h264parse ! avdec_h264 ! videoconvert ! autovideosink sync=false

------------------------------------------------------------------------------------------------------------------------
## OpenCV 간단 정리

### OpenCV 소개
- OpenCV는 이미지, 영상 처리와 컴퓨터 비전 기능을 제공하는 오픈소스 라이브러리이다.
- C++, Python 등에서 사용할 수 있으며 카메라 처리, 객체 검출, 이미지 변환 등에 사용된다.


### 라이브러리 설명
- `opencv_core`: `Mat`, `Point`, `Size`, `Rect` 같은 기본 자료구조 제공
- `opencv_imgcodecs`: 이미지 읽기/쓰기 (`imread`, `imwrite`)
- `opencv_imgproc`: 이미지 처리 (`resize`, `cvtColor`, `rectangle`)
- `opencv_highgui`: 창 출력과 키 입력 (`imshow`, `waitKey`)

### 기본 클래스
- `Point_`: x, y 좌표를 저장한다.
```cpp
Point p(10, 20);
```
- `Size_`: width, height 값을 저장한다.
```cpp
Size sz(640, 480);
```
- `Rect_`: x, y, width, height로 사각형 영역을 표현한다.
```cpp
Rect rc(10, 10, 100, 50);
```

### 모던 C++ 기법
- 범위 기반 for문은 배열이나 vector를 간단히 순회할 때 사용한다.
```cpp
vector<int> nums = {1, 2, 3};
for (int n : nums) {
    cout << n << endl;
}
```
- `auto`는 변수 타입을 컴파일러가 자동으로 추론하게 한다.
```cpp
auto value = 10;
auto name = string("OpenCV");
```

### InputArray, OutputArray
- `InputArray`: OpenCV 함수에서 다양한 입력 타입을 받을 수 있게 해주는 wrapper이다.
- `OutputArray`: 함수 결과를 `Mat` 등에 저장할 수 있게 해주는 wrapper이다.
```cpp
void func(InputArray src, OutputArray dst)
{
    Mat input = src.getMat();
    input.copyTo(dst);
}
```

### 얕은 복사와 깊은 복사
- 대입 연산(`=`)은 얕은 복사이다. 실제 이미지 데이터는 공유된다.
```cpp
Mat img2 = img1;
```
- `clone()`은 깊은 복사이다. 실제 데이터까지 새로 복사한다.
```cpp
Mat img3 = img1.clone();
```
- `copyTo()`도 깊은 복사이다. 대상 Mat에 데이터를 복사한다.
```cpp
Mat img4;
img1.copyTo(img4);
```
