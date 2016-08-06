//
// Created by Amith J. Kamath on 6/14/16.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <string>

// This is an abstract base class, which determines the common interface for all image classes.
// Everything common in all the derived classes are pushed up here.

template <typename T>
class image
{
public:
    // Constructor
    image();

    virtual int getHeight();
    virtual int getWidth();
    virtual int getBitDepth();

    // These methods are not defined, image is abstract.
    virtual T getPixelValueAt(int x, int y, int channel = 0) = 0;
    virtual void setPixelValueAt(T value, int x, int y, int channel = 0) = 0;

    int numberOfPixels()
    {
        return getWidth()*getHeight();
    }
    //void writeToFile(std::string filename);
    virtual ~image();

protected:

    virtual void setWidth(int );
    virtual void setHeight(int );
    virtual void setBitDepth(int );

    int _width;
    int _height;
    int _bitdepth;
};


#endif //IMAGE_H
