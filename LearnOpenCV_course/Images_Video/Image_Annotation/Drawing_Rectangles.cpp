// Include libraries
#include <iostream>
#include "dataPath.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main (void)
{

    string imageName = DATA_PATH + "/images/boy.jpg";

    Mat image;
    image = imread (imageName, IMREAD_COLOR);

    // Нарисуйте прямоугольник (толщина — положительное целое число)
    Mat imageRectangle = image.clone ();
    rectangle (imageRectangle, Point (170, 50), Point (300, 200), Scalar (255, 0, 255), 5, LINE_8);

    imwrite (DATA_PATH + "/results/rectangle.jpg", imageRectangle);

    imshow ("Draw rectangle on image", imageRectangle);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

    return 0;
}
