#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "dataPath.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

// Точки для хранения центра круга и точки на окружности
Point center, circumference;
// Исходное изображение
Mat source;

// функция, которая будет вызвана при вводе мыши
void drawCircle (int action, int x, int y, int flags, void* userdata)
{
    // Действие, которое необходимо выполнить при нажатии левой кнопки мыши
    if (action == EVENT_LBUTTONDOWN) {
        center = Point (x, y);
        // Отметьте центр
        circle (source, center, 1, Scalar (255, 255, 0), 2, LINE_AA);
    }
    // Действие, которое необходимо выполнить при отпускании левой кнопки мыши
    else if (action == EVENT_LBUTTONUP) {
        circumference = Point (x, y);
        // Рассчитать радиус окружности
        float radius = sqrt (pow (center.x - circumference.x, 2) + pow (center.y - circumference.y, 2));
        // Нарисуем круг
        circle (source, center, radius, Scalar (0, 255, 0), 2, LINE_AA);
        imshow ("Window", source);
    }
}

int main ()
{
    source = imread (DATA_PATH + "/images/sample.jpg", 1);
    // Создадим фиктивное изображение, оно будет полезно для очистки рисунка
    Mat dummy = source.clone ();
    namedWindow ("Window");
    // функция highgui вызывается при возникновении событий мыши
    setMouseCallback ("Window", drawCircle);
    int k = 0;
    // цикл до тех пор, пока не будет нажат символ escape
    while (k != 27) {
        imshow ("Window", source);
        putText (source, "Choose center, and drag, Press ESC to exit and c to clear", Point (10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar (255, 255, 255), 2);
        k = waitKey (20) & 0xFF;
        if (k == 99)
            // Другой способ клонирования
            dummy.copyTo (source);
    }
    return 0;
}
