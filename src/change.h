#ifndef CHANGE_H__
#define CHANGE_H__

#define MAX_SIZE_CHANGES 4

typedef enum {SEPIA, BLACKANDWHITE, BLUR, EDGE} change;

typedef struct ChangesToApply{
  char *changes[MAX_SIZE_CHANGES];
  int params[MAX_SIZE_CHANGES];
  int nbChanges;
}ChangesToApply;

change convertStringToChange(char *str);
void applyChanges(Image *image, ChangesToApply *changesChoosed, char (*modifications)[255], int *nbModifications);
void blackAndWhite(Image *image);
void sepia(int param, Image *image);
void convolutionMatrix(int (*matrix)[3], Image *image);

#endif
