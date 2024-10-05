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
    // Сначала создадим копию исходного изображения
    Mat copiedImage = image.clone ();

    Mat copyRoi = image (Range (40, 200), Range (180, 320));

    // Найти высоту и ширину области ROI
    int roiHeight = copyRoi.size ().height;
    int roiWidth  = copyRoi.size ().width;
    cout << "roiHeight:  " << roiHeight << "\n";
    cout << "roiWidth:  " << roiWidth << "\n";
    // Вставить скопированный регион слева
    copyRoi.copyTo (copiedImage (Range (40, 40 + roiHeight), Range (10, 10 + roiWidth)));
    // Вставить скопированный регион справа
    copyRoi.copyTo (copiedImage (Range (40, 40 + roiHeight), Range (330, 330 + roiWidth)));

    imwrite (DATA_PATH + "/results/copiedRegions.png", copiedImage);

    imshow ("Output Image", copiedImage);

    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

    return 0;
}
