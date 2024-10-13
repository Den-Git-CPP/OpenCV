#include <opencv2/opencv.hpp>
#include <iostream>
#include "dataPath.h"

using namespace cv;
using namespace std;

struct userdata {
    Mat im;
    vector<Point2f> points;
};

void mouseHandler (int event, int x, int y, int flags, void* data_ptr)
{
    if (event == EVENT_LBUTTONDOWN) {
        userdata* data = ((userdata*)data_ptr);
        circle (data->im, Point (x, y), 3, Scalar (0, 0, 255), 5, LINE_AA);
        imshow ("Image", data->im);
        if (data->points.size () < 4) {
            data->points.push_back (Point2f (x, y));
        }
    }
}

int main (int argc, char** argv)
{

    // Прочитать исходное изображение.
    Mat im_src = imread (DATA_PATH + "/images/book1.jpg");

    // Изображение назначения. Соотношение сторон книги 3/4
    Size size (300, 400);
    Mat im_dst = Mat::zeros (size, CV_8UC3);

    // Создаем вектор точек назначения.
    vector<Point2f> pts_dst;

    pts_dst.push_back (Point2f (0, 0));
    pts_dst.push_back (Point2f (size.width - 1, 0));
    pts_dst.push_back (Point2f (size.width - 1, size.height - 1));
    pts_dst.push_back (Point2f (0, size.height - 1));

    // Установить данные для события мыши
    Mat im_temp = im_src.clone ();
    userdata data;
    data.im = im_temp;

    cout << "Click on the corners of the book \n in a clockwise direction.\n";

    // Покажите изображение и дождитесь 4 кликов.
    imshow ("Image", im_temp);
    // Устанавливаем функцию обратного вызова для любого события мыши
    setMouseCallback ("Image", mouseHandler, &data);
    waitKey (0);

    // Рассчитать гомографию
    Mat h = findHomography (data.points, pts_dst);

    // Деформировать исходное изображение в целевое
    warpPerspective (im_src, im_dst, h, size);

    // Показать изображение
    imshow ("Image", im_dst);
    waitKey (0);

    return 0;
}
