
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;
int main ()
{
    // Open Image
    std::string path_shape = "../resources_opencv/DetectColor1.png";
    cv::Mat img_shape = cv::imread (path_shape);




    cv::imshow ("Image_shap", img_shape);
    //  Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        break;
    }

    return 0;
}
