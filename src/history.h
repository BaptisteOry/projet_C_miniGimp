#ifndef HISTORY_H__
#define HISTORY_H__

/// \brief create the name for the history file
/// \param historyName: pointer on the name of the history file
/// \param nameImage: pointer on the image associated with the history file
void nameHistory(char *historyName, char *nameImage);

/// \brief create the history for the output image
/// \param modifications: string table of modifications
/// \param nbModifications: pointer on the number of modifications
/// \param filenameInput: pointer on the name of the history input file
/// \param filenameOutput: pointer on the name of the history output file
/// \return EXIT_FAILURE in case of problem, else EXIT_SUCCESS
int saveHistory(char (*modifications)[255], int *nbModifications, char *filenameInput, char *filenameOutput);

#endif
