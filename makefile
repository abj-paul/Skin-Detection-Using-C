all: main.c image.c model.c image.h model.h CrossFoldValidation.c CrossFoldValidation.h
	gcc -g main.c image.c model.c CrossFoldValidation.c
clean:
	rm a.out *~ masked_test-image.ppm
