#include "opencv2/opencv.hpp"
#include <iostream>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main ()
{

    VideoCapture cap (DATA_PATH + "/videos/chaplin.mp4");
    // Проверяем, успешно ли открылась камера, и считываем кадр из крышки объекта
    if (!cap.isOpened ()) {
        cout << "Error opening video stream or file\n";
        return -1;
    }

    while (true) {
        Mat frame;
        // Захват кадр за кадром
        cap >> frame;
        // Если кадр пуст, немедленно прервать
        if (frame.empty ()) break;
        // Отображаем полученный кадр
        imshow ("Frame", frame);
        // Нажмите ESC на клавиатуре, чтобы выйти
        char c = (char)waitKey (25);
        if (c == 27) break;
    }

    // Когда все сделано, отпустите объект видеозахвата
    cap.release ();

    // Закрывает все фреймы
    destroyAllWindows ();

    return 0;
}
