#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ()
{
    string filename = DATA_PATH + "/images/nightsky.jpg";
    Mat img         = imread (filename);
    Mat imhsv;
    cvtColor (img, imhsv, COLOR_BGR2HSV);
    Mat imhsvClahe = imhsv.clone ();
    vector<Mat> imhsvChannels (3);
    split (imhsv, imhsvChannels);
    // Выполнить выравнивание гистограммы только на канале V
    equalizeHist (imhsvChannels [2], imhsvChannels [2]);
    Ptr<CLAHE> clahe = createCLAHE (2.0, Size (8, 8));

    vector<Mat> imhsvClaheChannels (3);
    split (imhsvClahe, imhsvClaheChannels);

    clahe->apply (imhsvClaheChannels [2], imhsvClaheChannels [2]);

    merge (imhsvChannels, imhsv);
    merge (imhsvClaheChannels, imhsvClahe);
    Mat imEq, imEqCLAHE;
    // Конвертировать обратно в формат BGR
    cvtColor (imhsv, imEq, COLOR_HSV2BGR);
    cvtColor (imhsvClahe, imEqCLAHE, COLOR_HSV2BGR);

    imshow ("Original Image", img);
    waitKey (0);
    imshow ("Histogram Equalized", imEq);
    waitKey (0);
    imshow ("CLAHE", imEqCLAHE);
    waitKey (0);

    return 0;
}
