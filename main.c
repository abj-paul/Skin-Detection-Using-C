#include<stdio.h>
#include<string.h>
#include<time.h>
#include "image.h"
#include "model.h"
#include "CrossFoldValidation.h"

//mogrify -format ppm ibtd/*.jpg
//mogrify -format ppm ibtd/Mask/*.bmp

int main(){
  clock_t begin = clock();

  trainModel(totalFileNameArray,555);
  testModel("test-image.ppm");

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total train & test time=%lf seconds.\n",time_spent);
  //debug3DTensorD(learn_array);

  crossFoldValidation(10);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%d Crossfold Validation time=%lf seconds.\n",5,time_spent);

  return 0;
}

