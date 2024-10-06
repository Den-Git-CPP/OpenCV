#include <iostream>
#include "dataPath.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main ()
{
    string filename = DATA_PATH + "/images/sample.jpg";
    Mat image       = imread (filename);

    // Определение размера ядра
    int kernelSize = 5;

    Mat medianBlurred;
    // Выполнение медианного размытия и сохранение в массиве numpy "medianBlurred"
    medianBlur (image, medianBlurred, kernelSize);

    imshow ("Original Image", image);
    waitKey (0);
    imshow ("Median Blur Result : KernelSize = 5", medianBlurred);
    waitKey (0);
    return 0;
}
