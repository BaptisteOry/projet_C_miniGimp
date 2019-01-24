#ifndef LUT_H__
#define LUT_H__

#define MAX_SIZE_LUTS 5

typedef enum {ADDLUM, DIMLUM, ADDCON, DIMCON, INVERT} lut;

typedef struct LutsToApply{
  char *luts[MAX_SIZE_LUTS];
  int params[MAX_SIZE_LUTS];
  int nbLuts;
}LutsToApply;

void applyLuts(Image *image, LutsToApply *lutsChoosed, char (*modifications)[255], int *nbModifications);
lut convertStringToLut(char *str);
void updateLutTab(int *lutTab);
void addlum(int param, int *lutAddlum);
void dimlum(int param, int *lutAddlum);
void addcon(int param, int *lutTab);
void dimcon(int param, int *lutTab);
void invert(int *lutTab);

#endif
