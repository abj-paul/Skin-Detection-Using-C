#ifndef _MODEL_H_
#define _MODEL_H_

#include "image.h"
#include<string.h>
#include<math.h>

extern char* totalFileNameArray[555];
extern long double learn_array[256][256][256];
extern long double THRESHOLD;

void countPixels(char* fileNameArray[], int n);
void learnSingleImage(char* imageName);

void trainModel(char* fileNameArray[], int n);
void testModel(char* fileName);

// Miscellaneous
void debug3DTensor(int tensor[256][256][256]);
void debug3DTensorD(long double tensor[256][256][256]);
long double sumTensor(int tensor[256][256][256]);


#endif
