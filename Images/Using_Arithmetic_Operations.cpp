#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "dataPath.h"

using namespace std;
using namespace cv;

int main (void)
{
    // Make the dimensions of the mask same as the input image.
    // Since Face Image is a 3-channel image, we create a 3 channel image for the mask
    Mat glassMask1 = imread (DATA_PATH + "/results/sunglassAlpha.png", 0);
    Mat glassBGR   = imread (DATA_PATH + "/results/sunglassRGB.png");
    Mat glassMask;
    Mat glassMaskChannels [] = { glassMask1, glassMask1, glassMask1 };
    merge (glassMaskChannels, 3, glassMask);
    // Make the values [0,1] since we are using arithmetic operations
    glassMask = glassMask / 255;

    // Load the Face Image
    string faceImagePath = DATA_PATH + "/images/musk.jpg";
    Mat faceImage        = imread (faceImagePath);

    // Make a copy
    Mat faceWithGlassesArithmetic = faceImage.clone ();

    // Get the eye region from the face image
    Mat eyeROI = faceWithGlassesArithmetic (Range (150, 250), Range (140, 440));

    Mat eyeROIChannels [3];
    split (eyeROI, eyeROIChannels);
    Mat maskedEyeChannels [3];
    Mat maskedEye;

    for (int i = 0; i < 3; i++) {
        // Use the mask to create the masked eye region
        multiply (eyeROIChannels [i], (1 - glassMaskChannels [i]), maskedEyeChannels [i]);
    }

    merge (maskedEyeChannels, 3, maskedEye);

    Mat maskedGlass;
    // Use the mask to create the masked sunglass region
    multiply (glassBGR, glassMask, maskedGlass);

    Mat eyeRoiFinal;
    // Combine the Sunglass in the Eye Region to get the augmented image
    add (maskedEye, maskedGlass, eyeRoiFinal);

    imwrite (DATA_PATH + "/results/maskedEyeRegion.png", maskedEye);
    imwrite (DATA_PATH + "/results/maskedSunglassRegion.png", maskedGlass);
    imwrite (DATA_PATH + "/results/augmentedEyeAndSunglass.png", eyeRoiFinal);

    imshow ("Masked eye region", maskedEye);
    imshow ("Masked Sunglass Region", maskedGlass);
    imshow ("Augmented Eye and Sunglass", eyeRoiFinal);

    // Replace the eye ROI with the output from the previous section
    eyeRoiFinal.copyTo (eyeROI);

    imwrite (DATA_PATH + "/results/withSunglasses.png", faceWithGlassesArithmetic);

    imshow ("With Sunglasses", faceWithGlassesArithmetic);

    if (cv::waitKey (0) == 27) {
        std::cout << "Esc key is pressed by user. Stoppig the image\n";
        exit;
    }
    destroyAllWindows ();

    return 0;
}
