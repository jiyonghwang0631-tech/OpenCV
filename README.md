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

constrast 조절, 곱하기, stretch, equalizeHist 설명 및 실습
연산 함수(add, subtract, addWeighted, absdiff), bitwise 연산 설명 및 실습
회선(convolution) 설명, filter2d, emboss 필터 실습
blur 설명
GaussianBlur, medianBlur 설명 및 실습

## OpenCV 영상 필터링

### 명암비와 히스토그램
- 픽셀값에 값을 곱하면 명암비를 조절할 수 있고, `normalize()`를 이용하면 영상의 밝기 범위를 확장(stretch)할 수 있다.
- `equalizeHist()`는 그레이스케일 영상의 히스토그램을 평활화하여 명암비를 개선한다.

### 산술 연산과 비트 연산
- `add()`, `subtract()`는 영상의 픽셀값을 더하거나 뺀다.
- `addWeighted()`는 두 영상을 가중치에 따라 합성하고, `absdiff()`는 픽셀값 차이의 절댓값을 구한다.
- `bitwise_and()`, `bitwise_or()`, `bitwise_xor()`, `bitwise_not()`은 마스크 처리와 영역 합성에 사용한다.

### 회선과 필터
- 회선(convolution)은 커널을 영상 위에서 이동시키며 주변 픽셀을 계산하는 연산이다.
- `filter2D()`에 커널을 적용하여 엠보싱, 샤프닝 등 다양한 필터를 구현할 수 있다.

### 블러
- 블러는 주변 픽셀값을 이용해 영상을 부드럽게 하고 노이즈를 줄인다.
- `blur()`는 평균값, `GaussianBlur()`는 가우시안 가중 평균, `medianBlur()`는 중앙값을 사용한다.

-------------------------------------------------------------------------------------------------------------------------------------

# 2026 - 6 - 11

perspective 변환 예제 설명
엣지 검출, sobel, canny 설명 및 실습
hough 변환 설명 및 실습 houghLines
houghLinesP 설명 및 실습
threshold, adaptiveThreshold, morphology 설명 및 실습
labeling, polygon 설명 및 실습
page_posit 실습
객체 검출

## OpenCV 특징 검출과 영상 변환

### 원근 변환
- `getPerspectiveTransform()`으로 변환 행렬을 구하고, `warpPerspective()`로 영상을 원하는 사각형 형태로 변환한다.
- 원근 변환과 마스크를 이용해 비행기 영상을 배경에 합성하고 이동, 크기 변화, 회전을 표현한다.
- `solvePnP()`와 `Rodrigues()`를 이용해 객체의 위치, 거리와 회전 방향을 계산한다.

### 엣지와 직선 검출
- `Sobel()`은 영상의 x축과 y축 밝기 변화를 계산하여 엣지를 검출한다.
- `Canny()`는 임계값을 이용해 선명한 엣지를 검출한다.
- `HoughLines()`는 직선을 극좌표로 검출하고, `HoughLinesP()`는 직선의 양 끝점을 검출한다.
- 트랙바로 Canny와 허프 변환의 임계값을 조절하며 검출 결과를 확인한다.

### 색상 분리와 이진화
- `split()`은 컬러 영상을 채널별로 분리하고, `inRange()`는 지정한 색상 범위만 마스크로 추출한다.
- BGR 영상을 HSV로 변환하면 색상, 채도, 밝기를 기준으로 원하는 색을 쉽게 검출할 수 있다.
- `threshold()`는 임계값을 기준으로 영상을 이진화하며, `adaptiveThreshold()`는 영역별 임계값을 적용한다.

### 형태학 연산
- `erode()`는 흰색 영역을 축소하고, `dilate()`는 흰색 영역을 확장한다.
- `morphologyEx()`의 열기와 닫기 연산으로 작은 노이즈를 제거하거나 끊어진 영역을 연결한다.

### 라벨링
- 라벨링은 이진 영상에서 서로 연결된 객체마다 고유한 번호를 부여하는 작업이다.
- `connectedComponents()`는 객체의 개수를 구하고, `connectedComponentsWithStats()`는 각 객체의 위치, 크기, 넓이와 중심점을 구한다.

### 폴리곤 검출
- `findContours()`로 객체의 윤곽선을 찾고, `approxPolyDP()`로 윤곽선을 다각형 형태로 근사한다.
- 근사한 꼭짓점이 3개이면 삼각형, 4개이면 사각형으로 구분하며 원형도를 계산해 원을 검출할 수 있다.
- `boundingRect()`, `minAreaRect()`, `minEnclosingCircle()`을 사용해 객체를 감싸는 사각형과 원을 구한다.

### 객체 검출
- 카메라 영상을 HSV로 변환하고 `inRange()`로 노란색 객체를 추출한다.
- 형태학 연산으로 마스크의 노이즈를 제거한 후 윤곽선의 넓이를 비교해 객체를 검출하고 사각형으로 표시한다.

### 종이 위치와 넓이 측정
- 노란색 테이프의 윤곽선과 네 꼭짓점을 검출하여 실제 크기 기준의 원근 변환 행렬을 구한다.
- 테이프 주변 색상을 기준으로 종이 영역을 추출하고, 윤곽선과 폴리곤으로 종이의 위치를 검출한다.
- 종이 윤곽선을 실제 좌표로 변환한 후 `contourArea()`로 비정형 종이의 넓이를 계산한다.

-------------------------------------------------------------------------------------------------------------------------------------

# 2026-6-12

