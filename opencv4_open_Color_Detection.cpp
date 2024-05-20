
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main ()
{
    // Open Image
    std::string path = "../resources_opencv/img2.png";
    cv::Mat img      = cv::imread (path);
    // обход  трансформируемой фигуры по часовой коодинат по часовой
     
     
    cv::imshow ("Image", img);
      //  Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        exit;
    }

    return 0;
}
