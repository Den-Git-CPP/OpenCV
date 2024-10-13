// Coin Detection Assignment
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "dataPath.h"

using namespace std;
using namespace cv;

void displayImage (const Mat& image, const std::string& name = "Image", bool clear = true, bool scale_down = false)
{
    auto imageCopy = image.clone ();
    if (scale_down) {
        resize (image, imageCopy, Size{}, 0.5, 0.5, INTER_AREA);
    }
    imshow (name, imageCopy);
    waitKey (0);
    if (clear) destroyAllWindows ();
}

Mat displayConnectedComponents (Mat& im)
{
    // Сделать копию изображения
    Mat imLabels = im.clone ();

    // Сначала найдем минимальное и максимальное значения в imLabels
    Point minLoc, maxLoc;
    double min, max;

    // Следующая строка находит минимальное и максимальное значения пикселей
    // и их расположение на изображении.
    minMaxLoc (imLabels, &min, &max, &minLoc, &maxLoc);

    // Нормализуем изображение так, чтобы минимальное значение было равно 0, а максимальное — 255.
    imLabels = 255 * (imLabels - min) / (max - min);
    // Преобразовать изображение в 8-битное
    imLabels.convertTo (imLabels, CV_8U);

    // Применить цветовую карту
    Mat imColorMap;
    applyColorMap (imLabels, imColorMap, COLORMAP_JET);

    return imColorMap;
}

int main ()
{

    string imagePath = DATA_PATH+ "/images/CoinsA.png";
    // Прочитать изображение
    // Сохраните его в переменной image
    Mat image     = imread (imagePath);
    Mat imageCopy = image.clone ();

    //	displayImage(image, "Source");

    // Преобразовать изображение в оттенки серого
    // Сохраните его в переменной imageGray
    Mat imageGray;
    cvtColor (imageCopy, imageGray, COLOR_RGB2GRAY);
    //	displayImage(imageGray);

    // Разделить ячейку на каналы
    // Сохранять их в переменных image, image, image
    Mat bands [3];
    Mat imageB, imageG, imageR;
    split (imageCopy, bands);
    imageB = bands [0];
    imageG = bands [1];
    imageR = bands [2];

    //	displayImage(imageB, "Blue");
    //	displayImage(imageG, "Green");
    //	displayImage(imageR, "Red");

    // Пороговое значение
    Mat dst;
    threshold (imageGray, dst, 35, 255, THRESH_BINARY_INV);

    // Измените по мере необходимости
    //	displayImage(dst, "Thresholded");
    // Морфологических операций
    Mat imageDilated, imageEroded;
    // Получить структурный элемент/ядро, которое будет использоваться для расширения
    Mat element  = getStructuringElement (MORPH_ELLIPSE, { 5, 5 });
    Mat element2 = getStructuringElement (MORPH_ELLIPSE, { 3, 3 });
    morphologyEx (dst, imageDilated, MORPH_DILATE, element2, Point{ -1, -1 }, 5);
    morphologyEx (imageDilated, imageDilated, MORPH_ERODE, element2, Point{ -1, -1 }, 7);
    morphologyEx (imageDilated, imageEroded, MORPH_DILATE, element, Point{ -1, -1 }, 4);

    //	displayImage(imageEroded, "Morphed", false);

    // Настройка параметров SimpleBlobDetector.
    SimpleBlobDetector::Params params;

    params.blobColor = 0;

    params.minDistBetweenBlobs = 2;

    // Фильтр по области
    params.filterByArea = false;

    // Фильтр по кругообразности
    params.filterByCircularity = true;
    params.minCircularity      = 0.8;

    // Фильтр по выпуклости
    params.filterByConvexity = true;
    params.minConvexity      = 0.8;

    // Фильтр по инерции
    params.filterByInertia = true;
    params.minInertiaRatio = 0.8;

    // Настраиваем детектор с параметрами
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create (params);

    // Обнаружение пятен
    std::vector<KeyPoint> keypoints;
    detector->detect (imageEroded, keypoints);
    // Распечатать количество обнаруженных монет
    std::cout << "Blob Detector detected " << keypoints.size () << " points" << std::endl;

    // Маркируем монеты, используя концепции аннотаций изображений, которые мы изучили до сих пор

    std::for_each (keypoints.begin (), keypoints.end (), [&imageCopy] (KeyPoint& point) {
        int radius      = point.size / 2;
        double diameter = point.size;
        circle (imageCopy, point.pt, radius, Scalar{ 0, 255, 0 }, 2);
        circle (imageCopy, point.pt, 1, Scalar{ 255, 0, 0 }, 2);
    });
    //	displayImage(imageCopy);
    //  displayImage(imageEroded);
    // Найти связанные компоненты
    Mat components;
    Mat inverted;
    bitwise_not (imageEroded, inverted);
    int n_components = connectedComponents (inverted, components);
    std::cout << "Connected Components = " << n_components << std::endl;

    // Используйте функцию displayConnectedComponents, указанную выше
    Mat colorMap = displayConnectedComponents (components);

    //	displayImage(colorMap);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<Vec4i> hierarchy;
    // Распечатать количество найденных контуров
    findContours (imageEroded, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    std::cout << "Found " << contours.size () << " contours" << std::endl;

    // Нарисовать все контуры
    imageCopy = image.clone ();
    drawContours (imageCopy, contours, -1, Scalar{ 0, 255, 0 }, 2);
    // Удалить внутренние контуры
    // Отобразить результат
    imageCopy = image.clone ();
    drawContours (imageCopy, contours, 9, Scalar{ 0, 255, 0 }, 3);
    //  displayImage(imageCopy, "Contours");

    // Печать области и периметра всех контуров
    for (uint32_t i = 0; i < contours.size (); i++) {
        float area = contourArea (contours [i]);
        std::cout << "Area of Contour #" << i << " = " << area << std::endl;
    }
    auto maxPos = std::max_element (contours.begin (), contours.end (), [] (auto& a, auto& b) {
        return contourArea (a) < contourArea (b);
    });
    // Распечатать максимальную площадь контура
    std::cout << "Max Area is " << contourArea (*maxPos) << std::endl;
    // Удалить этот контур и построить другие
    contours.erase (maxPos);
    imageCopy = image.clone ();
    drawContours (imageCopy, contours, -1, Scalar{ 0, 255, 0 }, 3);
    //  displayImage(imageCopy, "Contours filtered");
    // Разместите круги на монетах
    imageCopy = image.clone ();
    for (uint32_t i = 0; i < contours.size (); i++) {
        Point2f center;
        float radius;
        minEnclosingCircle (contours [i], center, radius);
        circle (imageCopy, center, radius, Scalar (0, 255, 0), 2);
    }

    //  displayImage(imageCopy);
    /***/
    // Путь к изображению
    imagePath = DATA_PATH+ "/images/CoinsB.png";
    // Прочитать изображение
    // Сохраните его в переменной image
    image     = imread (imagePath);
    imageCopy = image.clone ();

    // Преобразовать изображение в оттенки серого
    // Сохраните его в переменной imageGray

    cvtColor (imageCopy, imageGray, COLOR_RGB2GRAY);

    //	displayImage(imageGray);
    split (imageCopy, bands);
    imageB = bands [0];
    imageG = bands [1];
    imageR = bands [2];

    //	displayImage(imageB);
    //	displayImage(imageG);
    //	displayImage(imageR);

    threshold (imageB, dst, 127, 255, THRESH_BINARY);
    //	displayImage(dst, "DstB", true, true);

    // Морфологических операций
    element2 = getStructuringElement (MORPH_ELLIPSE, Size{ 11, 11 });
    morphologyEx (dst, imageDilated, MORPH_OPEN, element2, Point{ -1, -1 }, 1);
    morphologyEx (imageDilated, imageEroded, MORPH_CLOSE, element2, Point{ -1, -1 }, 2);
    morphologyEx (imageEroded, imageEroded, MORPH_ERODE, element2, Point{ -1, -1 }, 12);
    morphologyEx (imageEroded, imageEroded, MORPH_DILATE, element2, Point{ -1, -1 }, 6);
    displayImage (imageDilated, "Dilated", false, true);
    displayImage (imageEroded, "Eroded", true, true);
    // Настройка параметров SimpleBlobDetector.

    params.blobColor = 0;

    params.minDistBetweenBlobs = 2;

    // Фильтр по области
    params.filterByArea = false;

    // Фильтр по кругообразности
    params.filterByCircularity = true;
    params.minCircularity      = 0.8;

    // Фильтр по выпуклости
    params.filterByConvexity = true;
    params.minConvexity      = 0.8;

    // Фильтр по инерции
    params.filterByInertia = true;
    params.minInertiaRatio = 0.8;

    // Set up detector with params
    detector = SimpleBlobDetector::create (params);

    // Обнаружение пятен
    detector->detect (imageEroded, keypoints);
    // Распечатать количество обнаруженных монет
    std::cout << "Num Coins Detected = " << keypoints.size () << std::endl;

    // Маркируем монеты, используя концепции аннотаций изображений, которые мы изучили до сих пор
    for (auto& point : keypoints) {
        int radius = point.size / 2;
        circle (imageCopy, point.pt, radius, Scalar{ 0, 255, 0 }, 2);
        circle (imageCopy, point.pt, 1, Scalar{ 255, 0, 0 }, 2);
    }
    displayImage (imageCopy, "Annotated", true, true);

    bitwise_not (imageEroded, inverted);
    n_components = connectedComponents (inverted, components);
    std::cout << "Num of connected Components = " << n_components << std::endl;

    colorMap = displayConnectedComponents (components);
    displayImage (colorMap, "components", true, true);
    // Найти все контуры на изображении
    findContours (imageEroded, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Распечатать количество найденных контуров
    std::cout << "Number of contours = " << contours.size () << std::endl;

    // Нарисовать все контуры
    imageCopy = image.clone ();
    drawContours (imageCopy, contours, -1, Scalar{ 255, 0, 0 }, 3, LINE_AA);
    displayImage (imageCopy, "contours", true, true);

    // Удалить внутренние контуры
    // Отобразить результат
    std::sort (contours.begin (), contours.end (), [] (auto& a, auto& b) {
        return contourArea (a) > contourArea (b);
    });
    contours.pop_back ();
    contours.pop_back ();
    imageCopy = image.clone ();
    drawContours (imageCopy, contours, -1, Scalar{ 255, 0, 0 }, 3, LINE_AA);
    displayImage (imageCopy, "contours filtered", true, true);
    // Печать области и периметра всех контуров
    for (uint32_t i = 0; i < contours.size (); i++) {
        float area      = contourArea (contours [i]);
        float perimeter = arcLength (contours [i], true);
        std::cout << "Area of Contour #" << i << " = " << area << " Perimeter = " << perimeter << std::endl;
    }
    maxPos = std::max_element (contours.begin (), contours.end (), [] (auto& a, auto& b) {
        return contourArea (a) < contourArea (b);
    });
    // Распечатать максимальную площадь контура
    std::cout << "Max Area is " << contourArea (*maxPos) << std::endl;
    // Удалить этот контур и построить другие
    contours.erase (maxPos);
    imageCopy = image.clone ();
    drawContours (imageCopy, contours, -1, Scalar{ 255, 0, 0 }, 3, LINE_AA);
    displayImage (imageCopy, "contours Filtered", true, true);

    // Remove contours
    // Draw revised contours
    
    // Разместите круги на монетах
    imageCopy = image.clone ();
    for (uint32_t i = 0; i < contours.size (); i++) {
        Point2f center;
        float radius;
        minEnclosingCircle (contours [i], center, radius);
        circle (imageCopy, center, radius, Scalar (0, 255, 0), 5);
    }
    displayImage (imageCopy, "Final", true, true);

    return 0;
}