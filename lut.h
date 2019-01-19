#ifndef LUT_H__
#define LUT_H__

#include "image.h"

typedef enum {addlum, dimlum, addcon, dimcon, invert, sepia} lut;

typedef struct Lut {
    lut lut;
    int coeff;
    int tab[];
} Lut;

void DIMCON (Image* image, int n);
void INVERT(Image* image);
void SEPIA(Image* image, int coeff);

int INVERTLUT();

#endif
