#ifndef LUT_H__
#define LUT_H__

#define MAX_SIZE_LUTS 5

/// \brief enumeration of possible luts
typedef enum {ADDLUM, DIMLUM, ADDCON, DIMCON, INVERT} lut;

/// \brief structure that contains luts to apply
typedef struct LutsToApply{
  char *luts[MAX_SIZE_LUTS];
  int params[MAX_SIZE_LUTS];
  int nbLuts;
}LutsToApply;

/// \brief application of selected luts on the lut table, then the image
/// \param image: pointer on the image
/// \param chosenLuts: pointer on the structure of the luts to be applied
/// \param modifications: string table of modifications
/// \param nbModifications: pointer on the number of modifications
void applyLuts(Image *image, LutsToApply *chosenLuts, char (*modifications)[255], int *nbModifications);

/// \brief conversion of the string to a lut (enumeration)
/// \param str: pointer on the string
/// \return the related value, or -1 if it does not find it
lut convertStringToLut(char *str);

/// \brief corrects the lut table so that the values do not exceed 0 or 255
/// \param lutTab: lut table
void updateLutTab(int *lutTab);

/// \brief change the lut table by adding luminosity
/// \param param: parameter to apply
/// \param lutTab: pointer on the lut table
void addlum(int param, int *lutTab);

/// \brief change the lut table by decreasing luminosity
/// \param param: parameter to apply
/// \param lutTab: pointer on the lut table
void dimlum(int param, int *lutTab);

/// \brief change the lut table by adding contrast
/// \param param: parameter to apply
/// \param lutTab: pointer on the lut table
void addcon(int param, int *lutTab);

/// \brief change the lut table by decreasing contrast
/// \param param: parameter to apply
/// \param lutTab: pointer on the lut table
void dimcon(int param, int *lutTab);

/// \brief change the lut table by reversing the values
/// \param lutTab: pointer on the lut table
void invert(int *lutTab);

#endif
