#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ()
{
    string filename = DATA_PATH + "/images/dark-flowers.jpg";
    Mat img         = imread (filename);
    Mat imEq        = img.clone ();

    // Выполнить выравнивание гистограммы по каждому каналу отдельно
    vector<Mat> imgChannels (3);
    vector<Mat> imEqChannels (3);

    split (img, imgChannels);
    split (imEq, imEqChannels);

    for (int i = 0; i < 3; i++) {
        equalizeHist (imgChannels [i], imEqChannels [i]);
    }

    merge (imgChannels, img);
    merge (imEqChannels, imEq);

    imshow ("Original Image", img);
    waitKey (0);
    imshow ("Histogram Equalized", imEq);
    waitKey (0);

    filename = DATA_PATH + "/images/dark-flowers.jpg";
    img      = imread (filename);
    Mat imhsv;

    cvtColor (img, imhsv, COLOR_BGR2HSV);

    vector<Mat> imhsvChannels (3);
    split (imhsv, imhsvChannels);

    // Выполнить выравнивание гистограммы только на канале V
    equalizeHist (imhsvChannels [2], imhsvChannels [2]);
    merge (imhsvChannels, imhsv);
    // Конвертировать обратно в формат BGR
    cvtColor (imhsv, imEq, COLOR_HSV2BGR);

    imshow ("Original Image", img);
    waitKey (0);
    imshow ("Histogram Equalized", imEq);
    waitKey (0);

    return 0;
}
