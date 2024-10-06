#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
// прочитать изображение в формате BGR
  Mat bgr = imread(DATA_PATH + "/images/DetectColor1.png");

// конвертировать из bgr в формат LAB
  Mat labImage;
  cvtColor(bgr, labImage, COLOR_BGR2Lab);

  vector<Mat> channels(3);
  split(labImage, channels);

  imshow("L Channel", channels[0]);
  imshow("A Channel", channels[1]);
  imshow("B Channel", channels[2]);
  waitKey(0);

  return 0;
}
