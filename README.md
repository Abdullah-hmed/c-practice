

**Image to ASCII Art Converter**
=====================================

**Table of Contents**
-----------------

1. [Overview](#overview)
2. [Features](#features)
3. [Usage](#usage)
4. [Dependencies](#dependencies)
5. [Notes](#notes)
6. [License](#license)

**Overview**
------------

This is a C program that converts an image into ASCII and unicode art using ANSI escape sequences. It uses the stb_image library to load the image and then maps each pixel to a corresponding ASCII character.

**Features**
------------

* Converts images into ASCII art
* Supports grayscale and RGB images
* Adjustable output width
* Error handling for invalid image files and memory allocation

**Usage**
-----

### Compiling the Program

To compile the program, run the following command:
```bash
cd src
gcc -o termview main.c -lm
```
This will create an executable file called `image_to_ascii`.

### Running the Program

To run the program, use the following command:
```bash
./termview -d input_image.jpg -w 80
```
Replace `input_image.jpg` with the path to the image file you want to convert, and `80` with the desired output width.

**Dependencies**
------------

* stb_image library (included in the repository)

**Notes**
-----

* The program assumes that the input image is in a format that can be loaded by the stb_image library (e.g. JPEG, PNG, BMP).
* The output ASCII art is printed to the console, but it can be redirected to a file using standard output redirection (e.g. `./termview -d input_image.jpg -w 80 > output.txt`).

**License**
-------

This program is released under the MIT License.

**Contributing**
------------

Contributions are welcome! If you have any ideas for improving the program or fixing bugs, please submit a pull request.


**Acknowledgments**
---------------

* stb_image library by Sean Barrett