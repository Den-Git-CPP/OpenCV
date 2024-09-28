#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main (void)
{
    // Load the Face Image
    string faceImagePath = DATA_PATH + "/images/musk.jpg";

    Mat faceImage = imread (faceImagePath);

    Mat glassBGR = imread (DATA_PATH + "/sunglassRGB.png");
    // Make a copy
    Mat faceWithGlassesNaive = faceImage.clone ();
    Mat roiFace              = faceWithGlassesNaive (Range (150, 250), Range (140, 440));
    // Replace the eye region with the sunglass image
    glassBGR.copyTo (roiFace);

    // imwrite("../results/faceWithGlassesNaive.png", faceWithGlassesNaive);
    imshow ("Face with Glasses Naive", faceWithGlassesNaive);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

    return 0;
}
