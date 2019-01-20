#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "ihm.h"

int storeArguments(int nbArgs, char **tabArgs, char *imageToEdit, char *imageOutput, LutsToApply *lutsChoosed, int *histogram){
	lutsChoosed->nbLuts=0;
	for (int i = 0; i < nbArgs; i++){
		if (strstr(tabArgs[i], ".ppm") && !(strstr(tabArgs[i-1], "-o"))){
            strcpy(imageToEdit, tabArgs[i]);
        }
    	
    	if (strstr(tabArgs[i], "-o") && strstr(tabArgs[i+1], ".ppm")){
            strcpy(imageOutput, tabArgs[i+1]);
    	}
    	
    	if (!(strcmp(tabArgs[i], "-h")) || !(strcmp(tabArgs[i], "-histo"))){
    		*histogram=1;
    	}

    	if ((convertStringToLut(tabArgs[i])) != -1){
    		lutsChoosed->luts[lutsChoosed->nbLuts]=tabArgs[i];
    		lutsChoosed->params[lutsChoosed->nbLuts] = atoi(tabArgs[i+1]);
    		lutsChoosed->nbLuts++;
    	}
    }

	if(!(strcmp(imageToEdit, "images/default_input.ppm"))){
		printf("%s\n", "Please enter the address of the ppm image to edit.");
    	printf("usage : %s mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]\n", tabArgs[0]);
		return EXIT_FAILURE;
	}
    
    return EXIT_SUCCESS;
}