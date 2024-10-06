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
    // Нарисуем круг
    Mat imageCircle = image.clone ();

    circle (imageCircle, Point (250, 125), 100, Scalar (0, 0, 255), 5, LINE_AA);

    imwrite (DATA_PATH + "/results/circle.jpg", imageCircle);
    imshow ("Draw circle on image", imageCircle);

    // Нарисуем заполненный круг
    Mat imageFilledCircle = image.clone ();

    circle (imageFilledCircle, Point (250, 125), 100, Scalar (0, 0, 255), -1, LINE_AA);

    imwrite (DATA_PATH + "/results/filledCircle.jpg", imageFilledCircle);
    imshow ("Filled circle", imageFilledCircle);

    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }

    return 0;
}
