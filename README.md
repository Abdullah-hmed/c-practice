
**Table of Contents**
-----------------

1. [Overview](#overview)
2. [Features](#features)
3. [Usage](#usage)
4. [Arguments](#arguments)
5. [Dependencies](#dependencies)
6. [Notes](#notes)
7. [License](#license)

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
gcc -o termview src/main.c -lm
```
This will create an executable file called `image_to_ascii`.

### Running the Program

To run the program, use the following command:
```bash
./termview -d input_image.jpg -w 80
```
Replace `input_image.jpg` with the path to the image file you want to convert, and `80` with the desired output width.

**Arguments**

* `-h`: Display help message
* `-v`: Display version information
* `-d`: Path to the input image file
* `-w`: Output width
* `-c`: Colored output
* `-r`: High resolution output

#### Examples:
```bash
./termview -d input_image.jpg -w 80
./termview -d input_image.jpg -w 80 -c
./termview -d input_image.jpg -w 80 -r
```

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