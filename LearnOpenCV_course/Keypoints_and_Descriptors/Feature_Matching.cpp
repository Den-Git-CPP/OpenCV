#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ()
{
    Mat img1 = imread (DATA_PATH + "/images/book.jpeg", IMREAD_GRAYSCALE);
    Mat img2 = imread (DATA_PATH + "/images/book_scene.jpeg", IMREAD_GRAYSCALE);
    // Инициировать детектор ORB
    Ptr<ORB> orb = ORB::create ();
    // находим ключевые точки и дескрипторы с помощью ORB
    vector<KeyPoint> kp1, kp2;
    Mat des1, des2;
    orb->detectAndCompute (img1, Mat (), kp1, des1);
    orb->detectAndCompute (img2, Mat (), kp2, des2);

    // создаем объект BFMatcher
    BFMatcher bf (NORM_HAMMING, true);
    // Сопоставьте дескрипторы.
    vector<DMatch> matches;
    bf.match (des1, des2, matches, Mat ());

    // Сортируем их в порядке расстояния
    sort (matches.begin (), matches.end ());
    // Выбираем первые 10 матчей.
    matches = vector<DMatch> (matches.begin (), matches.begin () + 10);
    Mat img3;
    vector<char> match_mask (matches.size (), 1);
    drawMatches (img1, kp1, img2, kp2, matches, img3, Scalar::all (-1), Scalar::all (-1), match_mask, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imshow ("Image", img3);
    waitKey (0);
    
    FlannBasedMatcher matcher (new flann::LshIndexParams (6, 12, 1), new flann::SearchParams (50));
    std::vector<std::vector<DMatch> > matches_vec;
    matcher.knnMatch (des1, des2, matches_vec, 2);
    matches_vec = vector<vector<DMatch> > (matches_vec.begin (), matches_vec.begin () + 10);
    drawMatches (img1, kp1, img2, kp2, matches_vec, img3);
    imshow ("Image", img3);
    waitKey (0);

    destroyAllWindows ();
    return 0;
}
