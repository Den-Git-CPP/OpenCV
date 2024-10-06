#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main ()
{
    // прочитать изображение в формате BGR
    Mat bgr = imread (DATA_PATH + "/images/DetectColor1.png");

    // конвертировать из формата BGR в HSV
    Mat hsvImage;
    cvtColor (bgr, hsvImage, COLOR_BGR2HSV);

    Mat hsvChannels [3];
    split (hsvImage, hsvChannels);

    imshow ("Hue", hsvChannels [0]);
    imshow ("Saturation", hsvChannels [1]);
    imshow ("Value", hsvChannels [2]);
    waitKey (0);

    Mat imH, imS, imV, imhsv, imbgr;
    vector<Mat> channels;

    for (int i = 0; i < 7; i++) {
        // Создать 50x50 каналов HSV
        // Установить оттенок = 0, насыщенность = 0, значение = i x 40
        imH = Mat::zeros (Size (50, 50), CV_8U);
        imS = Mat::zeros (Size (50, 50), CV_8U);
        imV = Mat::ones (Size (50, 50), CV_8U) * (i * 40);

        channels = { imH, imS, imV };

        merge (channels, imhsv);

        // Конвертировать HSV в BGR
        cvtColor (imhsv, imbgr, COLOR_HSV2BGR);

        // Показать рисунок
        imshow ("V=" + to_string (i * 40), imbgr);
        waitKey (0);
    }

    for (int i = 0; i < 7; i++) {
        // Создать 50x50 каналов HSV
        // Установить оттенок = 0, значение = 128
        imH = Mat::zeros (Size (50, 50), CV_8U);
        imS = Mat::ones (Size (50, 50), CV_8U) * (i * 40);
        imV = Mat::ones (Size (50, 50), CV_8U) * 128;

        channels = { imH, imS, imV };

        merge (channels, imhsv);

        // Конвертировать HSV в BGR
        cvtColor (imhsv, imbgr, COLOR_HSV2BGR);

        // Показать рисунок
        imshow ("S=" + to_string (i * 40), imbgr);
        waitKey (0);
    }

    for (int i = 0; i < 7; i++) {
        // Создать 50x50 каналов HSV
        // Установить Насыщенность = 128, Значение = 128
        imH = Mat::ones (Size (50, 50), CV_8U) * (i * 30);
        imS = Mat::ones (Size (50, 50), CV_8U) * 128;
        imV = Mat::ones (Size (50, 50), CV_8U) * 128;

        channels = { imH, imS, imV };

        merge (channels, imhsv);

        // Конвертировать HSV в BGR
        cvtColor (imhsv, imbgr, COLOR_HSV2BGR);

        // Показать рисунок
        imshow ("H=" + to_string (i * 40), imbgr);
        waitKey (0);
    }

    return 0;
}
