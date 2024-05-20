
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main ()
{
    float w = 200;
    float h = 700;
    cv::Mat matrix, imgWrap;
    // Open Image
    std::string path = "../resources_opencv/img2.png";
    cv::Mat img      = cv::imread (path);
    // обход  трансформируемой фигуры по часовой коодинат по часовой
    cv::Point2f src [4] = {
        {407,  20},
        {471,  82},
        {100, 449},
        { 36, 385}
    };

    for (int i{ 0 }; i < 4; i++) {
        cv::circle (img, src [i], 8, cv::Scalar (139, 0, 0), cv::FILLED);
    }
    cv::Point2f dst [4] = {
        {0.0f, 0.0f},
        {   w, 0.0f},
        {   w,    h},
        {0.0f,    h}
    };

    matrix = cv::getPerspectiveTransform (src, dst);
    cv::warpPerspective (img, imgWrap, matrix, cv::Point (w, h));

    cv::imshow ("Image", img);
     cv::imshow ("imgWrap", imgWrap);
    //  Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        exit;
    }

    return 0;
}
