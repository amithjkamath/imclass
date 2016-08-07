// Inspired by: https://github.com/LuaDist/libjpeg/blob/master/example.c
// Created by Amith J. Kamath on 6/13/16.
//

#include <stdio.h> // FILE and size_t are not defined in jpeglib.h, and will fail to compile other wise.
#include "jpeglib.h"
#include "jpgImage.h"
#include <cstdlib>

template <typename T>
jpgImage<T>::jpgImage(std::string filename):
image<T>()
{
    FILE * infile;		/* source file */
    JSAMPARRAY buffer;		/* Output row buffer */
    int row_stride;		/* physical row width in output buffer */
    /* In this example we want to open the input file before doing anything else,
     * so that the setjmp() error recovery below can assume the file is open.
     * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
     * requires it in order to read binary files.
     */
    struct jpeg_error_mgr err;          //the error handler
    cinfo.err = jpeg_std_error( &err);

    if ((infile = fopen(filename.c_str(), "rb")) == NULL) {
        abort();
    }

    /* Step 1: allocate and initialize JPEG decompression object */


    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);

    /* Step 2: specify data source (eg, a file) */

    jpeg_stdio_src(&cinfo, infile);

    /* Step 3: read file parameters with jpeg_read_header() */

    (void) jpeg_read_header(&cinfo, TRUE);
    /* We can ignore the return value from jpeg_read_header since
     *   (a) suspension is not possible with the stdio data source, and
     *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
     * See libjpeg.txt for more info.
     */

    /* Step 4: set parameters for decompression */

    /* In this example, we don't need to change any of the defaults set by
     * jpeg_read_header(), so we do nothing here.
     */

    /* Step 5: Start decompressor */

    (void) jpeg_start_decompress(&cinfo);
    /* We can ignore the return value since suspension is not possible
     * with the stdio data source.
     */

    /* We may need to do some setup of our own at this point before reading
     * the data.  After jpeg_start_decompress() we have the correct scaled
     * output image dimensions available, as well as the output colormap
     * if we asked for color quantization.
     * In this example, we need to make an output work buffer of the right size.
     */
    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;

    setWidth(cinfo.output_width);
    setHeight(cinfo.output_height);
    setBitDepth(cinfo.output_components);

    image_buffer = new unsigned char[ this->getWidth() * this->getHeight() * this->getBitDepth()];
    /* Make a one-row-high sample array that will go away when done with image */
    buffer = (*cinfo.mem->alloc_sarray)
            ((j_common_ptr) &cinfo, JPOOL_IMAGE, (JDIMENSION)row_stride, 1);

    /* Step 6: while (scan lines remain to be read) */
    /*           jpeg_read_scanlines(...); */

    /* Here we use the library's state variable cinfo.output_scanline as the
     * loop counter, so that we don't have to keep track ourselves.
     */
    int counter = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        /* jpeg_read_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could ask for
         * more than one scanline at a time if that's more convenient.
         */
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(image_buffer+counter, buffer[0], row_stride);
        counter += row_stride;

        /* Assume put_scanline_someplace wants a pointer and sample count. */
    }

    /* Step 7: Finish decompression */

    (void) jpeg_finish_decompress(&cinfo);
    /* We can ignore the return value since suspension is not possible
     * with the stdio data source.
     */

    /* Step 8: Release JPEG decompression object */

    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_decompress(&cinfo);

    /* After finish_decompress, we can close the input file.
     * Here we postpone it until after no more JPEG errors are possible,
     * so as to simplify the setjmp error logic above.  (Actually, I don't
     * think that jpeg_destroy can do an error exit, but why assume anything...)
     */
    fclose(infile);

    /* At this point you may want to check to see whether any corrupt-data
     * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
     */
}

template <typename T>
jpgImage<T>::~jpgImage()
{
    delete image_buffer;
    image_buffer = NULL;
}

template <typename T>
T jpgImage<T>::getPixelValueAt(int x, int y, int channel)
{
    unsigned char* dataPtr = getData();
    int row_stride = this->getWidth() * this->getBitDepth();
    unsigned char* rowPtr = &dataPtr[y*row_stride + x*this->getBitDepth()];
    unsigned char pixel = *(rowPtr + channel);
    return (T)pixel;
}

template <typename T>
void jpgImage<T>::setPixelValueAt(T value, int x, int y, int channel)
{
    unsigned char* dataPtr = getData();
    int row_stride = this->getWidth() * this->getBitDepth();
    unsigned char* rowPtr = &dataPtr[y*row_stride + x*this->getBitDepth()];
    *(rowPtr + channel) = (unsigned char)value;
}

template <typename T>
void jpgImage<T>::setWidth(int width)
{
    this->_width = width;
}

template <typename T>
void jpgImage<T>::setHeight(int height)
{
    this->_height = height;
}

template <typename T>
void jpgImage<T>::setBitDepth(int depth)
{
    this->_bitdepth = depth;
}

template <typename T>
unsigned char* jpgImage<T>::getData()
{
    return image_buffer;
}

template <typename T>
void jpgImage<T>::writeToFile(std::string filename, int quality)
{
    struct jpeg_compress_struct coutinfo;
    /* This struct represents a JPEG error handler.  It is declared separately
     * because applications often want to supply a specialized error handler
     * (see the second half of this file for an example).  But here we just
     * take the easy way out and use the standard error handler, which will
     * print a message on stderr and call exit() if compression fails.
     * Note that this struct must live as long as the main JPEG parameter
     * struct, to avoid dangling-pointer problems.
     */
    struct jpeg_error_mgr err;          //the error handler
    coutinfo.err = jpeg_std_error( &err);

    FILE * outfile;		/* target file */
    JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
    int row_stride;		/* physical row width in image buffer */

    /* Step 1: allocate and initialize JPEG compression object */

    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&coutinfo);

    /* Step 2: specify data destination (eg, a file) */
    /* Note: steps 2 and 3 can be done in either order. */

    /* Here we use the library-supplied code to send compressed data to a
     * stdio stream.  You can also write your own code to do something else.
     * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
     * requires it in order to write binary files.
     */
    if ((outfile = fopen(filename.c_str(), "wb")) == NULL) {
        abort();
    }
    jpeg_stdio_dest(&coutinfo, outfile);

    /* Step 3: set parameters for compression */

    /* First we supply a description of the input image.
     * Four fields of the cinfo struct must be filled in:
     */
    coutinfo.image_width = this->getWidth(); 	/* image width and height, in pixels */
    coutinfo.image_height = this->getHeight();
    coutinfo.input_components = this->getBitDepth();		/* # of color components per pixel */
    coutinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
    /* Now use the library's routine to set default compression parameters.
     * (You must set at least cinfo.in_color_space before calling this,
     * since the defaults depend on the source color space.)
     */
    jpeg_set_defaults(&coutinfo);
    /* Now you can set any non-default parameters you wish to.
     * Here we just illustrate the use of quality (quantization table) scaling:
     */
    jpeg_set_quality(&coutinfo, quality, TRUE /* limit to baseline-JPEG values */);

    /* Step 4: Start compressor */

    /* TRUE ensures that we will write a complete interchange-JPEG file.
     * Pass TRUE unless you are very sure of what you're doing.
     */
    jpeg_start_compress(&coutinfo, TRUE);

    /* Step 5: while (scan lines remain to be written) */
    /*           jpeg_write_scanlines(...); */

    /* Here we use the library's state variable cinfo.next_scanline as the
     * loop counter, so that we don't have to keep track ourselves.
     * To keep things simple, we pass one scanline per call; you can pass
     * more if you wish, though.
     */
    row_stride = this->getWidth() * 3;	/* JSAMPLEs per row in image_buffer */

    while (coutinfo.next_scanline < coutinfo.image_height) {
        /* jpeg_write_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could pass
         * more than one scanline at a time if that's more convenient.
         */
        row_pointer[0] = & image_buffer[coutinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&coutinfo, row_pointer, 1);
    }

    /* Step 6: Finish compression */

    jpeg_finish_compress(&coutinfo);
    /* After finish_compress, we can close the output file. */
    fclose(outfile);

    /* Step 7: release JPEG compression object */

    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_compress(&coutinfo);
}

// Forward declaration of pngImage with ints.
template class jpgImage<int>;
template class jpgImage<float>;