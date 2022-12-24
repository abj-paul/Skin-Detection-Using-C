#ifndef _CROSS_FOLD_VALIDATION_H_
#define _CROSS_FOLD_VALIDATION_H_

#include "model.h"
#include<sys/time.h>
#include<stddef.h>
#include<stdlib.h>

#define NONSKIN_PIXEL 0
#define SKIN_PIXEL 1

typedef struct{
  float truePositiveCount;
  float trueNegativeCount;
  float falsePositiveCount;
  float falseNegativeCount;
  float accuracy;
}ConfusionMatrix;

void generateRandomDataset(char *array[], int n);
void crossFoldValidation(int crossFold);
ConfusionMatrix* calculateValidationMatrices(char* testData[], int n);
//void storeResultInFile();
// Miscellaneous
void printConfusionMatrix(ConfusionMatrix* x);
void initializeConfusionMatrix(ConfusionMatrix* t);
float sumConfusionMatrix(ConfusionMatrix* t);

#endif
