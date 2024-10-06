#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

int main (void)
{
    // Открыть веб-камеру
    VideoCapture cap (0);
    Mat frame;
    int k = 0;
    // Определить, правильно ли работает веб-камера
    if (!cap.isOpened ()) {
        cout << "Unable to detect webcam \n";
        return 0;
    }
    else {
        while (true) {
            // Захват кадра
            cap >> frame;
            if (k == 27) break;
            // Определить, нажата ли клавиша «e» или «E»
            if (k == 101 || k == 69)
                putText (frame, "E is pressed, press Z or ESC", Point (100, 180), FONT_HERSHEY_SIMPLEX, 1, Scalar (0, 255, 0), 3);

            // Определить, нажата ли клавиша «z» или «Z» или нет
            if (k == 90 || k == 122) putText (frame, "Z is pressed", Point (100, 180), FONT_HERSHEY_SIMPLEX, 1, Scalar (0, 255, 0), 3);
            imshow ("Image", frame);
            // Waitkey увеличивается, чтобы отобразить дисплей
            k = waitKey (10000) & 0xFF;
        }
    }
    cap.release ();
    destroyAllWindows ();
}
