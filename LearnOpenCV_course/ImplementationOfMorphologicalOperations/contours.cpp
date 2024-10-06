#include <iostream>
#include "dataPath.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main ()
{
    string imagePath = DATA_PATH + "/images/Contour.png";

    Mat image     = imread (imagePath);
    Mat imageCopy = image.clone ();

    Mat imageGray;
    // Преобразовать в оттенки серого
    cvtColor (image, imageGray, COLOR_BGR2GRAY);

    imshow ("image", imageGray);
    waitKey (0);

    // Найти все контуры на изображении
    vector<vector<Point> > contours; // контуры
    vector<Vec4i> hierarchy;         // иерархия

    findContours (imageGray, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    cout << "Number of contours found = " << contours.size ();
    drawContours (image, contours, -1, Scalar (0, 255, 0), 6);

    imshow ("image", image);
    waitKey (0);

    // Найти внешние контуры на изображении
    findContours (imageGray, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    cout << "Number of contours found = " << contours.size ();

    image = imageCopy.clone ();

    // Нарисуем все контуры
    drawContours (image, contours, -1, Scalar (0, 255, 0), 3);

    imshow ("image", image);
    waitKey (0);

    // Нарисуйте только 3-й контур
    // Обратите внимание, что сейчас мы не знаем
    // нумерацию контуров по формам,
    // присутствующим на рисунке
    image = imageCopy.clone ();
    drawContours (image, contours, 2, Scalar (0, 255, 0), 3);

    imshow ("image", image);
    waitKey (0);

    // Найти все контуры на изображении
    findContours (imageGray, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    // Нарисуем все контуры
    drawContours (image, contours, -1, Scalar (0, 255, 0), 3);

    Moments M;
    int x, y;
    for (size_t i = 0; i < contours.size (); i++) {
        // Мы будем использовать контурные моменты
        // для нахождения центра масс
        M = moments (contours [i]);
        x = int (M.m10 / double (M.m00));
        y = int (M.m01 / double (M.m00));

        // Отметьте центр
        circle (image, Point (x, y), 10, Scalar (255, 0, 0), -1);
    }

    imshow ("image", image);
    waitKey (0);

    for (size_t i = 0; i < contours.size (); i++) {
        // Мы будем использовать контурные моменты
        // для нахождения центра масс
        M = moments (contours [i]);
        x = int (M.m10 / double (M.m00));
        y = int (M.m01 / double (M.m00));

        // Отметьте центр
        circle (image, Point (x, y), 10, Scalar (255, 0, 0), -1);

        // Отметьте номер контура
        putText (image, to_string (i + 1), Point (x + 40, y - 10), FONT_HERSHEY_SIMPLEX, 1, Scalar (0, 0, 255), 2);
    }

    imageCopy = image.clone ();

    imshow ("image", image);
    waitKey (0);

    double area;
    double perimeter;
    for (size_t i = 0; i < contours.size (); i++) {
        area      = contourArea (contours [i]);
        perimeter = arcLength (contours [i], true);
        cout << "Contour #" << i + 1 << " has area = " << area << " and perimeter = " << perimeter << endl;
    }

    image = imageCopy.clone ();
    Rect rect;
    for (size_t i = 0; i < contours.size (); i++) {
        // Вертикальный прямоугольник
        rect = boundingRect (contours [i]);
        rectangle (image, rect, Scalar (255, 0, 255), 2);
    }
    imshow ("image", image);
    waitKey (0);

    image = imageCopy.clone ();
    RotatedRect rotrect;
    Point2f rect_points [4];
    Mat boxPoints2f, boxPointsCov;

    for (size_t i = 0; i < contours.size (); i++) {
        // Повернутый прямоугольник
        rotrect = minAreaRect (contours [i]);
        boxPoints (rotrect, boxPoints2f);
        boxPoints2f.assignTo (boxPointsCov, CV_32S);
        polylines (image, boxPointsCov, true, Scalar (0, 255, 255), 2);
    }

    imshow ("image", image);
    waitKey (0);

    image = imageCopy.clone ();
    Point2f center;
    float radius;
    for (size_t i = 0; i < contours.size (); i++) {
        // Вписать круг
        minEnclosingCircle (contours [i], center, radius);
        circle (image, center, radius, Scalar (125, 125, 125), 2);
    }

    imshow ("image", image);
    waitKey (0);

    image = imageCopy.clone ();
    RotatedRect rellipse;
    for (size_t i = 0; i < contours.size (); i++) {
        // Вписать эллипс
        // Мы можем вписать эллипс только
        // когда наш контур имеет минимум
        // 5 баллов
        if (contours [i].size () < 5) continue;
        rellipse = fitEllipse (contours [i]);
        ellipse (image, rellipse, Scalar (255, 0, 125), 2);
    }
    imshow ("image", image);
    waitKey (0);

    return 0;
}
