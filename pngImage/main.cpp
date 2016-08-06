#include <cstdlib>
#include <iostream>
#include "pngImage.h"
#include "processImage.h"

int main(int argc, char *argv[])
{
    std::cout << "This file is called: " << __FILE__ << std::endl;
    std::cout << "It was compiled at: " << __TIME__ << ", on " << __DATE__ << std::endl;
    
    if(argc != 3)
        abort();

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    pngImage<float> image(inputFilename);
    std::cout << "Number of pixels in the image: " << image.numberOfPixels() << std::endl;

    // //Other functions to try
    //addScalarToImage(&image, 50);
    //thresholdImageAt(&image, 128);
    //convertRGBImageToSepia(&image);
    convertRGBImageToGray(&image);

    image.writeToFile(outputFilename);
    return 0;
}
