#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "change.h"
#include "ihm.h"

int effectAlreadyChosen(char **effects, int nbEffects, char *effectChosen){
    for (int i = 0; i<nbEffects; i++){
        if (!(strcmp(effects[i], effectChosen))){
            return 1;
        }   
    }
    return 0;
}

int storeArguments(int nbArgs, char **tabArgs, char *imageToEdit, char *imageOutput, LutsToApply *lutsChosen, ChangesToApply *changesChosen, int *histogram, int *history){
	lutsChosen->nbLuts=0;
    changesChosen->nbChanges=0;

    for (int i = 0; i < nbArgs; i++){
		// storage of the image to edit
        if (!(strcmp(imageToEdit, "images/default_input.ppm")) && (strstr(tabArgs[i], ".ppm") && !(strstr(tabArgs[i-1], "-o")))){
            strcpy(imageToEdit, tabArgs[i]);
        }
    	
        // storage of the output image
    	if ((strstr(tabArgs[i], "-o") && strstr(tabArgs[i+1], ".ppm"))){
            strcpy(imageOutput, tabArgs[i+1]);
    	}
    	
        // storage of the histogram option
    	if (!(strcmp(tabArgs[i], "-h"))){
    		*histogram=1;
    	}

        // storage of the history option
        if (!(strcmp(tabArgs[i], "-histo"))){
            *history=1;
        }

        // storage of selected luts (effects) and their parameters
    	if (((convertStringToLut(tabArgs[i])) != -1) && !(effectAlreadyChosen(lutsChosen->luts, lutsChosen->nbLuts, tabArgs[i]))){
    		lutsChosen->luts[lutsChosen->nbLuts]=tabArgs[i];
    		if (tabArgs[i+1]){
                if (sscanf(tabArgs[i+1], "%d", &(lutsChosen->params[lutsChosen->nbLuts])) != 1) {
                    lutsChosen->params[lutsChosen->nbLuts]=0;
                }
            }else{
                lutsChosen->params[lutsChosen->nbLuts]=0;
            }
    		lutsChosen->nbLuts++;
    	}

        // storage of selected changes (effects) and their parameters
        if (((convertStringToChange(tabArgs[i])) != -1) && !(effectAlreadyChosen(changesChosen->changes, changesChosen->nbChanges, tabArgs[i]))){
            changesChosen->changes[changesChosen->nbChanges]=tabArgs[i];
            if (tabArgs[i+1]){
                if (sscanf(tabArgs[i+1], "%d", &(changesChosen->params[changesChosen->nbChanges])) != 1) {
                    changesChosen->params[changesChosen->nbChanges]=0;
                }
            }else{
                changesChosen->params[changesChosen->nbChanges]=0;
            }
            changesChosen->nbChanges++;
        }
    }

    // display the use of the program if the user has not chosen an image to edit
	if(!(strcmp(imageToEdit, "images/default_input.ppm"))){
		printf("%s\n", "Please enter the address of the ppm image to edit.");
    	printf("usage : %s mon_image.ppm [-h] [-histo] [<code_effect>[_<param1>]*]* [-o image_sortie.ppm]\n", tabArgs[0]);
		return EXIT_FAILURE;
	}
    
    return EXIT_SUCCESS;
}