# 2026 - 06 - 08
------------------------------------------------------------------------------------------------------------------------
openCV 소개, 설치 방법 설명
라이브러리 설명
기본 클래스 (Point_, Size_, Rect_ ) 설명
모던 cpp 기법 소개(범위 기반 for문, auto 키워드) 및 예제 설명
inputarray, outputarray 설명
assign 얕은 복사, clone, copyTo 깊은 복사 설명
gstream 예제 설명, gstreamer 설치 방법 설명
카메라 세팅(usbipd)

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

### GStreamer
- 영상과 오디오를 처리하는 멀티미디어 프레임워크이다.
- OpenCV에서 카메라 및 영상 스트림을 입력받거나 출력할 때 사용할 수 있으며, 관련 패키지를 설치한 후 파이프라인으로 연동한다.

------------------------------------------------------------------------------------------------------------------------

# 2026 - 06 - 09


복습
비디오 저장 코드
도형 그리기 (line, rectangle, circle, ellipse) 설명 및 AI 실습
putText, freetype2 설명 및 실습
keyboard event, TickMeter, getTickCount 설명 및 실습
mouse event 설명 및 실습, example 실습
trackbar 설명 및 실습, filestorage 설명 및 실습
마스크 활용 설명 및 실습, example 실습

## OpenCV 영상 처리와 이벤트

### 비디오 저장
- `VideoWriter`는 카메라에서 받은 프레임을 동영상 파일로 저장한다.
- 코덱, FPS, 영상 크기를 지정한 후 프레임을 순서대로 기록한다.
```cpp
int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
VideoWriter outVideo("output.avi", fourcc, 30.0, Size(640, 480));
outVideo << frame;
```

### 도형 그리기
- `line`, `rectangle`, `circle`, `ellipse`를 이용해 이미지 위에 도형을 그릴 수 있다.
```cpp
line(img, Point(50, 50), Point(200, 100), Color::Blue, 3);
rectangle(img, Rect(250, 50, 100, 60), Color::Red, 2);
circle(img, Point(350, 150), 20, Color::Yellow, 2);
ellipse(img, Point(500, 100), Size(60, 30), 0, 0, 360, Color::Cyan, 2);
```

### 문자 출력
- `putText()`는 영문과 숫자를 이미지 위에 출력한다.
- 한글을 출력하려면 OpenCV FreeType2 모듈과 한글 폰트 파일이 필요하다.
```cpp
putText(img, "OpenCV", Point(20, 50),
        FONT_HERSHEY_SIMPLEX, 1, Color::Red, 2);
```

### 키보드 이벤트
- `waitKey()`의 반환값으로 눌린 키를 확인할 수 있다.
- `ESC` 키의 코드는 27이며, 영문 키는 문자로 비교할 수 있다.
```cpp
int key = waitKey(30);
if (key == 27)
    break;
if (key == 'v' || key == 'V')
    img = ~img;
```

### 실행 시간 측정
- `getTickCount()`와 `getTickFrequency()`를 이용해 코드 실행 시간을 계산한다.
- `TickMeter`를 사용하면 시간을 더 간단하게 측정할 수 있다.
```cpp
TickMeter tm;
tm.start();
// 측정할 코드
tm.stop();
cout << tm.getTimeMilli() << " ms" << endl;
```

### 마우스 이벤트
- `setMouseCallback()`으로 클릭, 이동, 드래그 등의 마우스 이벤트를 처리한다.
```cpp
setMouseCallback("img", onMouse, &img);

void onMouse(int event, int x, int y, int flags, void *data)
{
    if (event == EVENT_LBUTTONDOWN)
        cout << x << ", " << y << endl;
}
```

### 트랙바
- `createTrackbar()`는 슬라이더를 생성하며 값이 변할 때 콜백 함수를 호출한다.
```cpp
int value = 0;
createTrackbar("level", "img", &value, 255, onChange, &img);
```

### FileStorage
- `FileStorage`를 이용해 숫자, 문자열, 벡터, 행렬 등을 XML 또는 YAML 파일로 저장하고 불러온다.
```cpp
FileStorage fs("mydata.xml", FileStorage::WRITE);
fs << "name" << "OpenCV";
fs << "data" << mat;
fs.release();
```

### 마스크 활용
- 마스크는 특정 영역만 선택하여 색상을 변경하거나 이미지를 합성할 때 사용한다.
- 마스크 영상은 일반적으로 선택 영역이 255, 나머지 영역이 0인 그레이스케일 영상이다.
```cpp
img.setTo(Color::Yellow, mask);
source.copyTo(destination, mask);
```
------------------------------------------------------------------------------------------------------------------------

# 2026-06-10