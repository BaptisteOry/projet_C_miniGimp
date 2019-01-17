#ifndef LUT_H__
#define LUT_H__

typedef enum {ADDLUM, DIMLUM, ADDCON, DIMCON, INVERTLUT, SEPIA} lut;

void addlum(int param, int *lutAddlum);
void dimlum(int param, int *lutAddlum);
void addcon(int param, int *lutTab);
void invertlut(int *lutTab);
void applyLut(Image *image, lut *luts, int *params);

/*
void dimcon(Image* image, int n);
void sepia(Image* image, int coeff);
*/

#endif
