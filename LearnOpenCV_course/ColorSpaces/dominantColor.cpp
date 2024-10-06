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
    imshow ("Original Image", img);
    waitKey (0);

    // Преобразовать в цветовое пространство HSV
    Mat hsvImage;
    cvtColor (img, hsvImage, COLOR_BGR2HSV);
    // Разделить каналы
    Mat hsvChannels [3];
    split (hsvImage, hsvChannels);
    Mat H = hsvChannels [0], S = hsvChannels [1], V = hsvChannels [2];

    cout << H.size ();

    imshow ("Image", img);
    waitKey (0);

    // Инициализация параметров
    int histSize           = 180; // bin size
    float range []         = { 0, 179 };
    const float* ranges [] = { range };

    // Рассчитать гистограмму
    MatND hist;
    calcHist (&hsvChannels [0], 1, 0, Mat (), hist, 1, &histSize, ranges);

    // Параметры для графика
    int hist_w = histSize * 3;
    int hist_h = 400;
    int bin_w  = cvRound ((double)hist_w / histSize);

    // построить гистограмму как изображение
    Mat histImage (hist_h, hist_w, CV_8UC3, Scalar (255, 255, 255));
    normalize (hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat ());

    // рисуем ось x
    line (histImage, Point (0, hist_h - 30), Point (hist_w, hist_h - 30), Scalar (0, 0, 0), 2, 8, 0);

    // Особый случай указания начала оси x
    line (histImage, Point (0, hist_h - 35), Point (0, hist_h - 25), Scalar (0, 0, 0), 2, 8, 0);
    putText (histImage, "0", Point (0, hist_h - 5), cv::FONT_HERSHEY_COMPLEX, .5, (0, 0, 0), 1, cv::LINE_AA);
    // Рисуем гистограмму
    for (int i = 1; i < histSize; i++) {
        line (histImage, Point (bin_w * (i - 1), hist_h - 30 - cvRound (hist.at<float> (i - 1))),
          Point (bin_w * (i), hist_h - 30 - cvRound (hist.at<float> (i))), Scalar (0, 0, 255), 2, 8, 0);
        // показать значения оси x
        if (i % 20 == 0) {
            char buffer [5];
            sprintf (buffer, "%d", i);
            line (histImage, Point (i * bin_w, hist_h - 35), Point (i * bin_w, hist_h - 25), Scalar (0, 0, 0), 2, 8, 0);
            putText (histImage, buffer, Point (i * bin_w, hist_h - 5), cv::FONT_HERSHEY_COMPLEX, .5, (0, 0, 0), 1, cv::LINE_AA);
        }
    }

    imshow ("Histogram", histImage);
    waitKey (0);

    return 0;
}
