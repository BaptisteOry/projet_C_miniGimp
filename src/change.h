#ifndef CHANGE_H__
#define CHANGE_H__

#define MAX_SIZE_CHANGES 8

/// \brief enumeration of possible changes
typedef enum {SEPIA, BLACKANDWHITE, BLUR, REINEDGES, DETECTEDGES, BUMP, HIGHPASS, LOWPASS} change;

/// \brief structure that contains changes to apply
typedef struct ChangesToApply{
  char *changes[MAX_SIZE_CHANGES];
  int params[MAX_SIZE_CHANGES];
  int nbChanges;
}ChangesToApply;

/// \brief application of selected changes on the image
/// \param image: pointer on the image
/// \param changesChosen: pointer on the structure of the changes to be applied
/// \param modifications: string table of modifications
/// \param nbModifications: pointer on the number of modifications
void applyChanges(Image *image, ChangesToApply *changesChosen, char (*modifications)[255], int *nbModifications);

/// \brief conversion of the string to a change (enumeration)
/// \param str: pointer on the string
/// \return the related value, or -1 if it does not find it
change convertStringToChange(char *str);

/// \brief change the image to "black and white"
/// \param image: pointer on the image
void blackAndWhite(Image *image);

/// \brief change the image to "sepia"
/// \param param: parameter to apply
/// \param image: pointer on the image
void sepia(int param, Image *image);

/// \brief change the image according to a convolution matrix
/// \param matrix: 2-dimensional table matrix to apply
/// \param image: pointer on the image
void convolutionMatrix(int (*matrix)[3], Image *image);

#endif
