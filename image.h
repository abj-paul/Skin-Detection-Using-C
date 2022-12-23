
#ifndef __IMAGE_H_
#define __IMAGE_H_

// This code can only read-write .PPM images. So first, convert all .jpg, .bmp etc images into ppm format.

#include<stdio.h>
#include<stdlib.h>

typedef struct {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
}Pixel;

typedef struct {
  int width;
  int height;
  Pixel* data;
} Image;

#define RGB_COLOR_RANGE 255
#define IMAGE_CREATOR "Abhijit Paul"

Image* readPPM(const char* fileName);
void writePPM(const char* fileName, Image* img);
void transformImage(Image *img); //For test purpose

#endif
