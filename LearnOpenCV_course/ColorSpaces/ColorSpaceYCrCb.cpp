#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
// прочитать изображение в формате BGR
  vector<Mat> channels(3);
  Mat bgr = imread(DATA_PATH + "/mages/DetectColor1.png");
  Mat ycbImage;
  cvtColor(bgr, ycbImage, COLOR_BGR2YCrCb);
  split(ycbImage, channels);

  imshow("Y Channel", channels[0]);
  imshow("Cr Channel", channels[1]);
  imshow("Cb Channel", channels[2]);
  waitKey(0);

  return 0;
}
