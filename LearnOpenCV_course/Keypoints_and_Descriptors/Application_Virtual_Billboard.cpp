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
        circle (data->im, Point (x, y), 3, Scalar (0, 255, 255), 5, LINE_AA);
        imshow ("Image", data->im);
        if (data->points.size () < 4) {
            data->points.push_back (Point2f (x, y));
        }
    }
}

int main (int argc, char** argv)
{ // Читаем изображение
    Mat im_src = imread (DATA_PATH + "/images/first-image.jpg");
    Size size  = im_src.size ();

    // Создаем вектор точек.
    vector<Point2f> pts_src;
    pts_src.push_back (Point2f (0, 0));
    pts_src.push_back (Point2f (size.width - 1, 0));
    pts_src.push_back (Point2f (size.width - 1, size.height - 1));
    pts_src.push_back (Point2f (0, size.height - 1));

    // Изображение назначения
    Mat im_dst = imread (DATA_PATH + "/images/times-square.jpg");

    // Установить данные для обработчика мыши
    Mat im_temp = im_dst.clone ();
    userdata data;
    data.im = im_temp;

    imshow ("Image", im_temp);
    cout << "Click on four corners of a billboard and then press ENTER" << endl;

    // устанавливаем функцию обратного вызова для любого события 
    setMouseCallback ("Image", mouseHandler, &data);
    waitKey (0);

    // Рассчитать гомографию между исходной и конечной точками
    Mat h = findHomography (pts_src, data.points);

    // Деформация исходного изображения
    warpPerspective (im_src, im_temp, h, im_temp.size ());

    // Извлечь четыре точки из данных 
    Point pts_dst [4];
    for (int i = 0; i < 4; i++) {
        pts_dst [i] = data.points [i];
    }

    // Затемнить многоугольную область на целевом изображении.
    fillConvexPoly (im_dst, pts_dst, 4, Scalar (0), LINE_AA);

    // Добавить деформированное исходное изображение к целевому изображению.
    im_dst = im_dst + im_temp;

    // Отображение изображения.
    imshow ("Image", im_dst);
    waitKey (0);

    return 0;
}
