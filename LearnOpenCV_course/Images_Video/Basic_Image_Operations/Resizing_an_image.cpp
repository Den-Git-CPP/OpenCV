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
    Mat image            = imread (DATA_PATH + "/images/boy.jpg");
    int resizeDownWidth  = 300;
    int resizeDownHeight = 200;
    Mat resizedDown;
    resize (image, resizedDown, Size (resizeDownWidth, resizeDownHeight), INTER_LINEAR);

    // Mess up with the aspect ratio
    int resizeUpWidth  = 600;
    int resizeUpHeight = 900;
    Mat resizedUp;
    resize (image, resizedUp, Size (resizeUpWidth, resizeUpHeight), INTER_LINEAR);

    imwrite (DATA_PATH + "/results/resizedUp.png", resizedUp);
    imwrite (DATA_PATH + "/results/resizedDown.png", resizedDown);
    imshow ("Resized Up", resizedUp);
    imshow ("Resized Down", resizedDown);

    // Scaling Down the image 1.5 times by specifying both scaling factors
    double scaleUpX = 1.5;
    double scaleUpY = 1.5;

    // Scaling Down the image 0.6 times specifying a single scale factor.
    double scaleDown = 0.6;

    Mat scaledUp, scaledDown;

    resize (image, scaledDown, Size (), scaleDown, scaleDown, INTER_LINEAR);

    resize (image, scaledUp, Size (), scaleUpX, scaleUpY, INTER_LINEAR);

    imwrite (DATA_PATH + "/results/scaledUp.png", scaledUp);
    imwrite (DATA_PATH + "/results/scaledDown.png", scaledDown);
    imshow ("Scaled Up", scaledUp);
    imshow ("Scaled Down", scaledDown);

    cout << "Scaled Up Image size = " << scaledUp.size () << endl;
    cout << "Scaled Down Image size = " << scaledDown.size () << endl;
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();
    return 0;
}
