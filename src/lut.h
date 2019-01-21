#ifndef LUT_H__
#define LUT_H__

#define MAX_SIZE 6

typedef enum {ADDLUM, DIMLUM, ADDCON, DIMCON, INVERT, SEPIA} lut;

typedef struct LutsToApply{
  char *luts[MAX_SIZE];
  int params[MAX_SIZE];
  int nbLuts;
}LutsToApply;

void addlum(int param, int *lutAddlum);
void dimlum(int param, int *lutAddlum);
void addcon(int param, int *lutTab);
void dimcon(int param, int *lutTab);
void invert(int *lutTab);
void sepia(int param, Image* image);
lut convertStringToLut(char *str);
void updateLutTab(int *lutTab);
void applyLut(Image *image, LutsToApply *lutsChoosed);

/*
void addconSimple(int param, int *lutTab);
void dimconSimple(int param, int *lutTab);
*/

#endif
