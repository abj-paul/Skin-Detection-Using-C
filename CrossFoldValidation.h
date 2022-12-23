#ifndef _CROSS_FOLD_VALIDATION_H_
#define _CROSS_FOLD_VALIDATION_H_

#include "model.h"
#include<sys/time.h>
#include<stddef.h>
#include<stdlib.h>

#define NONSKIN_PIXEL 0
#define SKIN_PIXEL 1

void generateRandomDataset(char *array[], int n);
void crossFoldValidation(int crossFold);
void calculateValidationMatrices(char* testData[], int n);
//void storeResultInFile();

#endif
