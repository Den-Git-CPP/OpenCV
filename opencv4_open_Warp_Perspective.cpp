
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main ()
{
    float w = 250;
    float h = 350;
    cv::Mat matrix, imgWrap;
    // Open Image
    std::string path = "../resources_opencv/img1.png";
    cv::Mat img      = cv::imread (path);
    // обход  трансформируемой фигуры по часовой коодинат по часовой
    cv::Point2f src [4] = {
        {444,  65},
        {527,  65},
        {527, 143},
        {444, 143}
    };

    cv::Point2f dst [4] = {
        {0.0f, 0.0f},
        {   w, 0.0f},
        {0.0f,    h},
        {   w,    h}
    };

    matrix = getPerspectiveTransform (src, dst);
    cv::warpPerspective (img, imgWrap, matrix, cv::Point (w, h));

   // cv::imshow ("Image", img);
    cv::imshow ("Image", imgWrap);
    // Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        exit;
    }

    return 0;
}
