// Include libraries
#include <iostream>
#include "dataPath.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main (void)
{

    // Путь к изображению, которое мы собираемся прочитать
    // Это может быть абсолютный или относительный путь
    // Здесь мы используем относительный путь
    string imageName = DATA_PATH + "/images/boy.jpg";

    // Загрузить изображение
    Mat image;
    image = imread (imageName, IMREAD_COLOR);

    // Нарисуйте эллипс
    // Примечание: Центры эллипса и длины осей должны быть целыми числами
    Mat imageEllipse = image.clone ();

    ellipse (imageEllipse, Point (250, 125), Point (100, 50), 0, 0, 360, Scalar (255, 0, 0), 3, LINE_AA);

    ellipse (imageEllipse, Point (250, 125), Point (100, 50), 90, 0, 360, Scalar (0, 0, 255), 3, LINE_AA);

    imwrite (DATA_PATH + "/results/ellipse.jpg", imageEllipse);
    imshow ("Draw ellipse on image", imageEllipse);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user.\n";
        exit;
    }

    // Нарисуйте эллипс
    // Примечание: Центры эллипса и длины осей должны быть целыми числами
    imageEllipse = image.clone ();

    // Неполный/Открытый эллипс
    ellipse (imageEllipse, Point (250, 125), Point (100, 50), 0, 180, 360, Scalar (255, 0, 0), 3, LINE_AA);

    // Заполненный эллипс
    ellipse (imageEllipse, Point (250, 125), Point (100, 50), 0, 0, 180, Scalar (0, 0, 255), -2, LINE_AA);

    imwrite (DATA_PATH + "/results/ellipseFilled.jpg", imageEllipse);

    imshow ("Draw filled ellipse", imageEllipse);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user.\n";
        exit;
    }
    return 0;
}
