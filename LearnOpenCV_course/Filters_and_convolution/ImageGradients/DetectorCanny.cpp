#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Переменные для исходных и краевых изображений
Mat src, edges;

// Переменные для нижнего и верхнего порогов
int lowThreshold  = 50;
int highThreshold = 100;

// Максимальное значение трекбара
int const maxThreshold = 1000;

// Размеры апертуры Собеля для детектора краев Кэнни
int apertureSizes [] = { 3, 5, 7 };
int maxapertureIndex = 2;
int apertureIndex    = 0;

// Размер размытия по Гауссу
int blurAmount    = 0;
int maxBlurAmount = 20;

// Функция для вызова трекбара
void applyCanny (int, void*)
{
    // Переменная для хранения размытого изображения
    Mat blurredSrc;

    // Размываем изображение перед обнаружением краев
    if (blurAmount > 0) {
        GaussianBlur (src, blurredSrc, Size (2 * blurAmount + 1, 2 * blurAmount + 1), 0);
    }
    else {
        blurredSrc = src.clone ();
    }

    // Canny требует, чтобы размер апертуры был нечетным
    int apertureSize = apertureSizes [apertureIndex];

    // Применяем canny, чтобы получить края
    Canny (blurredSrc, edges, lowThreshold, highThreshold, apertureSize);

    // Отображение изображений
    imshow ("Edges", edges);
}

int main ()
{

    src = imread (DATA_PATH + "/images/sample.jpg", IMREAD_GRAYSCALE);

    // Отображение изображений
    imshow ("Edges", src);

    // Создаем окно для отображения вывода.
    namedWindow ("Edges", WINDOW_AUTOSIZE);

    // Трекбар для управления нижним порогом
    createTrackbar ("Low Threshold", "Edges", &lowThreshold, maxThreshold, applyCanny);
    // Трекбар для управления высоким порогом
    createTrackbar ("High Threshold", "Edges", &highThreshold, maxThreshold, applyCanny);

    // Полоса прокрутки для управления размером апертуры
    createTrackbar ("aperture Size", "Edges", &apertureIndex, maxapertureIndex, applyCanny);

    // Полоса прокрутки для управления размытием
    createTrackbar ("Blur", "Edges", &blurAmount, maxBlurAmount, applyCanny);

    waitKey (0);

    destroyAllWindows ();
}
