// Include libraries
#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main (void)
{
    // Прочитать изображение
    Mat image = imread (DATA_PATH + "/images/boy.jpg");
    // Вырезать прямоугольник
    // x координаты = 170 to 320
    // y координаты = 40 to 200
    Mat crop = image (Range (40, 200), Range (170, 320));
    imwrite (DATA_PATH + "/results/crop.png", crop);

    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();
    return 0;
}
