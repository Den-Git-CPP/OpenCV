
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void getContures (cv::Mat imgDia, cv::Mat img_shape)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours (imgDia, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    //  cv::drawContours (img_shape, contours, -1, cv::Scalar (255, 0, 255),2);
    // убираем маленькие обьекты
    for (int i{ 0 }; i < contours.size (); i++) {
        int area = cv::contourArea (contours [i]);
        std::cout << area << "\n";

        std::vector<std::vector<cv::Point>> conPoly (contours.size ());
        std::vector<cv::Rect> boundRect (contours.size ());
        std::string ojectType;

        if (area > 1000) {
            float perimetr = cv::arcLength (contours [i], true);
            cv::approxPolyDP (contours [i], conPoly [i], 0.02 * perimetr, true);
            //  cv::drawContours (img_shape, conPoly, i, cv::Scalar (255, 0, 255),2);
            std::cout << conPoly [i].size () << "\n";

            boundRect [i] = cv::boundingRect (conPoly [i]);
            // cv::rectangle(img_shape,boundRect[i].tl(),boundRect[i].br(),cv::Scalar(0,255,0),2);

            int objCor = (int)conPoly [i].size ();

            if (objCor = 3) {
                ojectType = "Tri";
            };
            if (objCor = 4) {
                ojectType      = "Rect";
                float aspRatio = (float)boundRect [i].width / (float)boundRect [i].height;
                if (aspRatio > 0.95 && aspRatio < 1.05) {
                    ojectType = "Square";
                }
                else {
                    ojectType = "Rect";
                }
            };
            if (objCor > 4) {
                ojectType = "Circle";
            };

            // cv::drawContours (img_shape, conPoly, i, cv::Scalar (255, 0, 255), 2);
            cv::rectangle (img_shape, boundRect [i].tl (), boundRect [i].br (), cv::Scalar (0, 255, 0), 2);
            cv::putText (img_shape, ojectType, { boundRect [i].x, boundRect [i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar (139, 0, 0), 2);
        }
    }
};

int main ()
{
    cv::Mat imgGray, imgBlur, imgCanny, imgDia, imgErode;

    // Open Image
    std::string path_shape = "../resources_opencv/DetectColor1.png";
    cv::Mat img_shape      = cv::imread (path_shape);
    // Prepocessing
    cv::cvtColor (img_shape, imgGray, cv::COLOR_BGRA2GRAY);     // серый
    cv::GaussianBlur (imgGray, imgBlur, cv::Size (5, 5), 5, 0); //
    cv::Canny (imgBlur, imgCanny, 50, 150);                     // контур

    cv::Mat kernel = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (5, 5));
    cv::dilate (imgCanny, imgDia, kernel);

    getContures (imgDia, img_shape);

    cv::imshow ("Image_shap", img_shape);
    /*    cv::imshow ("imgGray", imgGray);
        cv::imshow ("imgBlur", imgBlur);
        cv::imshow ("imgCanny", imgCanny);
        cv::imshow ("imgDia", imgDia);
    */

    //  Close
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the show image\n";
        exit;
    }

    return 0;
}
