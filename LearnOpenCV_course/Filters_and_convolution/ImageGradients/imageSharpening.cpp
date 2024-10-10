#include <iostream>
#include "dataPath.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
  string filename = DATA_PATH + "/images/sample.jpg";

 
  Mat image = imread(filename);
 //Резкость изображения
  Mat sharpen = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  Mat sharpenOutput;
  filter2D(image, sharpenOutput, -1, sharpen);
  imshow("Original Image", image);
  waitKey(0);
  imshow("Sharpening Result", sharpenOutput);
  waitKey(0);

  return 0;
}
