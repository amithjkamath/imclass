## imclass

This is a simple image object framework to read and write image files.

## HOWTO

Run the following from the repository directory:

`mkdir build`

`cd build`

`cmake ..`

This should build two executables `jpgImage` and `pngImage` in the respective directories, and a static library `libimageprocessing.a` in the `/lib` directory.

To run either of these executables, you need to pass in a valid input image, and a new file name, to store the output.

For example,

`jpgImage ../images/image.jpg imageOut.jpg`

## TODO

Clean up the CMake structure, and add more image processing functions in the `imageprocessing` folder.
