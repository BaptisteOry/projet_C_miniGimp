#ifndef LUT_H__
#define LUT_H__

#include "image.h"

typedef enum {ADDLUM, DIMLUM, ADDCON, DIMCON, INVERTLUT, SEPIA} lut;

void DIMCON (Image* image, int n);
void INVERT(Image* image);
void SEPIA(Image* image, int coeff);

int[] INVERTLUT();

#endif
