#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main (void)
{
    string imagePath = DATA_PATH + "/images/number_zero.jpg";

    Mat testImage = imread (imagePath, 0);

    testImage.at<uchar> (0, 0) = 200;

    Mat test_roi = testImage (Range (0, 2), Range (0, 4));
    cout << "Original Matrix\n" << testImage << endl << endl;

    cout << "Selected Region\n" << test_roi;

    testImage (Range (0, 2), Range (0, 4)).setTo (111);

    cout << "Modified Matrix\n" << testImage;

    return 0;
}
