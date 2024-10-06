#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main (void)
{
    string imagePath = DATA_PATH + "/images/musk.jpg";
    // Прочитать изображение
    Mat img = imread (imagePath);
    // Показать каналы
    Mat imgChannels [3];
    split (img, imgChannels);

    // записываем результаты
    imwrite (DATA_PATH + "/results/imgBlue.png", imgChannels [0]);
    imwrite (DATA_PATH + "/results/imgGreen.png", imgChannels [1]);
    imwrite (DATA_PATH + "/results/imgRed.png", imgChannels [2]);

    imshow ("Blue Channel", imgChannels [0]);
    imshow ("Green Channel", imgChannels [1]);
    imshow ("Red Channel", imgChannels [2]);

    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

    return 0;
}
