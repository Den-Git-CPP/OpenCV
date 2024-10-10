#include <iostream>
#include "dataPath.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main ()
{
    string filename = DATA_PATH + "/images/truth.png";

    Mat image = imread (filename, IMREAD_GRAYSCALE);

    Mat sobelx, sobely;

    // Применить фильтр Собеля только с градиентом x
    Sobel (image, sobelx, CV_32F, 1, 0);

    // Применить фильтр Собеля только с градиентом по оси Y
    Sobel (image, sobely, CV_32F, 0, 1);

    // Нормализовать изображение для отображения
    normalize (sobelx, sobelx, 0, 1, NORM_MINMAX);
    normalize (sobely, sobely, 0, 1, NORM_MINMAX);

    imshow ("X Gradients", sobelx);
    waitKey (0);
    imshow ("Y Gradients", sobely);
    waitKey (0);

    return 0;
}
