# 2026 - 06 - 08
--------------------------------------------------------------
 opencv 시작

1장

light spectrum (빛)
 - UV (자외선)
 - VI (가시광선)
 - IR (적외선)


BYTE , uint8(표준) , uchar (그레이스케일 픽셀을 다루는 단위)

0 ~ 255

0 에 가까울수록 어둡다

파일 형식
- 압축의 형식에 따라 다르다. (jpg, bmp, png, gif)

2장
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

4장 
Open CV 소개

이동연산자 &&