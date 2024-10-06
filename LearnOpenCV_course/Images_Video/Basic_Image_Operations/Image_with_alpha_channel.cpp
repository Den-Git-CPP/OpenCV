#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main (void)
{
    string imagePath = DATA_PATH + "/images/panther.png";

    // Прочитать изображение
    // Обратите внимание, что мы передаем флаг = -1 при чтении изображения (он прочитает изображение как есть)
    Mat imgPNG = imread (imagePath, -1);
    cout << "image size = " << imgPNG.size () << endl;
    cout << "number of channels = " << imgPNG.channels () << endl;

    Mat imgBGR;
    Mat imgPNGChannels [4];
    split (imgPNG, imgPNGChannels);

    merge (imgPNGChannels, 3, imgBGR);

    Mat imgMask = imgPNGChannels [3];

    imshow ("Color Channels", imgBGR);
    imshow ("Alpha Channel", imgMask);
   
    imwrite (DATA_PATH + "/results/colorChannels.png", imgBGR);
    imwrite (DATA_PATH + "/results/alphaChannel.png", imgMask);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();
    return 0;
}
