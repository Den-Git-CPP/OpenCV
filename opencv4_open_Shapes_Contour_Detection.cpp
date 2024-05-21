
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;
int main ()
{
    cv::Mat imgGray, imgBlur, imgCanny, imgDia, imgErode;

    // Open Image
    std::string path_shape = "../resources_opencv/DetectColor1.png";
    cv::Mat img_shape      = cv::imread (path_shape);

    cv::cvtColor (img, imgGray, cv::COLOR_BGRA2GRAY);       // серый
    cv::GaussianBlur (img, imgBlur, cv::Size (5, 5), 5, 0); //
    cv::Canny (imgBlur, imgCanny, 50, 150);                 // контур

    cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (5, 5));
    cv::dilate (imgCanny, imgDia, kernel);

    cv::imshow ("Image_shap", img_shape);
    cv::imshow ("imgGray", img_shape);
    cv::imshow ("imgBlur", img_shape);
    cv::imshow ("imgCanny", img_shape);
    cv::imshow ("imgDia", img_shape);

    //  Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        break;
    }

    return 0;
}
