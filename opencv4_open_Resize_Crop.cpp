
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main ()
{
    // Open Image
    std::string path = "../resources_opencv/img1.png";
    cv::Mat img      = cv::imread (path);
    cv::Mat imgResize, imgResizeHalf;
    cv::Mat imgCrop;
    // Resize
    cv::resize (img, imgResize, cv::Size (640, 480));
    cv::resize (img, imgResizeHalf, cv::Size (), 0.5, 0.5);
    // Crop
    cv::Rect roi (100, 100, 300, 250);
    imgCrop = img (roi);

    // show
    std::cout << "Image " << img.size () << "\n";
    std::cout << "imgResize " << imgResize.size () << "\n";
    std::cout << "imgResizeHalf " << imgResizeHalf.size () << "\n";
    std::cout << "imgCrop " << imgCrop.size () << "\n";

    cv::imshow ("Image", img);
    cv::imshow ("ImgResize", imgResize);
    cv::imshow ("imgResizeHalf", imgResizeHalf);
    cv::imshow ("imgCrop", imgCrop);

    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }

    return 0;
}
