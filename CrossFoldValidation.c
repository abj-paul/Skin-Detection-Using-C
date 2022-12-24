#include "CrossFoldValidation.h"
char RESULT_FILENAME[64] = "10-CrossFoldValidation.txt";


void generateRandomDataset(char *array[], int n) {    
    struct timeval timeValue;
    gettimeofday(&timeValue, NULL);
    int usec = timeValue.tv_usec;
    srand48(usec);

    if (n > 1) {
        int i;
        for (i = n - 1; i > 0; i--) {
            int j = (unsigned int) (drand48()*(i+1));
            char* t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void crossFoldValidation(int crossFold){
  ConfusionMatrix* cnf[crossFold+1];
  
  for(int i=0; i<crossFold; i++){
    generateRandomDataset(totalFileNameArray, 555);

    char* trainData[500], *testData[55];
    for(int j=0; j<500; j++) trainData[j] = totalFileNameArray[j];
    for(int j=0; j<55; j++) testData[j] = totalFileNameArray[500+j];

    trainModel(trainData, 500);
    printf("%d-Cross Fold Validation, Run %d:--------------------------------------------------------------\n",crossFold,i);
    cnf[i] = calculateValidationMatrices(testData, 55);
  }

  printf("Average Results:\n");
  cnf[crossFold] = (ConfusionMatrix*)malloc(sizeof(ConfusionMatrix));
  initializeConfusionMatrix(cnf[crossFold]);
  for(int i=0; i<crossFold; i++){
    cnf[crossFold]->accuracy += cnf[i]->accuracy;
    cnf[crossFold]->truePositiveCount += cnf[i]->truePositiveCount;
    cnf[crossFold]->trueNegativeCount += cnf[i]->trueNegativeCount;
    cnf[crossFold]->falsePositiveCount += cnf[i]->falsePositiveCount;
    cnf[crossFold]->falseNegativeCount += cnf[i]->falseNegativeCount;
  }
  printf("Average Accuracy=%lf\n",cnf[crossFold]->accuracy/10.0);
  printf("Average True Positive=%lf\n",cnf[crossFold]->truePositiveCount/sumConfusionMatrix(cnf[crossFold]));
  printf("Average True Negative=%lf\n",cnf[crossFold]->trueNegativeCount/sumConfusionMatrix(cnf[crossFold]));
  printf("Average False Positive=%lf\n",cnf[crossFold]->falsePositiveCount/sumConfusionMatrix(cnf[crossFold]));
  printf("Average False Negative=%lf\n",cnf[crossFold]->falseNegativeCount/sumConfusionMatrix(cnf[crossFold]));

  for(int i=0; i<=crossFold; i++) free(cnf[i]);
}


ConfusionMatrix* calculateValidationMatrices(char* testData[], int n){
  char mask_image_location[] = "ibtd/Mask/";
  char original_image_location[] = "ibtd/";

  float truePositiveCount=0;
  float trueNegativeCount=0;
  float falsePositiveCount=0;
  float falseNegativeCount=0;
  float accuracy;

  for(int img_itr=0; img_itr<n; img_itr++){

    char image_location[256];
    image_location[0]='\0';
    strcat(image_location,mask_image_location);
    strcat(image_location,testData[img_itr]);
    strcat(image_location,".ppm");
    Image* mask_image = readPPM(image_location);
    
    image_location[0]='\0';
    strcat(image_location,original_image_location);
    strcat(image_location,testData[img_itr]);
    strcat(image_location,".ppm");
    Image* original_image = readPPM(image_location);

    int r,g,b;
    float predicted_value, actual_value;
    for(int i=0; i<original_image->width * original_image->height; i++){
      r = original_image->data[i].red;
      g = original_image->data[i].green;
      b = original_image->data[i].blue;

      if(abs(learn_array[r][g][b])<THRESHOLD) predicted_value = NONSKIN_PIXEL;
      else predicted_value = SKIN_PIXEL;

      if(mask_image->data[i].red > 250 && mask_image->data[i].green > 250 && mask_image->data[i].blue > 250) actual_value=NONSKIN_PIXEL;
      else actual_value = SKIN_PIXEL;

      if(actual_value==0 && predicted_value==0) falseNegativeCount++;
      else if(actual_value==0 && predicted_value==1) falsePositiveCount++;
      else if(actual_value==1 && predicted_value==0) trueNegativeCount++;
      else if(actual_value==1 && predicted_value==1) truePositiveCount++;

    }
    free(mask_image->data);
    free(mask_image);
    free(original_image->data);
    free(original_image);
  }
  accuracy = (truePositiveCount + falseNegativeCount) / (truePositiveCount + trueNegativeCount + falsePositiveCount + falseNegativeCount);
  
  ConfusionMatrix* t = (ConfusionMatrix*)malloc(sizeof(ConfusionMatrix));
  t->accuracy = accuracy;
  t->truePositiveCount = truePositiveCount;
  t->trueNegativeCount = trueNegativeCount;
  t->falsePositiveCount = falsePositiveCount;
  t->falseNegativeCount = falseNegativeCount;
  printConfusionMatrix(t);

  return t;
}

void printConfusionMatrix(ConfusionMatrix* x){
  printf("Accuracy=%lf\n",x->accuracy);
  printf("True Positive=%.2lf\n",x->truePositiveCount);
  printf("True Negative=%.2lf\n",x->trueNegativeCount);
  printf("False Positive=%.2lf\n",x->falsePositiveCount);
  printf("False Negative=%.2lf\n",x->falseNegativeCount);
}

void initializeConfusionMatrix(ConfusionMatrix* t){
  t->accuracy = 0;
  t->truePositiveCount = 0;
  t->trueNegativeCount = 0;
  t->falsePositiveCount = 0;
  t->falseNegativeCount = 0;
}

float sumConfusionMatrix(ConfusionMatrix* t){
  return t->truePositiveCount + t->trueNegativeCount + t->falsePositiveCount + t->falseNegativeCount;
}
