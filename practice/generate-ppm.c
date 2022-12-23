#include <stdio.h>
void main() {
  FILE * out;
  out = fopen("color_test.ppm", "wb");
  fprintf(out, "P6\n 256 256\n 255\n");
  for(int r=0; r<256; r++) {
    for(int b=0; b<256; b++) {
      fputc(r, out);
      fputc(0, out);
      fputc(b, out);
    }
  }
  fclose(out);
}
