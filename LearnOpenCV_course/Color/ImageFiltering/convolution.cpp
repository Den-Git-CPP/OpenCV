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

    if (image.empty ()) {
        cout << "Could not read image" << endl;
    }
    // Установить размер ядра 5
    int kernelSize = 5;

    // Создаем ядро ​​5x5 со всеми элементами, равными 1
    Mat kernel = Mat::ones (kernelSize, kernelSize, CV_32F);

    // Нормализуем ядро ​​так, чтобы сумма всех элементов была равна 1
    kernel = kernel / (float)(kernelSize * kernelSize);

    // Печать ядра
    cout << kernel << endl;

    // Выходное изображение
    Mat result;

    // Применить фильтр
    filter2D (image, result, -1, kernel, Point (-1, -1), 0, BORDER_DEFAULT);

    imshow ("Original Image", image);
    waitKey (0);
    imshow ("Convolution Result", result);
    waitKey (0);

    return 0;
}
