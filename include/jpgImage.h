//
// Created by Amith J. Kamath on 6/13/16.
//

#ifndef JPGIMAGE_H
#define JPGIMAGE_H

#include <stdio.h> // FILE and size_t are not defined in jpeglib.h, and will fail to compile other wise.
#include "jpeglib.h"
#include "image.h"
#include <string>

template <typename T>
class jpgImage : public image<T>
{
public:
    // Constructor
    jpgImage(std::string filename);

    T getPixelValueAt(int x, int y, int channel = 0);
    void setPixelValueAt(T value, int x, int y, int channel = 0);
    virtual ~jpgImage();

    void writeToFile(std::string filename, int quality = 100);

private:

    unsigned char* getData();
    // Inherited from image: overridden here.
    virtual void setWidth(int );
    virtual void setHeight(int );
    virtual void setBitDepth(int );

    /* This struct contains the JPEG decompression parameters and pointers to
     * working space (which is allocated as needed by the JPEG library).
     */
    struct jpeg_decompress_struct cinfo;
    /* We use our private extension JPEG error handler.
     * Note that this struct must live as long as the main JPEG parameter
     * struct, to avoid dangling-pointer problems.
     */
    unsigned char * image_buffer;
};


#endif //PNGIMAGE_H
