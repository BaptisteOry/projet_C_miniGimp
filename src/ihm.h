#ifndef IHM_H__
#define IHM_H__

int lutAlreadyChoosed(LutsToApply *lutsChoosed, char *lutChoosed);
int storeArguments(int nbArgs, char **tabArgs, char *imageToEdit, char *imageOutput, LutsToApply *lutsChoosed, int *histogram, int *history);

#endif
