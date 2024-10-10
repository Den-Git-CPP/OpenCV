#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/photo.hpp"
#include "dataPath.h"
#include <iostream>

using namespace cv;
using namespace std;

// Объявляем объекты Mat для исходного изображения и маску для зарисовки
Mat img, inpaintMask;
// Объект Mat для вывода результата
Mat res;
Point prevPt (-1, -1);

// функция onMouse для обработки мыши
// Используется для рисования областей, необходимых для закрашивания
static void onMouse (int event, int x, int y, int flags, void*)
{
    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
        prevPt = Point (-1, -1);
    else if (event == EVENT_LBUTTONDOWN)
        prevPt = Point (x, y);
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
        Point pt (x, y);
        if (prevPt.x < 0) prevPt = pt;
        line (inpaintMask, prevPt, pt, Scalar::all (255), 5, 8, 0);
        line (img, prevPt, pt, Scalar::all (255), 5, 8, 0);
        prevPt = pt;
        imshow ("image", img);
        imshow ("image: mask", inpaintMask);
    }
}

int main (int argc, char** argv)
{
    cout << "Usage: ./inpaint <image_path>" << endl;
    cout << "Keys: " << endl;
    cout << "t - inpaint using FMM" << endl;
    cout << "n - inpaint using NS technique" << endl;
    cout << "r - reset the inpainting mask" << endl;
    cout << "ESC - exit" << endl;

    string filename;
    if (argc > 1)
        filename = argv [1];
    else
        filename = DATA_PATH + "/images/sample.jpg";

    // Прочитать изображение в цветном режиме
    img = imread (filename, IMREAD_COLOR);
    Mat img_mask;
    // Возвращает ошибку, если изображение не считано правильно
    if (img.empty ()) {
        cout << "Failed to load image: " << filename << endl;
        return 0;
    }

    namedWindow ("image", WINDOW_AUTOSIZE);

    // Создать копию исходного изображения
    img_mask = img.clone ();
    // Инициализируем маску (черное изображение)
    inpaintMask = Mat::zeros (img_mask.size (), CV_8U);

    // Показать исходное изображение
    imshow ("image", img);
    setMouseCallback ("image", onMouse, NULL);

    for (;;) {
        char c = (char)waitKey ();
        if (c == 't') {
            // Используйте алгоритм, предложенный Алексендрой Телеа
            inpaint (img, inpaintMask, res, 3, INPAINT_TELEA);
            imshow ("Inpaint Output using FMM", res);
        }
        if (c == 'n') {
            // Используйте алгоритм, предложенный Бертальмио и др.
            inpaint (img, inpaintMask, res, 3, INPAINT_NS);
            imshow ("Inpaint Output using NS Technique", res);
        }
        if (c == 'r') {
            inpaintMask = Scalar::all (0);
            img_mask.copyTo (img);
            imshow ("image", inpaintMask);
        }
        if (c == 27) break;
    }
    return 0;
}
