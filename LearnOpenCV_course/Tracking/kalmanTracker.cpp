/*
 Copyright 2017 BIG VISION LLC ALL RIGHTS RESERVED

 This program is distributed WITHOUT ANY WARRANTY to the
 students of the online course titled

 "Computer Visionfor Faces" by Satya Mallick

 for personal non-commercial use.

 Sharing this code is strictly prohibited without written
 permission from Big Vision LLC.

 For licensing and other inquiries, please email
 spmallick@bigvisionllc.com

 */

#include "opencv2/opencv.hpp"
#include "dataPath.h"

using namespace cv;
using namespace std;

// Сравнение прямоугольников
bool rectAreaComparator (Rect& r1, Rect& r2)
{
    return r1.area () < r2.area ();
}

// Цвета для отображения
Scalar blue (255, 128, 0);
Scalar red (64, 64, 255);

int main (int, char**)
{

    // Инициализируем дескриптор   для обнаружения людей
    HOGDescriptor hog (Size (64, 128),      // winSize
      Size (16, 16),                        // blocksize
      Size (8, 8),                          // blockStride,
      Size (8, 8),                          // cellSize,
      9,                                    // nbins,
      0,                                    // derivAperture,
      -1,                                   // winSigma,
      HOGDescriptor::HistogramNormType (0), // histogramNormType,
      0.2,                                  // L2HysThresh,
      1,                                    // gammal correction,
      64,                                   // nlevels=64
      0);                                   // signedGradient
    // Настраиваем детектор людей.
    vector<float> svmDetector = hog.getDefaultPeopleDetector ();
    hog.setSVMDetector (svmDetector);
    float hitThreshold        = 0.0;
    Size winStride            = Size (8, 8);
    Size padding              = Size (32, 32);
    float scale               = 1.05;
    float finalThreshold      = 1;
    bool useMeanshiftGrouping = 0;
    vector<double> weights;

    // Вектор для хранения объектов-прямоугольников
    std::vector<Rect> objects;

    // загрузка видео
    VideoCapture cap (DATA_PATH + "/videos/boy-walking.mp4");

    if (!cap.isOpened ()) {
        cerr << "Unable to read video" << endl;
        return EXIT_FAILURE;
    }

    // Переменные для хранения кадров
    Mat frame, frameDisplayDetection, frameDisplay, output;

    // Укажите тип фильтра Калмана
    int type = CV_32F;

    // Инициализируем фильтр Калмана.
    // Внутреннее состояние имеет 6 элементов (x, y, ширина, vx, vy, vw)
    // Измерение имеет 3 элемента (x, y, ширина ).
    // Примечание: высота = 2 x ширина, поэтому она не является частью состояния
    // или измерения.
    KalmanFilter KF (6, 3, 0, type);

    /*
     Transition matrix is of the form
     [
       1, 0, 0, dt, 0,  0,
       0, 1, 0, 0,  dt, 0,
       0, 0, 1, 0,  0,  dt,
       0, 0, 0, 1,  0,  0,
       0, 0, 0, 0,  1,  0,
       0, 0, 0, dt, 0,  1
     ]

     because

     x = x + vx * dt
     y = y + vy * dt
     w = y + vw * dt

     vx = vx
     vy = vy
     vw = vw

     */
    setIdentity (KF.transitionMatrix);

    /*
     Measurement matrix is of the form
     [
      1, 0, 0, 0, 0,  0,
      0, 1, 0, 0, 0,  0,
      0, 0, 1, 0, 0,  0,
     ]

     because we are detecting only x, y and w.
     These quantities are updated.

    */
    setIdentity (KF.measurementMatrix);

    // Переменная для хранения обнаруженных x, y и w
    Mat measurement = Mat::zeros (3, 1, type);

    // Переменные для хранения обнаруженного объекта и отслеживаемого объекта
    Rect objectTracked, objectDetected;

    // Переменные для хранения результатов прогнозирования и обновления (также известные как правильный шаг).
    Mat updatedMeasurement, predictedMeasurement;

    // Переменная для указания того, что измерение было обновлено.
    bool measurementWasUpdated = false;

    // Временная переменная
    double ticks, preTicks;

    // Читать кадры, пока объект не будет обнаружен в первый раз
    while (cap.read (frame)) {

        // Обнаружить объект
        hog.detectMultiScale (frame, objects, weights, hitThreshold, winStride, padding, scale, finalThreshold, useMeanshiftGrouping);

        // Обновить таймер
        ticks = (double)cv::getTickCount ();

        if (objects.size () > 0) {
            // Первый обнаруженный объект
            objectDetected = *std::max_element (objects.begin (), objects.end (), rectAreaComparator);

            // Обновить измерение
            measurement.at<float> (0) = objectDetected.x;
            measurement.at<float> (1) = objectDetected.y;
            measurement.at<float> (2) = objectDetected.width;

            // Обновить состояние. Обратите внимание, что x, y, w установлены на измеренные значения.
            // vx = vy = vw, потому что мы пока не имеем представления о скоростях.
            KF.statePost.at<float> (0) = measurement.at<float> (0);
            KF.statePost.at<float> (1) = measurement.at<float> (1);
            KF.statePost.at<float> (2) = measurement.at<float> (2);
            KF.statePost.at<float> (3) = 0;
            KF.statePost.at<float> (4) = 0;
            KF.statePost.at<float> (5) = 0;

            // Задайте диагональные значения для ковариационных матриц.
            // processNoiseCov is Q
            setIdentity (KF.processNoiseCov, Scalar::all (1e-2));

            // MeasurementNoiseCov — это R
            setIdentity (KF.measurementNoiseCov, Scalar::all (1e-2));
            break;
        }
    }

    // dt for Transition matrix
    double dt = 0;

    // Генератор случайных чисел для случайного выбора кадров для обновления
    RNG rng (0xFFFFFFFF);

    // Цикл по всем кадрам
    while (cap.read (frame)) {
        // Переменная для отображения результата отслеживания
        frameDisplay = frame.clone ();

        // Переменная для отображения результата обнаружения
        frameDisplayDetection = frame.clone ();

        // Обновляем dt для матрицы перехода.
        // dt = time elapsed.

        preTicks = ticks;
        ticks    = (double)cv::getTickCount ();
        dt       = (ticks - preTicks) / cv::getTickFrequency ();

        KF.transitionMatrix.at<float> (3)  = dt;
        KF.transitionMatrix.at<float> (10) = dt;
        KF.transitionMatrix.at<float> (17) = dt;

        // Шаг прогнозирования фильтра Калмана
        predictedMeasurement = KF.predict ();

        // Очистить объекты, обнаруженные в предыдущем кадре.
        objects.clear ();

        // Обнаружение объектов в текущем кадре
        hog.detectMultiScale (frame, objects, weights, hitThreshold, winStride, padding, scale, finalThreshold, useMeanshiftGrouping);

        // Найти самый большой объект
        objectDetected = *std::max_element (objects.begin (), objects.end (), rectAreaComparator);

        // Отображение обнаруженного прямоугольника
        rectangle (frameDisplayDetection, objectDetected, red, 2, 4);

        // Мы обновим измерения в 15% случаев.
        // Кадры выбираются случайным образом.
        bool update = rng.uniform (0.0, 1.0) < 0.15;

        if (update) {
            // Шаг обновления фильтра Калмана
            if (objects.size () > 0) {
                // Копировать x, y, w из обнаруженного прямоугольника
                measurement.at<float> (0) = objectDetected.x;
                measurement.at<float> (1) = objectDetected.y;
                measurement.at<float> (2) = objectDetected.width;

                // Выполнить шаг обновления Калмана
                updatedMeasurement    = KF.correct (measurement);
                measurementWasUpdated = true;
            }
            else {
                // Измерение не обновлено, так как объект не обнаружен
                measurementWasUpdated = false;
            }
        }
        else {
            // Измерение не обновлено
            measurementWasUpdated = false;
        }

        if (measurementWasUpdated) {
            // Использовать обновленное измерение, если измерение было обновлено
            objectTracked = Rect (updatedMeasurement.at<float> (0), updatedMeasurement.at<float> (1), updatedMeasurement.at<float> (2),
              2 * updatedMeasurement.at<float> (2));
        }
        else {
            // Если измерение не было обновлено, используйте прогнозируемые значения.
            objectTracked = Rect (predictedMeasurement.at<float> (0), predictedMeasurement.at<float> (1), predictedMeasurement.at<float> (2),
              2 * predictedMeasurement.at<float> (2));
        }

        // Рисуем отслеживаемый объект
        rectangle (frameDisplay, objectTracked, blue, 2, 4);

        // Текст, указывающий на отслеживание или обнаружение.
        putText (frameDisplay, "Tracking", Point (20, 40), FONT_HERSHEY_SIMPLEX, 0.75, blue, 2);
        putText (frameDisplayDetection, "Detection", Point (20, 40), FONT_HERSHEY_SIMPLEX, 0.75, red, 2);

        // Объединить обнаруженный результат и отслеживаемый результат по вертикали
        vconcat (frameDisplayDetection, frameDisplay, output);

        / Показать результат.imshow ("object Tracker", output);
        int key = waitKey (5);
        // Остановка при нажатии ESC
        if (key == 27) {
            break;
        }
    }
    return EXIT_SUCCESS;
}
