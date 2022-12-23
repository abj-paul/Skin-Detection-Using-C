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
  for(int i=0; i<crossFold; i++){
    generateRandomDataset(totalFileNameArray, 555);

    char* trainData[500], *testData[55];
    for(int j=0; j<500; j++) trainData[j] = totalFileNameArray[j];
    for(int j=0; j<55; j++) testData[j] = totalFileNameArray[500+j];

    trainModel(trainData, 500);
    printf("%d-Cross Fold Validation, Run %d:--------------------------------------------------------------\n",crossFold,i);
    calculateValidationMatrices(testData, 55);
  }
}


void calculateValidationMatrices(char* testData[], int n){
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
  }
  accuracy = (truePositiveCount + falseNegativeCount) / (truePositiveCount + trueNegativeCount + falsePositiveCount + falseNegativeCount);
  printf("Accuracy=%lf\n",accuracy);
  printf("True Positive=%.2lf\n",truePositiveCount);
  printf("True Negative=%.2lf\n",trueNegativeCount);
  printf("False Positive=%.2lf\n",falsePositiveCount);
  printf("False Negative=%.2lf\n",falseNegativeCount);

}
