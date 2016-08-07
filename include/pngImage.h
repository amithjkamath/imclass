//
// Created by Amith J. Kamath on 6/13/16.
//

#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include <png.h>
#include "image.h"
#include <string>

template <typename T>
class pngImage : public image<T>
{
public:
    // Constructor
    pngImage(std::string filename);
    png_bytep *getData();

    T getPixelValueAt(int x, int y, int channel = 0);
    void setPixelValueAt(T value, int x, int y, int channel = 0);
    virtual ~pngImage();

    void writeToFile(std::string filename);

private:
    void setStruct();
    void setInfo();
    void setColorType();

    // Inherited from image: overridden here.
    virtual void setWidth(int );
    virtual void setHeight(int );
    virtual void setBitDepth(int );

    png_structp _pngStruct;
    png_infop   _pngInfo;
    png_byte    _pngColorType;
    png_bytep*  _rowPointers;
};


#endif //PNGIMAGE_H
