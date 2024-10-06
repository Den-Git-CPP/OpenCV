
#include "opencv2/opencv.hpp"
#include "dataPath.h"
#include <iostream>

using namespace std;
using namespace cv;

int main ()
{

    // Создать объект VideoCapture
    VideoCapture cap (0);

    // Проверяем, успешно ли открылась камера
    if (!cap.isOpened ()) {
        cout << "Error opening video stream or file\n";
        return -1;
    }

    int frame_width  = cap.get (CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get (CAP_PROP_FRAME_HEIGHT);
    VideoWriter outavi (DATA_PATH + "/results/output.avi", cv::VideoWriter::fourcc ('M', 'J', 'P', 'G'), 10, Size (frame_width, frame_height));
    VideoWriter outmp4 (DATA_PATH + "/results/output.mp4", cv::VideoWriter::fourcc ('X', 'V', 'I', 'D'), 10, Size (frame_width, frame_height));

    // Читать и сохранять поток с веб-камеры до нажатия ESC.
    while (true) {

        Mat frame;
        // Захват кадр за кадром
        cap >> frame;

        // Если кадр пуст, немедленно прервать
        if (frame.empty ()) break;

        // Записать кадр
        outavi.write (frame);
        outmp4.write (frame);

        imshow ("Frame", frame);
        char c = (char)waitKey (25);
        if (c == 27) break;
    }

    // Когда все сделано, отпустите объект видеозахвата
    cap.release ();
    outavi.release ();
    outmp4.release ();

    // Закрывает все фреймы
    destroyAllWindows ();

    return 0;
}
