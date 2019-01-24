#ifndef IHM_H__
#define IHM_H__

int effectAlreadyChoosed(char **effects, int nbEffects, char *effectChoosed);
int storeArguments(int nbArgs, char **tabArgs, char *imageToEdit, char *imageOutput, LutsToApply *lutsChoosed, ChangesToApply *changesChoosed, int *histogram, int *history);

#endif
