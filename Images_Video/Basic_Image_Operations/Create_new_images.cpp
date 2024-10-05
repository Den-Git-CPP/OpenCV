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
    // Read image
    Mat image = imread (DATA_PATH + "/images/boy.jpg");
    imshow ("Input Image", image);

    // Create a new image by copying the already present image
    // using the clone operation
    Mat imageCopy = image.clone ();

    Mat emptyMatrix = Mat (100, 200, CV_8UC3, Scalar (0, 0, 0));
    imwrite (DATA_PATH + "/results/emptyMatrix.png", emptyMatrix);

    imshow ("Empty Matrix", emptyMatrix);

    emptyMatrix.setTo (Scalar (255, 255, 255));
    imwrite (DATA_PATH + "/results/emptyMatrixWhite.png", emptyMatrix);
    imshow ("Empty Matrix White", emptyMatrix);

    Mat emptyOriginal = Mat (emptyMatrix.size (), emptyMatrix.type (), Scalar (100, 100, 100));
    imwrite (DATA_PATH + "/results/emptyMatrix100.png", emptyOriginal);
    imshow ("Empty Original", emptyOriginal);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

    return 0;
}
