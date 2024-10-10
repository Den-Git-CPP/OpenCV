#include <iostream>
#include "dataPath.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main ()
{
    string filename = DATA_PATH + "/images/sample.jpg";

    Mat image = imread (filename, IMREAD_GRAYSCALE);

    Mat laplacian, LOG;
    int kernelSize = 3;

    // Применение лапласиана
    Laplacian (image, laplacian, CV_32F, kernelSize, 1, 0);

    Mat img1;

    GaussianBlur (image, img1, Size (3, 3), 0, 0);

    // Нормализовать изображения
    normalize (laplacian, laplacian, 0, 1, NORM_MINMAX, CV_32F);

    imshow ("Laplacian", laplacian);
    waitKey (0);

    return 0;
}
