
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main ()
{
    // Open Image
    std::string path = "../resources_opencv/DetectColor.png";
    cv::Mat imgHSV, mask;
    int hmin{ 0 }, smin{ 110 }, vmin{ 153 };
    int hmax{ 19 }, smax{ 240 }, vmax{ 255 };
    cv::Mat img = cv::imread (path);
    // обход  трансформируемой фигуры по часовой коодинат по часовой
    cv::cvtColor (img, imgHSV, cv::COLOR_BGR2HSV); // серый
    cv::Scalar lower (hmin, smin, vmin);
    cv::Scalar upper (hmax, smax, vmax);
    cv::inRange (imgHSV, lower, upper, mask);

    cv::imshow ("Image", img);
    cv::imshow ("Mask", mask);
    cv::imshow ("imgHSV", imgHSV);

    //  Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        exit;
    }

    return 0;
}
