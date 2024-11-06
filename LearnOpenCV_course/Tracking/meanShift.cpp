#include <opencv2/opencv.hpp>
#include <iostream>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main ()
{
    string filename = DATA_PATH + "/videos/face1.mp4";
    VideoCapture cap (filename);

    Mat frame;
    cap >> frame;

    // Обнаружение лиц на изображении
    CascadeClassifier faceCascade;
    String faceCascadePath = DATA_PATH + "/haarcascade/haarcascade_frontalface_default2.xml";

    if (!faceCascade.load (faceCascadePath)) {
        printf ("--(!)Error loading face cascade\n");
    };
    Mat frameGray;
    cvtColor (frame, frameGray, COLOR_BGR2GRAY);

    vector<Rect> faces;
    faceCascade.detectMultiScale (frameGray, faces, 1.3, 5);

    int x = faces [0].x;
    int y = faces [0].y;
    int w = faces [0].width;
    int h = faces [0].height;

    Rect currWindow = Rect ((long)x, (long)y, (long)w, (long)h);

    Mat roiObject;

    // получаем область лица из кадра
    frame (currWindow).copyTo (roiObject);
    Mat hsvObject;
    cvtColor (roiObject, hsvObject, COLOR_BGR2HSV);
    // Получить маску для расчета гистограммы объекта и
    // также удалить шум
    Mat mask;
    inRange (hsvObject, Scalar (0, 50, 50), Scalar (180, 256, 256), mask);

    // Разделить изображение на каналы для нахождения гистограммы
    vector<Mat> channels (3);
    split (hsvObject, channels);

    imshow ("Mask of ROI", mask);
    waitKey (0);
    imshow ("ROI", roiObject);
    waitKey (0);
    destroyAllWindows ();

    Mat histObject;

    // Инициализируем параметры для гистограммы
    int histSize           = 180;
    float range []         = { 0, 179 };
    const float* ranges [] = { range };

    // Найти гистограмму и нормализовать ее, чтобы она имела значения
    // от 0 до 255
    calcHist (&channels [0], 1, 0, mask, histObject, 1, &histSize, ranges, true, false);
    normalize (histObject, histObject, 0, 255, NORM_MINMAX);

    // Мы обработаем только первые 5 кадров
    int count = 0;
    Mat hsv, backProjectImage, frameClone;
    while (1) {
        // Прочитать кадр
        cap >> frame;
        if (frame.empty ()) break;

        // Преобразовать в цветовое пространство hsv
        cvtColor (frame, hsv, COLOR_BGR2HSV);
        split (hsv, channels);

        // находим обратно спроецированное изображение с гистограммой, полученной ранее
        calcBackProject (&channels [0], 1, 0, histObject, backProjectImage, ranges);
        imshow ("Back Projected Image", backProjectImage);
        waitKey (0);
        // Вычислить новое окно, используя среднее смещение в текущем кадре
        int ret = meanShift (backProjectImage, currWindow, TermCriteria (TermCriteria::EPS | TermCriteria::COUNT, 10, 1));

        // Отображение кадра с отслеженным местоположением лица
        frameClone = frame.clone ();

        rectangle (frameClone, Point (currWindow.x, currWindow.y), Point (currWindow.x + currWindow.width, currWindow.y + currWindow.height),
          Scalar (255, 0, 0), 2, LINE_AA);
        imshow ("Mean Shift Object Tracking Demo", frameClone);
        waitKey (0);

        count += 2;
        if (count == 10) break;
    }

    cap.release ();
    return 0;
}
