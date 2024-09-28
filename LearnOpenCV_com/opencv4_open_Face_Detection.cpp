
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

//////Open Image
int main ()
{
    // Open Image
    std::string path = "../resources_opencv/FaceDetection.png";
    cv::Mat img      = cv::imread (path);

    cv::CascadeClassifier faceCascade;
    faceCascade.load ("../resources_opencv/haarcascade_frontalface_default.xml");
    if (faceCascade.empty ()) {
        std::cout << "XML file not found\n";
        exit;
    }
    std::vector<cv::Rect> faces;

    faceCascade.detectMultiScale (img, faces, 1.1, 10);

    for (int i{ 0 }; i < faces.size (); i++) {
        cv::rectangle (img, faces [i].tl (), faces [i].br (), cv::Scalar (139, 0, 0), 3);
    }
    cv::imshow ("Image", img);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the video\n";
        exit;
    }

    return 0;
}
