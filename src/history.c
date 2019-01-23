#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "history.h"

void nameHistory(char *historyName, char *nameImage){
    strncpy(historyName, nameImage, strlen(nameImage)-4);
    historyName[strlen(nameImage)-4] = '\0';
    strcat(historyName, "_history.txt");
}

int saveHistory(char (*modifications)[255], int *nbModifications, char *filenameInput, char *filenameOutput){

    char chaine[255];

    if(!(strcmp(filenameInput, filenameOutput))){
        // open the file that must exist for writing (wt)
        FILE *myfileOutput;
        if ((myfileOutput = fopen(filenameOutput,"a")) == NULL){
            printf("saveHistory : error opening file %s.\n",filenameOutput);
            return EXIT_FAILURE;
        }

        // save the data
        for (int i = 0; i < *nbModifications; i++){
            fputs(modifications[i], myfileOutput);
        }

        // close the file
        fclose(myfileOutput);
    }else{
        // open the file that must exist for writing (wt)
        FILE *myfileOutput;
        if ((myfileOutput = fopen(filenameOutput,"wt")) == NULL){
            printf("saveHistory : error opening file %s.\n",filenameOutput);
            return EXIT_FAILURE;
        }

        // open the file that must exist for reading (r)
        FILE *myfileInput;
        if ((myfileInput = fopen(filenameInput, "rt")) == NULL) {
            if (errno != ENOENT) {
                printf("saveHistory : error opening file %s.\n",filenameInput);
                return EXIT_FAILURE;
            }
        } else {
            while(fgets(chaine,255,myfileInput)){
                fputs(chaine, myfileOutput);
            }
            fclose(myfileInput);
        }

        // save the data
        for (int i = 0; i < *nbModifications; i++){
            fputs(modifications[i], myfileOutput);
        }

        // close the file
        fclose(myfileOutput);
        }

    return EXIT_SUCCESS;
}