

#include <cstdlib>
#include <iostream>
#include "jpgImage.h"
#include "processImage.h"

int main(int argc, char *argv[])
{
    std::cout << "This file is called: " << __FILE__ << std::endl;
    std::cout << "It was compiled at: " << __TIME__ << ", on " << __DATE__ << std::endl;

    if(argc != 3)
        abort();

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    jpgImage<int> inputimage(inputFilename);

    std::cout << "Number of pixels in the image: " << inputimage.numberOfPixels() << std::endl;

    for(int x = 100; x < 105; x++)
    {
        for(int y = 100; y < 105; y++)
        {
            // pixel[0] is the R channel, 1 is G, and 2 is B.
            //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, pixel[0], pixel[1], pixel[2], pixel[3]);
            // Get pixel values from R, G and B channels.
            int Rvalue = inputimage.getPixelValueAt(x, y, 0);
            int Gvalue = inputimage.getPixelValueAt(x, y, 1);
            int Bvalue = inputimage.getPixelValueAt(x, y, 2);
            std::cout << "(" << x << ", " << y << ") = " << Rvalue << " " << Gvalue << " " << Bvalue << std::endl;
        }
    }

    //addScalarToImage(&inputimage, 50);

    //thresholdImageAt(&inputimage, 128);
    //convertRGBImageToGray(&inputimage);
    //convertRGBImageToSepia(&inputimage);

    inputimage.writeToFile(outputFilename);

    return 0;
}
