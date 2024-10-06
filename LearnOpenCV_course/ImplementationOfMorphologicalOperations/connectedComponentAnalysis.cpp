#include <iostream>
#include "dataPath.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main ()
{
    Mat img = imread (DATA_PATH + "/images/truth.png", IMREAD_GRAYSCALE);
    imshow ("image", img);
    waitKey (0);

    // Пороговое изображение
    Mat imThresh;
    threshold (img, imThresh, 127, 255, THRESH_BINARY);

    // Найти связанные компоненты
    Mat imLabels;
    int nComponents = connectedComponents (imThresh, imLabels);

    Mat imLabelsCopy = imLabels.clone ();

    // Сначала найдем минимальное и максимальное значения в imLabels
    Point minLoc, maxLoc;
    double min, max;

    // Следующая строка находит минимальное и максимальное значения пикселей
    // и их расположение на изображении.
    minMaxLoc (imLabels, &min, &max, &minLoc, &maxLoc);

    // Нормализуем изображение так, чтобы минимальное значение было равно 0, а максимальное — 255.
    imLabels = 255 * (imLabels - min) / (max - min);

    // Преобразовать изображение в 8-битное
    imLabels.convertTo (imLabels, CV_8U);

    imshow ("image", imLabels);
    waitKey (0);
    imLabels = imLabelsCopy.clone ();
    // Display the labels
    cout << "Number of components = " << nComponents;

    for (int i = 0; i < 6; i++) {
        imshow ("image", imLabels == i);
        waitKey (0);
    }

    // Сделать копию изображения
    imLabels = imLabelsCopy.clone ();

    // Сначала давайте найдем минимальное и максимальное значения в imLabels
    // Следующая строка находит минимальное и максимальное значения пикселей
    // и их расположение в изображенииe.
    double minValue, maxValue;
    minMaxLoc (imLabels, &minValue, &maxValue, &minLoc, &maxLoc);

    // Нормализуем изображение так, чтобы минимальное значение было равно 0, а максимальное — 255.
    imLabels = 255 * (imLabels - minValue) / (maxValue - minValue);

    // Преобразовать изображение в 8-битное
    imLabels.convertTo (imLabels, CV_8U);

    // Применить цветовую карту
    Mat imColorMap;
    applyColorMap (imLabels, imColorMap, COLORMAP_JET);

    // Отображение цветных меток
    imshow ("image", imColorMap);
    waitKey (0);

    return 0;
}
