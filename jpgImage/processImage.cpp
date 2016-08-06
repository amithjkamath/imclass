//
// Created by Amith J. Kamath on 6/15/16.
//

#include "processImage.h"
#include "image.h"

template <typename T>
T addScalarToPixel(T pixelVal, T value)
{
    pixelVal += value;
    if(pixelVal > 255)
    {
        pixelVal = 255;
    }
    else if (pixelVal < 0)
    {
        pixelVal = 0;
    }

    return pixelVal;
}

template <typename T>
void addScalarToImage(image<T>*  inputImage, int value)
{
    for(int y = 0; y < inputImage->getHeight(); y++)
    {
        for(int x = 0; x < inputImage->getWidth(); x++)
        {
            // pixel[0] is the R channel, 1 is G, and 2 is B.
            //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, pixel[0], pixel[1], pixel[2], pixel[3]);
            T Rvalue = inputImage->getPixelValueAt(x, y, 0);
            Rvalue = addScalarToPixel<T>(Rvalue, value);
            inputImage->setPixelValueAt(Rvalue, x, y, 0);
            T Gvalue = inputImage->getPixelValueAt(x, y, 1);
            Gvalue = addScalarToPixel<T>(Gvalue, value);
            inputImage->setPixelValueAt(Gvalue, x, y, 1);
            T Bvalue = inputImage->getPixelValueAt(x, y, 2);
            Bvalue = addScalarToPixel<T>(Bvalue, value);
            inputImage->setPixelValueAt(Bvalue, x, y, 2);
            inputImage->setPixelValueAt(255, x, y, 3);
        }
    }
}

template <typename T>
T convertRGBPixelToGray(T Rpx, T Gpx, T Bpx)
{
    return (T) ((double)Rpx * 0.2989 + (double)Gpx * 0.5870 + (double)Bpx * 0.1140);
}

template <typename T>
void convertRGBImageToGray(image<T>* inputImage)
{
    for(int y = 0; y < inputImage->getHeight(); y++)
    {
        for(int x = 0; x < inputImage->getWidth(); x++)
        {
            // pixel[0] is the R channel, 1 is G, and 2 is B.
            //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, pixel[0], pixel[1], pixel[2], pixel[3]);
            // Get pixel values from R, G and B channels.
            T Rvalue = inputImage->getPixelValueAt(x, y, 0);
            T Gvalue = inputImage->getPixelValueAt(x, y, 1);
            T Bvalue = inputImage->getPixelValueAt(x, y, 2);
            // Compute the grayscale value.
            T grayVal = convertRGBPixelToGray<T>(Rvalue, Gvalue, Bvalue);
            // Write the gray values to all the three channels.
            inputImage->setPixelValueAt(grayVal, x, y, 0);
            inputImage->setPixelValueAt(grayVal, x, y, 1);
            inputImage->setPixelValueAt(grayVal, x, y, 2);
            inputImage->setPixelValueAt(255, x, y, 3);
        }
    }
}

template <typename T>
void convertRGBImageToSepia(image<T> * inputImage)
{
    for(int y = 0; y < inputImage->getHeight(); y++)
    {
        for(int x = 0; x < inputImage->getWidth(); x++)
        {
            // pixel[0] is the R channel, 1 is G, and 2 is B.
            //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, pixel[0], pixel[1], pixel[2], pixel[3]);
            // Get pixel values from R, G and B channels.
            float Rvalue = (float)inputImage->getPixelValueAt(x, y, 0);
            float Gvalue = (float)inputImage->getPixelValueAt(x, y, 1);
            float Bvalue = (float)inputImage->getPixelValueAt(x, y, 2);
            // Compute the grayscale value.
            T outputRed = (T)((Rvalue * .393) + (Gvalue *.769) + (Bvalue * .189));
            T outputGreen = (T)((Rvalue * .349) + (Gvalue *.686) + (Bvalue * .168));
            T outputBlue = (T)((Rvalue * .272) + (Gvalue *.534) + (Bvalue * .131));
            // Write the gray values to all the three channels.
            inputImage->setPixelValueAt(outputRed, x, y, 0);
            inputImage->setPixelValueAt(outputGreen, x, y, 1);
            inputImage->setPixelValueAt(outputBlue, x, y, 2);
            inputImage->setPixelValueAt(255, x, y, 3);
        }
    }
}

template <typename T>
void thresholdImageAt(image<T> * inputImage, int threshold)
{
    for(int y = 0; y < inputImage->getHeight(); y++)
    {
        for(int x = 0; x < inputImage->getWidth(); x++)
        {
            // pixel[0] is the R channel, 1 is G, and 2 is B.
            //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, pixel[0], pixel[1], pixel[2], pixel[3]);
            // Get pixel values from R, G and B channels.
            T Rvalue = inputImage->getPixelValueAt(x, y, 0);
            T Gvalue = inputImage->getPixelValueAt(x, y, 1);
            T Bvalue = inputImage->getPixelValueAt(x, y, 2);
            // Compute the grayscale value.
            T grayVal = convertRGBPixelToGray<T>(Rvalue, Gvalue, Bvalue);
            // Threshold the image, using the threshold and the grayvalue.
            if(grayVal > threshold) grayVal = 255; else grayVal = 0;
            // Write the true or false result to all three channels.
            inputImage->setPixelValueAt(grayVal, x, y, 0);
            inputImage->setPixelValueAt(grayVal, x, y, 1);
            inputImage->setPixelValueAt(grayVal, x, y, 2);
            inputImage->setPixelValueAt(255, x, y, 3);
        }
    }
}

// Forward declarations for the linker to be happy.
template void addScalarToImage(image<int>*  inputImage, int value);
template void addScalarToImage(image<float>*  inputImage, int value);

template void thresholdImageAt(image<int>*  inputImage, int value);
template void thresholdImageAt(image<float>*  inputImage, int value);

template void convertRGBImageToGray(image<int>*  inputImage);
template void convertRGBImageToGray(image<float>*  inputImage);