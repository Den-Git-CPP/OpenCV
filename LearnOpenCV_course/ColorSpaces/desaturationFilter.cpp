#include <iostream>
#include "dataPath.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ()
{

    string filename = DATA_PATH + "/images/boy.jpg";
    Mat img         = imread (filename);

    // Укажите коэффициент масштабирования
    float saturationScale = 0.01;

    Mat hsvImage;

    // Преобразовать в цветовое пространство HSV
    cv::cvtColor (img, hsvImage, COLOR_BGR2HSV);

    // Преобразовать в float32
    hsvImage.convertTo (hsvImage, CV_32F);

    vector<Mat> channels (3);

    // Разделить каналы
    split (hsvImage, channels);

    // Умножаем канал S на коэффициент масштабирования
    channels [1] = channels [1] * saturationScale;
    // Операция отсечения выполняется для ограничения значений пикселей
    // между 0 и 255
    min (channels [1], 255, channels [1]);
    max (channels [1], 0, channels [1]);

    // Объединить каналы
    merge (channels, hsvImage);

    // Преобразовать обратно из float32
    hsvImage.convertTo (hsvImage, CV_8UC3);

    Mat imSat;
    // Преобразовать в цветовое пространство BGR
    cv::cvtColor (hsvImage, imSat, COLOR_HSV2BGR);

    imshow ("Original Image", img);
    imshow ("Desaturated Image", imSat);
    waitKey (0);

    return 0;
}
