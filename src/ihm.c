#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "change.h"
#include "ihm.h"

int effectAlreadyChoosed(char **effects, int nbEffects, char *effectChoosed){
    for (int i = 0; i<nbEffects; i++){
        if (!(strcmp(effects[i], effectChoosed))){
            return 1;
        }   
    }
    return 0;
}

int storeArguments(int nbArgs, char **tabArgs, char *imageToEdit, char *imageOutput, LutsToApply *lutsChoosed, ChangesToApply *changesChoosed, int *histogram, int *history){
	lutsChoosed->nbLuts=0;
    changesChoosed->nbChanges=0;

    for (int i = 0; i < nbArgs; i++){
		if (!(strcmp(imageToEdit, "images/default_input.ppm")) && (strstr(tabArgs[i], ".ppm") && !(strstr(tabArgs[i-1], "-o")))){
            strcpy(imageToEdit, tabArgs[i]);
        }
    	
    	if ((strstr(tabArgs[i], "-o") && strstr(tabArgs[i+1], ".ppm"))){
            strcpy(imageOutput, tabArgs[i+1]);
    	}
    	
    	if (!(strcmp(tabArgs[i], "-h"))){
    		*histogram=1;
    	}

        if (!(strcmp(tabArgs[i], "-histo"))){
            *history=1;
        }

    	if (((convertStringToLut(tabArgs[i])) != -1) && !(effectAlreadyChoosed(lutsChoosed->luts, lutsChoosed->nbLuts, tabArgs[i]))){
    		lutsChoosed->luts[lutsChoosed->nbLuts]=tabArgs[i];
    		if (tabArgs[i+1]){
                if (sscanf(tabArgs[i+1], "%d", &(lutsChoosed->params[lutsChoosed->nbLuts])) != 1) {
                    lutsChoosed->params[lutsChoosed->nbLuts]=0;
                }
            }else{
                lutsChoosed->params[lutsChoosed->nbLuts]=0;
            }
    		lutsChoosed->nbLuts++;
    	}

        if (((convertStringToChange(tabArgs[i])) != -1) && !(effectAlreadyChoosed(changesChoosed->changes, changesChoosed->nbChanges, tabArgs[i]))){
            changesChoosed->changes[changesChoosed->nbChanges]=tabArgs[i];
            if (tabArgs[i+1]){
                if (sscanf(tabArgs[i+1], "%d", &(changesChoosed->params[changesChoosed->nbChanges])) != 1) {
                    changesChoosed->params[changesChoosed->nbChanges]=0;
                }
            }else{
                changesChoosed->params[changesChoosed->nbChanges]=0;
            }
            changesChoosed->nbChanges++;
        }
    }

	if(!(strcmp(imageToEdit, "images/default_input.ppm"))){
		printf("%s\n", "Please enter the address of the ppm image to edit.");
    	printf("usage : %s mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]\n", tabArgs[0]);
		return EXIT_FAILURE;
	}
    
    return EXIT_SUCCESS;
}