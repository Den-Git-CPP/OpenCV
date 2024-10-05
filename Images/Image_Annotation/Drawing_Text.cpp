// Include libraries
#include <iostream>
#include "dataPath.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main (void)
{

    string imageName = DATA_PATH + "/images/boy.jpg";

    Mat image;
    image = imread (imageName, IMREAD_COLOR);

    Mat imageText = image.clone ();
    string text   = "I am studying";
    //
    double fontScale  = 1.5;
    int fontFace      = FONT_HERSHEY_SIMPLEX;
    Scalar fontColor  = Scalar (250, 10, 10);
    int fontThickness = 2;
    // Разместить текст на изображении
    putText (imageText, text, Point (20, 350), fontFace, fontScale, fontColor, fontThickness, LINE_AA);

    imwrite (DATA_PATH + "/results/text.jpg", imageText);
    imshow ("Drawing text on image", imageText);
 
    int pixelHeight = 20;
    // Рассчитать fontScale
    fontScale = getFontScaleFromHeight (fontFace, pixelHeight, fontThickness);
    cout << "fontScale = " << fontScale << endl;

    Mat imageTextFontScale;
    imageTextFontScale = image.clone ();
    putText (imageTextFontScale, text, Point (20, 350), fontFace, fontScale, fontColor, fontThickness, LINE_AA);

    imwrite (DATA_PATH + "/results/text2.jpg", imageTextFontScale);
    imshow ("Text written using fontScale", imageTextFontScale);

    Mat imageGetTextSize;
    imageGetTextSize = image.clone ();
    int imageHeight  = imageGetTextSize.rows;
    int imageWidth   = imageGetTextSize.cols;

    // Получить высоту и ширину текстового поля, а также базовую линию
    int baseLine   = 0;
    Size textSize  = getTextSize (text, fontFace, fontScale, fontThickness, &baseLine);
    int textWidth  = textSize.width;
    int textHeight = textSize.height;

    cout << "TextWidth = " << textWidth << ", TextHeight = " << textHeight << ", baseLine = " << baseLine << endl;
    // Получить координаты нижнего левого угла текстового поля
    // Координата x будет такой, что текст будет центрирован
    int xcoordinate = (imageWidth - textWidth) / 2;
    // Координата Y будет такой, что весь блок будет всего на 10 пикселей выше нижней части изображения
    int ycoordinate = (imageHeight - baseLine - 10);

    cout << "TextBox Bottom Left = (" << xcoordinate << "," << ycoordinate << ")" << endl;

    // Нарисуйте холст, используя закрашенный прямоугольник
    Scalar canvasColor = Scalar (255, 255, 255);
    Point canvasBottomLeft (xcoordinate, ycoordinate + baseLine);
    Point canvasTopRight (xcoordinate + textWidth, ycoordinate - textHeight);

    rectangle (imageGetTextSize, canvasBottomLeft, canvasTopRight, canvasColor, -1);

    cout << "Canvas Bottom Left = " << canvasBottomLeft << ", Top Right = " << canvasTopRight << endl;

    // Теперь нарисуем базовую линию (просто для справки)
    int lineThickness = 2;
    Point lineLeft (xcoordinate, ycoordinate);
    Point lineRight (xcoordinate + textWidth, ycoordinate);
    Scalar lineColor = Scalar (0, 255, 0);

    line (imageGetTextSize, lineLeft, lineRight, lineColor, lineThickness, LINE_AA);

    // Наконец рисуем текст
    putText (imageGetTextSize, text, Point (xcoordinate, ycoordinate), fontFace, fontScale, fontColor, fontThickness, LINE_AA);

    imwrite (DATA_PATH + "/results/text3.jpg", imageGetTextSize);

    imshow ("Write image using calculated text size", imageGetTextSize);
    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

    return 0;
}
