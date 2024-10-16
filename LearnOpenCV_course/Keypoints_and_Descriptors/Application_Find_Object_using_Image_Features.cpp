#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main ()
{
    int MAX_FEATURES    = 1000;
    int MIN_MATCH_COUNT = 10;

    Mat img1 = imread (DATA_PATH + "/images/book.jpeg");
    Mat img1Gray;
    cvtColor (img1, img1Gray, COLOR_BGR2GRAY);

    Mat img2 = imread (DATA_PATH + "/images/book_scene.jpeg");
    Mat img2Gray;
    cvtColor (img2, img2Gray, COLOR_BGR2GRAY);

    imshow ("Image", img1);
    waitKey (0);
    imshow ("Gray", img1Gray);
    waitKey (0);
    imshow ("Image", img2);
    waitKey (0);
    imshow ("Gray", img2Gray);
    waitKey (0);
    destroyAllWindows ();

    // Инициировать детектор ORB
    Ptr<ORB> orb = ORB::create (MAX_FEATURES);

    // находим ключевые точки с помощью ORB
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;

    orb->detectAndCompute (img1Gray, Mat (), keypoints1, descriptors1);
    orb->detectAndCompute (img2Gray, Mat (), keypoints2, descriptors2);

    FlannBasedMatcher matcher (new flann::KDTreeIndexParams (5), new flann::SearchParams (50));

    std::vector<std::vector<DMatch> > matches;
    descriptors1.convertTo (descriptors1, CV_32F);
    descriptors2.convertTo (descriptors2, CV_32F);
    matcher.knnMatch (descriptors1, descriptors2, matches, 2);

    //-- Фильтрация совпадений с использованием теста Лоу
    const float ratio_thresh = 0.9f;
    std::vector<DMatch> good;
    for (size_t i = 0; i < matches.size (); i++) {
        if (matches [i][0].distance < ratio_thresh * matches [i][1].distance) {
            good.push_back (matches [i][0]);
        }
    }

    std::vector<Point2f> src_pts;
    std::vector<Point2f> dst_pts;
    for (size_t i = 0; i < good.size (); i++) {
        //-- Получить ключевые точки из хороших совпадений
        src_pts.push_back (keypoints1 [good [i].queryIdx].pt);
        dst_pts.push_back (keypoints2 [good [i].trainIdx].pt);
    }

    //-- Draw matches
    Mat img3;
    drawMatches (img1, keypoints1, img2, keypoints2, good, img3, Scalar (0, 255, 0), Scalar::all (-1), std::vector<char> (), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    if (good.size () > MIN_MATCH_COUNT) {
        Mat H = findHomography (src_pts, dst_pts, RANSAC, 5.0);

        //-- Получаем углы из image_1 (объект, который нужно «обнаружить»)
        std::vector<Point2f> obj_corners (4);
        obj_corners [0] = Point2f (0, 0);
        obj_corners [1] = Point2f ((float)img1.cols, 0);
        obj_corners [2] = Point2f ((float)img1.cols, (float)img1.rows);
        obj_corners [3] = Point2f (0, (float)img1.rows);
        std::vector<Point2f> scene_corners (4);
        perspectiveTransform (obj_corners, scene_corners, H);

        //-- Рисуем линии между углами (отображенный объект на сцене - image_2 )
        line (img3, scene_corners [0] + Point2f ((float)img1.cols, 0), scene_corners [1] + Point2f ((float)img1.cols, 0), Scalar (0, 0, 255), 10);
        line (img3, scene_corners [1] + Point2f ((float)img1.cols, 0), scene_corners [2] + Point2f ((float)img1.cols, 0), Scalar (0, 0, 255), 10);
        line (img3, scene_corners [2] + Point2f ((float)img1.cols, 0), scene_corners [3] + Point2f ((float)img1.cols, 0), Scalar (0, 0, 255), 10);
        line (img3, scene_corners [3] + Point2f ((float)img1.cols, 0), scene_corners [0] + Point2f ((float)img1.cols, 0), Scalar (0, 0, 255), 10);
    }
    else {
        cout << "Not enough matches are found - " << good.size () << "/" << MIN_MATCH_COUNT;
    }

    imshow ("Detected Object", img3);
    waitKey (0);
    destroyAllWindows ();

    return 0;
}
