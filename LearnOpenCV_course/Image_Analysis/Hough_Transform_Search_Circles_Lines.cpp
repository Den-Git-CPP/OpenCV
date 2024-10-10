#include <opencv2/opencv.hpp>
#include <iostream>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main()
{
 // Считать изображение как полутоновое
  Mat img = imread(DATA_PATH + "/images/lanes.jpg", IMREAD_COLOR);
// Преобразуем изображение в оттенки серого
  Mat gray;
  cvtColor(img, gray, COLOR_BGR2GRAY);
// Найдите края на изображении с помощью детектора Canny
  Mat edges;
  Canny(gray, edges, 50, 200);
// Обнаружение точек, образующих линию
  vector<Vec4i> lines;
  HoughLinesP(edges, lines, 1, CV_PI / 180, 100, 10, 250);
// Нарисуйте линии на изображении
  for (size_t i = 0; i < lines.size(); i++) {
    Vec4i line = lines[i];
    cv::line(img, Point(line[0], line[1]), Point(line[2], line[3]), Scalar(255, 0, 0), 3, LINE_AA);
  }
  imshow("Hough Lines", img);
  waitKey(0);

// Считать изображение как полутоновое
  img = imread(DATA_PATH + "/images/circles.jpg", IMREAD_COLOR);
// Преобразуем изображение в оттенки серого
  cvtColor(img, gray, COLOR_BGR2GRAY);

// Размыть изображение, чтобы уменьшить шум
  Mat img_blur;
  medianBlur(gray, img_blur, 5);
// Применить преобразование Хафа к изображению
  vector<Vec3f> circles;
  HoughCircles(img_blur, circles, HOUGH_GRADIENT, 1, 50, 450, 10, 30, 40);
  for (size_t i = 0; i < circles.size(); i++) {
    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);
 // Нарисуем внешний круг
    circle(img, center, radius, Scalar(0, 255, 0), 2);
// Нарисуем центр круга
    circle(img, center, 2, Scalar(0, 0, 255), 3);
  }

  imshow("Hough Circles", img);
  waitKey(0);

  return 0;
}
