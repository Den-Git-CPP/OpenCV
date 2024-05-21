
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;
int main ()
{
    // Open Image
    std::string path       = "../resources_opencv/DetectColor.png";
    std::string path_shape = "../resources_opencv/DetectColor1.png";

    cv::Mat imgHSV, imgHSV_shape, mask, mask_shape;
    cv::Mat img       = cv::imread (path);
    cv::Mat img_shape = cv::imread (path_shape);

    cv::cvtColor (img, imgHSV, cv::COLOR_BGR2HSV);
    cv::cvtColor (img_shape, imgHSV_shape, cv::COLOR_BGR2HSV);

    // Трекбары для поиска значений фильтров
    cv::namedWindow ("Trackbars", (640, 200));
    cv::createTrackbar ("Hue Min", "Trackbars", &hmin, 179);
    cv::createTrackbar ("Hue Max", "Trackbars", &hmax, 179);
    cv::createTrackbar ("Sat Min", "Trackbars", &smin, 255);
    cv::createTrackbar ("Sat Max", "Trackbars", &smax, 255);
    cv::createTrackbar ("Val Min", "Trackbars", &vmin, 255);
    cv::createTrackbar ("Val Max", "Trackbars", &vmax, 255);

    while (true) {
        cv::Scalar lower (hmin, smin, vmin);
        cv::Scalar upper (hmax, smax, vmax);
        cv::inRange (imgHSV, lower, upper, mask);
        cv::inRange (imgHSV_shape, lower, upper, mask_shape);

        cv::imshow ("Image", img);
        cv::imshow ("Image_shap", img_shape);
        cv::imshow ("Mask", mask);
        cv::imshow ("Mask_shape", mask_shape);
        cv::imshow ("imgHSV", imgHSV);
        cv::imshow ("imgHSV_shape", imgHSV_shape);

        //  Close
        if (cv::waitKey (0) == 27) {
            std::cout << "Esc key is pressed by user. Stoppig the show image\n";
            break;
        }
    }

    return 0;
}
