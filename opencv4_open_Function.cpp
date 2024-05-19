
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main ()
{
    // Open Image
    std::string path = "../resources_opencv/img1.png";
    cv::Mat img      = cv::imread (path);
    cv::Mat imgGray, imgBlur;
    cv::cvtColor (img, imgGray, cv::COLOR_BGRA2GRAY);         // серый
    cv::GaussianBlur (img, imgBlur, cv::Size (5, 5), 5, 0); //
    
    // show
    cv::imshow ("Image", img);
    cv::imshow ("ImageGray", imgGray);
    cv::imshow ("imgBlur", imgBlur);

    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }

    return 0;
}
