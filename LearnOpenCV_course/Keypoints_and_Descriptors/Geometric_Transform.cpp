#include <iostream>
#include "dataPath.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ()
{
    // Создаем черное изображение размером 200x200
    Mat img (200, 200, CV_32FC3, Scalar (0, 0, 0));
    // Создаем синий квадрат в центре
    img (Range (50, 150), Range (50, 150)).setTo (Scalar (1, 0.6, 0.2));

    imshow ("Image", img);
    waitKey (0);
    destroyAllWindows ();

    // Выходное измерение
    Size outDim = img.size ();
    // Перевод на 25,25
    float warpMatValues [] = { 1.0, 0.0, 25.0, 0.0, 1.0, 25.0 };
    Mat warpMat            = Mat (2, 3, CV_32F, warpMatValues);
    // Деформация изображения
    Mat result;
    warpAffine (img, result, warpMat, outDim);

    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    // Масштаб по направлению x
    float warpMatValues2 [] = { 2.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
    warpMat                 = Mat (2, 3, CV_32F, warpMatValues2);

    // Деформация изображения
    warpAffine (img, result, warpMat, outDim);

    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    // Масштаб по направлению x

    // Деформация изображения
    warpAffine (img, result, warpMat, Size (outDim.width * 2, outDim.height));

    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    // Масштаб по направлениям x и y
    float warpMatValues3 [] = { 2.0, 0.0, 0.0, 0.0, 2.0, 0.0 };
    warpMat                 = Mat (2, 3, CV_32F, warpMatValues3);

    // Деформация изображения
    warpAffine (img, result, warpMat, Size (outDim.width * 2, outDim.height * 2));

    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();
    // Поворот  изображения
    float angleInRadians = 30;
    angleInRadians       = 30 * 3.14 / 180.0;

    float cosTheta = cos (angleInRadians);
    float sinTheta = sin (angleInRadians);

    // Матрица вращения
    // https://en.wikipedia.org/wiki/Rotation_matrix

    float warpMatValues4 [] = { cosTheta, sinTheta, 0.0, -sinTheta, cosTheta, 0.0 };
    warpMat                 = Mat (2, 3, CV_32F, warpMatValues4);

    // Деформация изображения
    warpAffine (img, result, warpMat, outDim);
    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    float centerX = img.size ().width / 2;
    float centerY = img.size ().height / 2;

    float tx = (1 - cosTheta) * centerX - sinTheta * centerY;
    float ty = sinTheta * centerX + (1 - cosTheta) * centerY;

    // Матрица вращения
    // https://en.wikipedia.org/wiki/Rotation_matrix

    float warpMatValues5 [] = { cosTheta, sinTheta, tx, -sinTheta, cosTheta, ty };
    warpMat                 = Mat (2, 3, CV_32F, warpMatValues5);

    // Деформация изображения
    warpAffine (img, result, warpMat, outDim);
    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    float anglesInDegrees = 30;
    // Получить матрицу вращения
    Mat rotationMatrix = getRotationMatrix2D (Point2f (centerX, centerY), anglesInDegrees, 1);

    // Деформация изображения
    warpAffine (img, result, rotationMatrix, outDim);
    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    float shearAmount = 0.1;

    float warpMatValues6 [] = { 1, shearAmount, 0, 0, 1.0, 0 };
    warpMat                 = Mat (2, 3, CV_32F, warpMatValues6);

    // Деформация изображения
    warpAffine (img, result, warpMat, outDim);

    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    // Шкала
    float scaleAmount       = 1.1;
    float warpMatValues7 [] = { scaleAmount, 0.0, 0, scaleAmount };
    Mat scaleMat            = Mat (2, 2, CV_32F, warpMatValues7);
    // Сдвиг
    shearAmount             = -0.1;
    float warpMatValues8 [] = { 1, shearAmount, 0, 1.0 };
    Mat shearMat            = Mat (2, 2, CV_32F, warpMatValues8);

    // Поворот на 10 градусов вокруг (0,0)
    angleInRadians = 10.0 * 3.14 / 180.0;
    cosTheta       = cos (angleInRadians);
    sinTheta       = sin (angleInRadians);

    float warpMatValues9 [] = { cosTheta, sinTheta, -sinTheta, cosTheta };
    Mat rotMat              = Mat (2, 2, CV_32F, warpMatValues9);

    float warpMatValues10 [] = { 10, 0 };
    Mat translateVector      = Mat (2, 1, CV_32F, warpMatValues10);

    // Сначала применяется масштабирование, затем сдвиг, затем вращение.
    Mat scaleShearRotate = rotMat * shearMat * scaleMat;

    hconcat (scaleShearRotate, translateVector, warpMat);

    cout << warpMat;
    float warpMatValues11 [] = { 50, 50, 50, 149, 149, 50, 149, 149 };
    hconcat (translateVector, translateVector, translateVector);
    hconcat (translateVector, translateVector, translateVector);
    Mat outPts = scaleShearRotate * Mat (4, 2, CV_32F, warpMatValues11).t () + translateVector;
    cout << outPts;
    // Деформация изображения
    warpAffine (img, result, warpMat, outDim);

    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    vector<Point2f> srcPoints{ Point2f (50, 50), Point2f (50, 149), Point2f (149, 50) };
    vector<Point2f> dstPoints{ Point2f (68, 45), Point2f (76, 155), Point2f (176, 27) };
    Mat estimatedMat = estimateAffine2D (srcPoints, dstPoints);
    cout << "True warp matrix:\n\n" << warpMat;
    cout << "Estimated warp matrix:\n\n" << estimatedMat;
    srcPoints    = vector<Point2f>{ Point2f (50, 50), Point2f (50, 149), Point2f (149, 149), Point2f (149, 50) };
    dstPoints    = vector<Point2f>{ Point2f (68, 45), Point2f (76, 155), Point2f (183, 135), Point2f (176, 27) };
    estimatedMat = estimateAffine2D (srcPoints, dstPoints);
    cout << "True warp matrix:\n\n" << warpMat;
    cout << "Estimated warp matrix:\n\n" << estimatedMat;
    // Деформация изображения
    warpAffine (img, result, estimatedMat, outDim);

    imshow ("Result", result);
    waitKey (0);
    destroyAllWindows ();

    // Деформация изображения
    Mat imgT (200, 200, CV_32FC3, Scalar (0, 0, 0));
    Point dstPoints2 [] = { Point (75, 50), Point (50, 149), Point (149, 149), Point (124, 50) };
    fillConvexPoly (imgT, dstPoints2, 4, Scalar (1.0, 0.6, 0.2), LINE_AA);

    imshow ("Original Image", img);
    waitKey (0);
    imshow ("Transformed Image", imgT);
    waitKey (0);
    destroyAllWindows ();

    dstPoints    = vector<Point2f>{ Point2f (75, 50), Point2f (50, 149), Point2f (149, 149), Point2f (124, 50) };
    estimatedMat = estimateAffine2D (srcPoints, dstPoints);
    cout << "Estimated warp matrix:\n\n" << estimatedMat;
    // Деформация изображения
    Mat imA;
    warpAffine (img, imA, estimatedMat, outDim);

    imshow ("Transformed Image", imgT);
    waitKey (0);
    imshow ("Image warped using estimated Affine Transform", imA);
    waitKey (0);
    destroyAllWindows ();

    Mat h = findHomography (srcPoints, dstPoints);
    cout << h;
    // Деформировать исходное изображение в целевое на основе гомографии
    Mat imH;
    warpPerspective (img, imH, h, outDim);

    imshow ("Transformed Image", imgT);
    waitKey (0);
    imshow ("Image warped using estimated Affine Transform", imA);
    waitKey (0);
    imshow ("Image warped using estimated Homography", imH);
    waitKey (0);
    destroyAllWindows ();

    return 0;
}
