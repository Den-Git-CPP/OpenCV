#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Piecewise Linear interpolation implemented on a particular Channel
void interpolation (uchar* lut, float* fullRange, float* Curve, float* originalValue)
{
    int i;
    for (i = 0; i < 256; i++) {
        int j   = 0;
        float a = fullRange [i];
        while (a > originalValue [j]) {
            j++;
        }
        if (a == originalValue [j]) {
            lut [i] = Curve [j];
            continue;
        }
        float slope    = ((float)(Curve [j] - Curve [j - 1])) / (originalValue [j] - originalValue [j - 1]);
        float constant = Curve [j] - slope * originalValue [j];
        lut [i]        = slope * fullRange [i] + constant;
    }
}

int main ()
{
    // Прочитать изображение
    string filename = DATA_PATH + "/images/boy.jpg";
    Mat Image       = imread (filename);

    // Точки поворота для X-координат
    float originalValue [] = { 0, 50, 100, 150, 200, 255 };

    // Изменены точки на оси Y для каждого канала
    float rCurve [] = { 0, 80, 150, 190, 220, 255 };
    float bCurve [] = { 0, 20, 40, 75, 150, 255 };

    // Разделение каналов
    vector<Mat> channels (3);
    split (Image, channels);

    // Создать таблицу поиска
    float fullRange [256];
    int i;
    for (i = 0; i < 256; i++) {
        fullRange [i] = (float)i;
    }
    Mat lookUpTable (1, 256, CV_8U);
    uchar* lut = lookUpTable.ptr ();

    // Применить интерполяцию и создать таблицу поиска
    interpolation (lut, fullRange, rCurve, originalValue);

    // Применить сопоставление и проверить переполнение/недополнение в красном канале
    LUT (channels [2], lookUpTable, channels [2]);
    min (channels [2], 255, channels [2]);
    max (channels [2], 0, channels [2]);

    // Применить интерполяцию и создать таблицу поиска
    interpolation (lut, fullRange, bCurve, originalValue);

    // Применить сопоставление и проверить переполнение/недополнение в синем канале
    LUT (channels [0], lookUpTable, channels [0]);
    min (channels [0], 255, channels [0]);
    max (channels [0], 0, channels [0]);

    Mat output;
    // Объединить каналы
    merge (channels, output);

    // Отображение изображений
    Mat combined;
    cv::hconcat (Image, output, combined);

    imshow ("Warming Filter Output", combined);
    waitKey (0);

    return 0;
}
