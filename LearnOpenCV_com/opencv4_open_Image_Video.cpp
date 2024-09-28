
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//////Open Image
int main ()
{
    // Open Image
    std::string path = "../resources_opencv/img1.png";
    cv::Mat img      = cv::imread (path);
    cv::imshow ("Image", img);

    // Open Video
    std::string path_video = "../resources_opencv/36OpenCV_BackgroundEstimation.mp4";
    cv::VideoCapture capture_video (path_video);
    cv::Mat img_vid;

    while (true) {
        capture_video.read (img_vid);
        cv::imshow ("Video", img_vid);
        if (cv::waitKey (10) == 27) {
            std::cout << "Esc key is pressed by user. Stoppig the video\n" ;
            break;
        }
    }

    return 0;
}
