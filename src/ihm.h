#ifndef IHM_H__
#define IHM_H__

/// \brief test if an effect (lut or change) has already been chosen
/// \param effects: string table of chosen effects (luts or changes)
/// \param nbEffects: number of selected effects
/// \param effectChosen: string of the effect to be tested
/// \return 1 if the test effect has already been chosen, else return 0
int effectAlreadyChosen(char **effects, int nbEffects, char *effectChosen);

/// \brief store the options / arguments chosen by the user
/// \param nbArgs: number of arguments in the command line
/// \param tabArgs: string table of arguments in the command line
/// \param imageToEdit: name of the image to edit
/// \param imageOutput: name of the output image
/// \param lutsChosen: pointer on the structure of the luts to be applied
/// \param changesChosen: pointer on the structure of the changes to be applied
/// \param histogram: presence of histograms
/// \param history: presence of the history
/// \return EXIT_FAILURE in case of problem, else EXIT_SUCCESS
int storeArguments(int nbArgs, char **tabArgs, char *imageToEdit, char *imageOutput, LutsToApply *lutsChosen, ChangesToApply *changesChosen, int *histogram, int *history);

#endif
