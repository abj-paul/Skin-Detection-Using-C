#include "image.h"

Image* readPPM(const char* fileName){
  char buffer[16];
  
  // Opening Image File
  FILE* fp = fopen(fileName, "rb");
  if(!fp){
    fprintf(stderr, "Unable to open file '%s'\n",fileName);
    exit(1);
  }

  // Check image format
  if(!fgets(buffer, sizeof(buffer),fp)){
    perror(fileName);
    exit(1);
  }

  if(buffer[0] != 'P' || buffer[1] != '6'){
    fprintf(stderr, "Invalid image format (must be 'P6')\n");
  }

  // Check comments
  int c = fgetc(fp);
  while(c == '#'){
    while(getc(fp) != '\n');
    c = getc(fp);
  }
  ungetc(c, fp);

 // Load image
  Image* img = (Image*)malloc(sizeof(Image));
  if(!img){
    fprintf(stderr, "Unable to allocate memory for image %s\n",fileName);
    exit(1);
  }

  if(fscanf(fp, "%d %d", &img->width, &img->height) !=2){ //reading height, width
    fprintf(stderr,"Invalid image size(error loading %s)\n",fileName);
    exit(1);
  }

  int rgb_color_range;
  if(fscanf(fp, "%d", &rgb_color_range)!=1){
    fprintf(stderr, "Invalid rgb color range in image '%s'\n",fileName);
    exit(1);
  }

  if(rgb_color_range != RGB_COLOR_RANGE) {
    fprintf(stderr, "Invalid RGB Color Range! Image '%s' has range %d\n", fileName, rgb_color_range);
    exit(1);
  }

  while(fgetc(fp) != '\n');
  img->data = (Pixel*)malloc(img->height * img->width * sizeof(Pixel));
  if(!img->data){
    fprintf(stderr, "Unable to allocate memory for image %s\n",fileName);
    exit(1);
  }

  if(fread(img->data, 3*img->width, img->height, fp)!=img->height){
    fprintf(stderr,"Error loading image '%s'. Insufficient pixels.\n",fileName);
    exit(1);
  }
  fclose(fp);
  return img;
  
}
void writePPM(const char* fileName, Image* img){
  FILE* fp = fopen(fileName, "wb");
  if(!fp){
    fprintf(stderr, "Unable to open file '%s'\n", fileName);
    exit(1);
  }

  fprintf(fp, "P6\n");
  fprintf(fp, "# Created by %s\n",IMAGE_CREATOR);
  fprintf(fp, "%d %d\n",img->width,img->height);
  fprintf(fp, "%d\n",RGB_COLOR_RANGE);

  fwrite(img->data, 3 * img->width, img->height, fp);
  fclose(fp);
}
void transformImage(Image *img){ //For test purpose
  if(!img) {
    fprintf(stderr, "Error loading image!\n");
    exit(1);
  }

  for(int i=0; i<img->width*img->height; i++){
    img->data[i].red +=2;
    img->data[i].green +=2;
    img->data[i].blue +=2;
  }
}
