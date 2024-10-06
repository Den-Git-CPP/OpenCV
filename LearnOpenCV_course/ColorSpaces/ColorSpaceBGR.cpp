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

  imshow("Original Image", bgr);
  waitKey(0);

  Mat bgrChannels[3];
  split(bgr, bgrChannels);

  imshow("Blue Channel", bgrChannels[0]);
  imshow("Green Channel", bgrChannels[1]);
  imshow("Red Channel", bgrChannels[2]);
  waitKey(0);

  return 0;
}
