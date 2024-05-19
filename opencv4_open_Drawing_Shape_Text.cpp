
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main ()
{
    // Open blank Image
     cv::Mat img(512,512,cv::CV_8UC3,cv::Scalar(255,0,0));


    // Show
    cv::imshow ("Image", img);
    // Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        exit;
    }

    return 0;
}
