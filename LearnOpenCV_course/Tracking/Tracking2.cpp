/**
https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html
Обнаружить объект
Определить точное положение (координаты x, y) объекта
Провести линию вдоль траектории объекта

*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
  VideoCapture cap("./36OpenCV_BackgroundEstimation.mp4"); // прочитать видео

  if (!cap.isOpened()) {
    cout << "Cannot open the web cam" << endl;
    return -1;
  }

  namedWindow("Control"); // create a window called "Control"

  int iLowH = 170;
  int iHighH = 179;

  int iLowS = 150;
  int iHighS = 255;

  int iLowV = 60;
  int iHighV = 255;

  // Создать трекбары в окне «Управление»
  createTrackbar("LowH", "Control", &iLowH, 179); // Hue (0 - 179)
  createTrackbar("HighH", "Control", &iHighH, 179);

  createTrackbar("LowS", "Control", &iLowS, 255); // Saturation (0 - 255)
  createTrackbar("HighS", "Control", &iHighS, 255);

  createTrackbar("LowV", "Control", &iLowV, 255); // Value (0 - 255)
  createTrackbar("HighV", "Control", &iHighV, 255);

  int iLastX = -1;
  int iLastY = -1;

  // Захват временного изображения с камеры
  Mat imgTmp;
  cap.read(imgTmp);

  // Создаем черное изображение с размером, как на выходе камеры
  Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);

  while (true) {
    Mat imgOriginal;

    bool bSuccess = cap.read(imgOriginal); // считываем новый кадр из видео

    if (!bSuccess) // если не удалось, прерываем цикл
    {
      cout << "Cannot read a frame from video stream" << endl;
      break;
    }

    Mat imgHSV;

    cvtColor(imgOriginal, imgHSV,
             COLOR_BGR2HSV); // Преобразовать захваченный кадр из BGR в HSV

    Mat imgThresholded;

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV),
            imgThresholded); // Порог изображения

    // морфологическое открытие (удаляет мелкие объекты с переднего плана)
    erode(imgThresholded, imgThresholded,
          getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThresholded, imgThresholded,
           getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    // морфологическое закрытие (удаляет небольшие отверстия с переднего плана)
    dilate(imgThresholded, imgThresholded,
           getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThresholded, imgThresholded,
          getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    // Рассчитать моменты порогового изображения
    Moments oMoments = moments(imgThresholded);

    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;

    // если площадь <= 10000, я считаю, что на изображении нет объектов, и это
    // из-за шума, площадь не равна нулю
    if (dArea > 100) {
      // вычислить положение обьекта
      int posX = dM10 / dArea;
      int posY = dM01 / dArea;

      if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0) {
        // Рисуем красную линию от предыдущей точки до текущей точки
        line(imgLines, Point(posX, posY), Point(iLastX, iLastY),
             Scalar(0, 0, 255), 2);
      }

      iLastX = posX;
      iLastY = posY;
    }

    imshow("Thresholded Image",
           imgThresholded); // показать пороговое изображение

    imgOriginal = imgOriginal + imgLines;
    imshow("Original", imgOriginal); // показать исходное изображение

    if (waitKey(30) == 27) // ждать нажатия клавиши 'esc' в течение 30 мс. Если
                           // нажата клавиша 'esc', прерываем цикл
    {
      cout << "esc key is pressed by user" << endl;
      break;
    }
  }

  return 0;
}