
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//////Open Image
int main ()
{

    // Open WebCamera
    cv::VideoCapture capture_webcam (0); // WebCamera
    cv::Mat img_cam;

    while (true) {
        capture_webcam.read (img_cam);
        cv::imshow ("WebCamera", img_cam);
        if (cv::waitKey (10) == 27) {
            std::cout << "Esc key is pressed by user. Stoppig the WebCamera\n";
            break;
        }
    }

    return 0;
}
