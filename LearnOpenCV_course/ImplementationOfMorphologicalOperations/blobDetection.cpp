#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main ()
{
    Mat img = imread (DATA_PATH + "/images/blob_detection.jpg", IMREAD_GRAYSCALE);

    // Настроить детектор с параметрами по умолчанию
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create ();

    std::vector<KeyPoint> keypoints;
    detector->detect (img, keypoints);

    // Отметьте пятна, используя концепции аннотации изображений, которые мы изучили до сих пор
    int x, y;
    int radius;
    double diameter;
    cvtColor (img, img, COLOR_GRAY2BGR);
    for (int i = 0; i < keypoints.size (); i++) {
        KeyPoint k = keypoints [i];
        Point keyPt;
        keyPt = k.pt;
        x     = (int)keyPt.x;
        y     = (int)keyPt.y;
        // Отметить центр ЧЕРНЫМ
        circle (img, Point (x, y), 5, Scalar (255, 0, 0), -1);
        // Получить радиус монеты
        diameter = k.size;
        radius   = (int)diameter / 2.0;
        // Отметить пятно ЗЕЛЕНЫМ
        circle (img, Point (x, y), radius, Scalar (0, 255, 0), 2);
    }

    imshow ("Image", img);
    waitKey (0);

    // Настройка параметров SimpleBlobDetector.
    SimpleBlobDetector::Params params;

    // Изменить пороги
    params.minThreshold = 10;
    params.maxThreshold = 200;
    // Фильтр по области.
    params.filterByArea = true;
    params.minArea      = 1500;

    // Фильтр по кругообразности
    params.filterByCircularity = true;
    params.minCircularity      = 0.1;

    // Фильтр по выпуклости
    params.filterByConvexity = true;
    params.minConvexity      = 0.87;

    // Фильтр по инерции
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;

    detector = SimpleBlobDetector::create (params);

    return 0;
}
