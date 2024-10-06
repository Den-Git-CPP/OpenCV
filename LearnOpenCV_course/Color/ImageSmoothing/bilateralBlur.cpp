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

    // диаметр пиксельной окрестности, используемой при фильтрации
    int dia = 15;

    // Чем больше значение, тем дальние цвета будут смешаны вместе
    // для создания областей полуравных цветов
    double sigmaColor = 80;

    // Чем больше значение, тем больше влияние более удаленных пикселей
    // пока их цвета достаточно близки
    double sigmaSpace = 80;

    Mat bilateralFiltered;

    // Применить двусторонний фильтр
    bilateralFilter (image, bilateralFiltered, dia, sigmaColor, sigmaSpace);

    imshow ("Original Image", image);
    waitKey (0);
    imshow ("Bilateral Blur Result", bilateralFiltered);
    waitKey (0);

    return 0;
}
