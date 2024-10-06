#include <iostream>
#include "dataPath.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main ()
{

    string imageName = DATA_PATH + "/images/opening.png";
    Mat image        = imread (imageName, IMREAD_GRAYSCALE);
    imshow ("image", image);
    waitKey (0);

    // Укажите размер ядра
    int kernelSize = 10;

    // Создаем ядро
    Mat element = getStructuringElement (MORPH_ELLIPSE, Size (2 * kernelSize + 1, 2 * kernelSize + 1), Point (kernelSize, kernelSize));

    imshow ("image", 255 * element);
    waitKey (0);

    Mat imEroded;
    // Выполнить дилатацию
    erode (image, imEroded, element, Point (-1, -1), 1);

    imshow ("image", 255 * imEroded);
    waitKey (0);

    Mat imOpen;
    dilate (imEroded, imOpen, element, Point (-1, -1), 1);

    imshow ("image", 255 * imOpen);
    waitKey (0);

    // Получить структурный элемент/ядро, которое будет использоваться
    // для операции открытия
    int openingSize = 3;
    // Выбор эллиптического ядраl
    element = getStructuringElement (MORPH_ELLIPSE, Size (2 * openingSize + 1, 2 * openingSize + 1), Point (openingSize, openingSize));

    Mat imageMorphOpened;
    morphologyEx (image, imageMorphOpened, MORPH_OPEN, element, Point (-1, -1), 3);
    imshow ("image", imageMorphOpened * 255);
    waitKey (0);

    imageName = DATA_PATH + "/images/closing.png";
    // Изображение взято в качестве входных данных
    image = imread (imageName, IMREAD_GRAYSCALE);

    // Укажите размер ядра
    kernelSize = 10;
    // Create kernel
    element = getStructuringElement (MORPH_ELLIPSE, Size (2 * kernelSize + 1, 2 * kernelSize + 1), Point (kernelSize, kernelSize));

    Mat imDilated;
    // Выполнить дилатацию
    dilate (image, imDilated, element);

    imshow ("image", imDilated);
    waitKey (0);

    Mat imClose;
    // Выполнить эрозию
    erode (imDilated, imClose, element);

    imshow ("image", imClose);
    waitKey (0);

    // Создать структурирующий элемент
    int closingSize = 10;
    // Выбор эллиптического ядра и сохранение в элементе Mat
    element = getStructuringElement (MORPH_ELLIPSE, Size (2 * closingSize + 1, 2 * closingSize + 1), Point (closingSize, closingSize));

    Mat imageMorphClosed;
    morphologyEx (image, imageMorphClosed, MORPH_CLOSE, element);
    imshow ("image", imageMorphClosed);
    waitKey (0);

    destroyAllWindows ();

    return 0;
}
