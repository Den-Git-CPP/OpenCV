//https://learnopencv.com/contour-detection-using-opencv-python-c/#What-are-Contours
#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>

using namespace std;
using namespace cv;

int main (int argc, char const* argv [])
{
    // прочитать изображение
    Mat image = imread ("img1.png");
    // преобразовать изображение в формат оттенков серого
    Mat img_gray;
    // cvtColor() функция для преобразования исходного RGB-изображения в изображение в оттенках серого.
    cvtColor (image, img_gray, COLOR_BGR2GRAY);
    // применить двоичное пороговое значение
    Mat thresh;
    threshold (img_gray, thresh, 150, 255, THRESH_BINARY);
    imshow ("Binary mage", thresh);
    waitKey (0);
    /*
    * Рисование контуров CHAIN_APPROX_NONE.
    * Начните с функции findContours() . Eсть три обязательных аргумента

    * image: Двоичное входное изображение img_gray
    * mode: Это режим поиска контуров. Мы предоставили это как RETR_TREE, что означает, что алгоритм извлекает все возможные контуры из двоичного
    * изображения.
    * method: Это определяет метод аппроксимации контура.  CHAIN_APPROX_NONE.Хотя и немного медленнее,чем CHAIN_APPROX_SIMPLE, мы будем использовать
    * этот метод здесь, чтобы сохранить ВСЕ точки контура.

    * Дополнительные аргументы приведены на странице документации CHAIN_APPROX_NONE
    * https://docs.opencv.org/4.x/d3/dc0/group__imgproc__shape.html#gadf1ad6a0b82947fa1fe3c3d497f260e0

    *  Затем используйте функцию drawContours() для наложения контуров на изображение RGB.
    *  Первые четыре аргумента ниже обязательны. Дополнительные аргументы приведены на странице документации. здесь.
    *
    *  image: Это входное RGB-изображение, на котором вы хотите нарисовать контур.
    *  contours: Указывает на значение contours , полученное с помощью функции findContours() .
    *  contourIdx: Пиксельные координаты точек контура перечислены в полученных контурах. Используя этот аргумент, вы можете указать позицию  индекса
    *  из этого списка, указывая, какую именно точку контура вы хотите нарисовать. При указании отрицательного значения будут прорисованы все точки контура.
    *  color: Это указывает цвет точек контура, которые вы хотите нарисовать. Мы рисуем точки зеленым цветом.
    *  thickness: Это толщина точек контура.
    */

    // detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours (thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

    // draw contours on the original image
    Mat image_copy = image.clone ();
    drawContours (image_copy, contours, -1, Scalar (0, 255, 0), 2);
    imshow ("None approximation", image_copy);
    waitKey (0);
    // imwrite ("contours_none_image1.jpg", image_copy);

    // Разделение каналов B, G, R
    Mat channels [3];
    split (image, channels);

    // обнаружить контуры с использованием синего канала и без порогового значения
    vector<vector<Point>> contours1;
    vector<Vec4i> hierarchy1;
    findContours (channels [0], contours1, hierarchy1, RETR_TREE, CHAIN_APPROX_NONE);
    // необработанные контуры на исходном изображении
    Mat image_contour_blue = image.clone ();
    drawContours (image_contour_blue, contours1, -1, Scalar (0, 255, 0), 2);
    imshow ("Contour detection using blue channels only", image_contour_blue);
    waitKey (0);
    // imwrite ("blue_channel.jpg", image_contour_blue);

    // обнаружить контуры с использованием зеленого канала и без порогового значения
    vector<vector<Point>> contours2;
    vector<Vec4i> hierarchy2;
    findContours (channels [1], contours2, hierarchy2, RETR_TREE, CHAIN_APPROX_NONE);
    // нарисуйте контуры на исходном изображении
    Mat image_contour_green = image.clone ();
    drawContours (image_contour_green, contours2, -1, Scalar (0, 255, 0), 2);
    imshow ("Contour detection using green channels only", image_contour_green);
    waitKey (0);
    // imwrite ("green_channel.jpg", image_contour_green);

    // обнаружить контуры с использованием красного канала и без порогового значения
    vector<vector<Point>> contours3;
    vector<Vec4i> hierarchy3;
    findContours (channels [2], contours3, hierarchy3, RETR_TREE, CHAIN_APPROX_NONE);
    // нарисуйте контуры на исходном изображении
    Mat image_contour_red = image.clone ();
    drawContours (image_contour_red, contours3, -1, Scalar (0, 255, 0), 2);
    imshow ("Contour detection using red channels only", image_contour_red);
    waitKey (0);
    // imwrite ("red_channel.jpg", image_contour_red);

    // Теперь давайте попробуем с CHAIN_APPROX_SIMPLE
    // определение контуров на бинарном изображении с помощью cv2.CHAIN_APPROX_NONE
    vector<vector<Point>> contours1_simple;
    vector<Vec4i> hierarchy1_simple;
    findContours (thresh, contours1_simple, hierarchy1_simple, RETR_TREE, CHAIN_APPROX_SIMPLE);
    // рисуем контуры на исходном изображении
    Mat image_copy1_simple = image.clone ();
    drawContours (image_copy1_simple, contours1_simple, -1, Scalar (0, 255, 0), 2);
    imshow ("Simple approximation", image_copy1_simple);
    waitKey (0);
    // imwrite ("contours_simple_image1.jpg", image_copy1_simple);

    destroyAllWindows ();
    return 0;
}
