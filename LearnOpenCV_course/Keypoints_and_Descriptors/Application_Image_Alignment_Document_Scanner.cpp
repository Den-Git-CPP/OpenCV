#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ()
{
    // Прочитать эталонное изображение
    string refFilename (DATA_PATH + "/images/form.jpg");
    cout << "Reading reference image : " << refFilename << endl;
    Mat imReference = imread (refFilename);
    imshow ("Image", imReference);
    waitKey (0);
    // Прочитать изображение для выравнивания
    string imFilename (DATA_PATH + "/images/scanned-form.jpg");
    cout << "Reading image to align : " << imFilename << endl;
    Mat img = imread (imFilename);
    imshow ("Image", img);
    waitKey (0);

    int MAX_FEATURES         = 500;
    float GOOD_MATCH_PERCENT = 0.15f;
    // Преобразование изображений в оттенки серого
    Mat im1Gray, im2Gray;
    cvtColor (img, im1Gray, COLOR_BGR2GRAY);
    cvtColor (imReference, im2Gray, COLOR_BGR2GRAY);
    // Переменные для хранения ключевых точек и дескрипторов
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;

    // Обнаружение функций ORB и вычисление дескрипторов.
    Ptr<Feature2D> orb = ORB::create (MAX_FEATURES);
    orb->detectAndCompute (im1Gray, Mat (), keypoints1, descriptors1);
    orb->detectAndCompute (im2Gray, Mat (), keypoints2, descriptors2);
    // Сопоставьте характеристики.
    std::vector<DMatch> matches;
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create ("BruteForce-Hamming");
    matcher->match (descriptors1, descriptors2, matches, Mat ());

    // Сортировать матчи по счету
    std::sort (matches.begin (), matches.end ());

    // Удалить не очень хорошие совпадения
    const int numGoodMatches = matches.size () * GOOD_MATCH_PERCENT;
    matches.erase (matches.begin () + numGoodMatches, matches.end ());

    // Нарисуйте лучшие совпадения
    Mat imMatches;
    drawMatches (img, keypoints1, imReference, keypoints2, matches, imMatches);
    imwrite ("matches.jpg", imMatches);

    imshow ("Matches", imMatches);
    waitKey (0);

    // Извлечь местоположение хороших совпадений
    std::vector<Point2f> points1, points2;

    for (size_t i = 0; i < matches.size (); i++) {
        points1.push_back (keypoints1 [matches [i].queryIdx].pt);
        points2.push_back (keypoints2 [matches [i].trainIdx].pt);
    }

    // Найти гомографию
    Mat h = findHomography (points1, points2, RANSAC);

    // Используем гомографию для деформации изображения
    Mat im1Reg;
    warpPerspective (img, im1Reg, h, imReference.size ());

    imshow ("Image", im1Reg);
    waitKey (0);
    // Распечатать предполагаемую гомографию
    cout << "Estimated homography : \n" << h << endl;

    destroyAllWindows ();
    return 0;
}
