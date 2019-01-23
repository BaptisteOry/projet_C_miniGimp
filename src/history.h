#ifndef HISTORY_H__
#define HISTORY_H__

void nameHistory(char *historyName, char *nameImage);
int saveHistory(char (*modifications)[255], int *nbModifications, char *filenameInput, char *filenameOutput);

#endif
