//
// Created by Amith J. Kamath on 6/15/16.
//

#ifndef PNGIMAGEREAD_PROCESSIMAGE_H
#define PNGIMAGEREAD_PROCESSIMAGE_H

#include "image.h"

template <typename T = int>
T addScalarToPixel(T pixelVal, T value);

template <typename T = int>
T convertRGBPixelToGray(T Rpx, T Gpx, T Bpx);

template <typename T>
void addScalarToImage(image<T> * inputImage, int value);

template <typename T>
void thresholdImageAt(image<T> * inputImage, int threshold);

template <typename T>
void convertRGBImageToGray(image<T> * inputImage);

template <typename T>
void convertRGBImageToSepia(image<T> * inputImage);

#endif //PNGIMAGEREAD_PROCESSIMAGE_H
