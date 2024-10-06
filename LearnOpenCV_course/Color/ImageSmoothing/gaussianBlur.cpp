#include <iostream>
#include "dataPath.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main ()
{
    string filename = DATA_PATH + "/images/sample.jpg";
    Mat image       = imread (filename);

    Mat dst1, dst2;

    // Применить гауссовский фильтр
    GaussianBlur (image, dst1, Size (5, 5), 0, 0);

    // Увеличенная сигма
    GaussianBlur (image, dst2, Size (25, 25), 50, 50);

    imshow ("Original Image", image);
    waitKey (0);
    imshow ("Gaussian Blur Result 1 : KernelSize = 5", dst1);
    waitKey (0);
    imshow ("Gaussian Blur Result 2 : KernelSize = 25", dst2);
    waitKey (0);

    return 0;
}
