#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main (void)
{
    string imagePath = DATA_PATH + "/images/musk.jpg";
    // Прочитать изображение
    Mat img = imread (imagePath);

    cout << "image size = " << img.size ();
    return 0;
}
