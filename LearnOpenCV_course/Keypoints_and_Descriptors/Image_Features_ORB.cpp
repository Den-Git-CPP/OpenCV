#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ()
{
    Mat img = imread (DATA_PATH + "/images/book.jpeg");
    Mat imgGray;
    cvtColor (img, imgGray, COLOR_BGR2GRAY);

    imshow ("Image", img);
    waitKey (0);

    imshow ("Gray", imgGray);
    waitKey (0);
    destroyAllWindows ();

    // Инициировать детектор ORB
    Ptr<ORB> orb = ORB::create ();

    // находим ключевые точки с помощью ORB
    vector<KeyPoint> kp;
    orb->detect (imgGray, kp, Mat ());
    // вычисляем дескрипторы с помощью ORB
    Mat des;
    orb->compute (imgGray, kp, des);
    // рисуем только местоположение ключевых точек, а не размер и ориентацию
    Mat img2;
    drawKeypoints (img, kp, img2, Scalar (0, 255, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow ("Keypoints", img2);
    waitKey (0);
    destroyAllWindows ();

    orb = ORB::create (10);
    orb->detectAndCompute (imgGray, Mat (), kp, des);
    drawKeypoints (img, kp, img2, Scalar (0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow ("Keypoints", img2);
    waitKey (0);

    destroyAllWindows ();
    return 0;
}
