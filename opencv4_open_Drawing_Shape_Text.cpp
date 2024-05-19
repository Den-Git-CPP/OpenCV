
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main ()
{
    // Open blank Image
    cv::Mat img (512, 512, CV_8UC3, cv::Scalar (255, 255, 255));
    // draw circle
    cv::circle (img, cv::Point (50, 50), 25, cv::Scalar (139,0,0));
    cv::circle (img, cv::Point (150, 50), 25, cv::Scalar (139,0,0), 10);
    cv::circle (img, cv::Point (250, 50), 25, cv::Scalar (139,0,0), cv::FILLED);
    // draw rectangle
    cv::rectangle (img, cv::Point (25, 150), cv::Point (125, 100), cv::Scalar (139,0,0));
    cv::rectangle (img, cv::Point (150, 150), cv::Point (250, 100), cv::Scalar (139,0,0),3);
    cv::rectangle (img, cv::Point (275, 150), cv::Point (375, 100), cv::Scalar (139,0,0),cv::FILLED);
     
         // draw line
 cv::line (img, cv::Point (25, 200), cv::Point (400, 200), cv::Scalar (139,0,0));
 // draw text
 cv::putText(img,"Work with text-1",cv::Point (25, 250),cv::FONT_HERSHEY_DUPLEX,0.75,cv::Scalar (139,0,0));
cv::putText(img,"Work with text-2",cv::Point (25, 300),cv::FONT_HERSHEY_DUPLEX,0.75,cv::Scalar (139,0,0),2);

       // Show
    cv::imshow ("Image", img);
    // Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        exit;
    }

    return 0;
}
