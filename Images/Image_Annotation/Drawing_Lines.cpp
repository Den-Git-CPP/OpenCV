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
    image = imread (imageName,IMREAD_COLOR);
    // Нарисовать линию
    Mat imageLine = image.clone ();

    // Линия начинается с (322,179) и заканчивается в (400,183)
    // Цвет линии КРАСНЫЙ (напомним, что OpenCV использует формат BGR)
    // Толщина линии 5 пикселей
    // Тип линии LINE_AA

    line (imageLine, Point (200, 80), Point (280, 80), Scalar (0, 255, 0), 3, LINE_AA);

    imwrite (DATA_PATH + "/results/line.jpg", imageLine);

    imshow ("Image line", imageLine);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

    return 0;
}
