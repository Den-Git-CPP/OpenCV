// Include libraries
#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(void)
{
  // Read image
  Mat image = imread(DATA_PATH + "/images/boy.jpg");

  // Создайте пустое изображение того же размера, что и исходное.
  Mat mask1 = Mat::zeros(image.size(), image.type());
  imwrite(DATA_PATH + "/results/mask1.png", mask1);
  imshow("Mask 1",mask1);
  
  mask1(Range(50, 200), Range(170, 320)).setTo(255);
  imwrite(DATA_PATH + "/results/mask1Revised.png", mask1);
  imshow("Mask 1 Revised",mask1);
  

  Mat mask2;
  inRange(image, Scalar(0, 0, 150), Scalar(100, 100, 255), mask2);
  imwrite(DATA_PATH + "/results/mask2.png", mask2);
  imshow("Mask 2",mask2);

   if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

  return 0;
}
