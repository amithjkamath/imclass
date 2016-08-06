//
// Created by Amith J. Kamath on 6/14/16.
//

#include "image.h"

// Constructor
template <typename T>
image<T>::image()
{
    setWidth(0);
    setHeight(0);
    setBitDepth(0);
}

template <typename T>
image<T>::~image()
{

}

template <typename T>
int image<T>::getHeight()
{
    return _height;
}

template <typename T>
void image<T>::setHeight(int height)
{
    _height = height;
}

template <typename T>
int image<T>::getWidth()
{
    return _width;
}

template <typename T>
void image<T>::setWidth(int width)
{
    _width = width;
}

template <typename T>
int image<T>::getBitDepth()
{
    return _bitdepth;
}

template <typename T>
void image<T>::setBitDepth(int bitdepth)
{
    _bitdepth = bitdepth;
}

// Forward declaration of int and float type.
template class image<int>;
template class image<float>;