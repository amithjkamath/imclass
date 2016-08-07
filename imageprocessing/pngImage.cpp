/* Inspired from:
 * A simple libpng example program
 * http://zarb.org/~gc/html/libpng.html
 *
 * Modified by Yoshimasa Niwa to make it much simpler
 * and support all defined color_type.
 *
 * To build, use the next instruction on OS X.
 * $ brew install libpng
 * $ clang -lz -lpng15 libpng_test.c
 *
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */

//
// Created by Amith J. Kamath on 6/13/16.
//

#include "pngImage.h"
#include <cstdlib>

template <typename T>
pngImage<T>::pngImage(std::string filename):
image<T>(),
_pngStruct(NULL),
_pngInfo(NULL),
_rowPointers(NULL),
_pngColorType(0)
{
    setStruct();
    FILE *fp = fopen(filename.c_str(), "rb");
    png_init_io(_pngStruct, fp);
    setInfo();

    setWidth((int)png_get_image_width(_pngStruct, _pngInfo));
    setHeight((int)png_get_image_height(_pngStruct, _pngInfo));
    setBitDepth((int)png_get_bit_depth(_pngStruct, _pngInfo));
    setColorType();

    png_read_update_info(_pngStruct, _pngInfo);

    _rowPointers = (png_bytep*)malloc(sizeof(png_bytep) * this->getHeight());
    for(int y = 0; y < this->getHeight(); y++) {
        _rowPointers[y] = (png_byte*)malloc(png_get_rowbytes(_pngStruct,_pngInfo));
    }

    png_read_image(_pngStruct, _rowPointers);

    fclose(fp);
}

template <typename T>
T pngImage<T>::getPixelValueAt(int x, int y, int channel)
{
    png_bytep *dataPtr = getData();
    png_bytep rowPtr = dataPtr[y];
    png_bytep pixel = &(rowPtr[x * 4]);
    return (T)pixel[channel];
}

template <typename T>
void pngImage<T>::setPixelValueAt(T value, int x, int y, int channel)
{
    png_bytep *dataPtr = getData();
    png_bytep rowPtr = dataPtr[y];
    png_bytep pixel = &(rowPtr[x * 4]);
    pixel[channel] = (png_byte)value;
}

template <typename T>
pngImage<T>::~pngImage()
{
    for(int y = 0; y < this->getHeight(); y++) {
        free(_rowPointers[y]);
    }
    free(_rowPointers);
}

template <typename T>
void pngImage<T>::setStruct()
{
    _pngStruct= png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!_pngStruct)
        abort();

    if(setjmp(png_jmpbuf(_pngStruct)))
        abort();

}

template <typename T>
void pngImage<T>::setWidth(int width)
{
    if((_pngStruct != NULL) && (_pngInfo != NULL))
        this->_width = width;
    else
        this->_width = 0;
}

template <typename T>
void pngImage<T>::setHeight(int height)
{
    if((_pngStruct != NULL) && (_pngInfo != NULL))
        this->_height = height;
    else
        this->_height = 0;
}

template <typename T>
void pngImage<T>::setBitDepth(int depth)
{
    if((_pngStruct != NULL) && (_pngInfo != NULL))
    {
        this->_bitdepth  = depth;
        // Read any color_type into 8bit depth, RGBA format.
        // See http://www.libpng.org/pub/png/libpng-manual.txt
        if(depth == 16)
            png_set_strip_16(_pngStruct);
    }
    else
        this->_bitdepth = 0;
}

template <typename T>
void pngImage<T>::setColorType()
{
    _pngColorType = png_get_color_type(_pngStruct, _pngInfo);
    if(_pngColorType == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(_pngStruct);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(_pngColorType == PNG_COLOR_TYPE_GRAY && this->getBitDepth() < 8)
        png_set_expand_gray_1_2_4_to_8(_pngStruct);

    if(png_get_valid(_pngStruct, _pngInfo, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(_pngStruct);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(_pngColorType == PNG_COLOR_TYPE_RGB ||
       _pngColorType == PNG_COLOR_TYPE_GRAY ||
       _pngColorType == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(_pngStruct, 0xFF, PNG_FILLER_AFTER);
    if(_pngColorType == PNG_COLOR_TYPE_GRAY ||
       _pngColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(_pngStruct);
}

template <typename T>
void pngImage<T>::setInfo()
{
    if(_pngStruct != NULL)
    {
        _pngInfo = png_create_info_struct(_pngStruct);
        if(!_pngInfo)
            abort();
        png_read_info(_pngStruct, _pngInfo);
    }
    else
        abort();
}

template <typename T>
png_bytep *pngImage<T>::getData()
{
    return _rowPointers;
}

template <typename T>
void pngImage<T>::writeToFile(std::string filename)
{
    int y;

    FILE *fp = fopen(filename.c_str(), "wb");
    if(!fp)
        abort();
    png_structp pngWStruct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pngWInfo = png_create_info_struct(pngWStruct);

    png_init_io(pngWStruct, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(pngWStruct, pngWInfo, this->getWidth(), this->getHeight(), 8,
                 PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    png_write_info(pngWStruct, pngWInfo);

    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
    // Use png_set_filler().
    //png_set_filler(png, 0, PNG_FILLER_AFTER);

    png_write_image(pngWStruct, _rowPointers);
    png_write_end(pngWStruct, NULL);

    fclose(fp);
}

// Forward declaration of pngImage with ints.
template class pngImage<int>;
template class pngImage<float>;
