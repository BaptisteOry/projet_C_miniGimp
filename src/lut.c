#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "image.h"
#include "lut.h"

void applyLuts(Image *image, LutsToApply *lutsChosen, char (*modifications)[255], int *nbModifications){
    // initialise the lut table
    int lutTab[256];
    for (int i = 0; i <= 255; i++){
        lutTab[i]=i;
    }
    
    for (int i = 0; i<lutsChosen->nbLuts; i++){
        int behaviorLut=0;

        // apply the effect on the lut table for the desired lut
        switch (convertStringToLut(lutsChosen->luts[i])){
            case ADDLUM:
            addlum(lutsChosen->params[i], lutTab);
            break;
            case DIMLUM:
            dimlum(lutsChosen->params[i], lutTab);
            break;
            case ADDCON:
            addcon(lutsChosen->params[i], lutTab);
            break;
            case DIMCON:
            dimcon(lutsChosen->params[i], lutTab);
            break;
            case INVERT:
            behaviorLut = 1;
            invert(lutTab);
            break;
            default: ;
            break;
        }

        // display and store the lut change
        char modificationText[255];
        if(behaviorLut==0){
            sprintf(modificationText, "Add %s, parameter %d\n", lutsChosen->luts[i], lutsChosen->params[i]);
        }else{
            sprintf(modificationText, "Add %s\n", lutsChosen->luts[i]);
        }  
        printf("%s", modificationText);
        strcpy(modifications[*nbModifications], modificationText);
        (*nbModifications)++;
    }

    // apply the lut table on the image (with corrections)
    updateLutTab(lutTab);
    for(int i = 0; i < (image->width)*(image->height)*3; i++) {
        image->data[i]=lutTab[image->data[i]];
    }
}

lut convertStringToLut(char *str){
    if(!(strcmp(str, "ADDLUM"))) return ADDLUM;
    else if(!(strcmp(str, "DIMLUM"))) return DIMLUM;
    else if(!(strcmp(str, "ADDCON"))) return ADDCON;
    else if(!(strcmp(str, "DIMCON"))) return DIMCON;
    else if(!(strcmp(str, "INVERT"))) return INVERT;
    else return -1;
}

void updateLutTab(int *lutTab){
    for (int i = 0; i <= 255; i++){
        if(lutTab[i]<0){
            lutTab[i]=0;
        }else if(lutTab[i]>255) {
            lutTab[i]=255;
        }
    }
}

void addlum(int param, int *lutTab) {
    for (int i = 0; i <= 255; i++){
        lutTab[i]=lutTab[i]+param;
    }
}

void dimlum(int param, int *lutTab) {
    for (int i = 0; i <= 255; i++){
        lutTab[i]=lutTab[i]-param;
    }
}

void addcon(int param, int *lutTab) {
    for (int i = 0; i <= 255; i++){
        if (param>128){
            param=128;
        }
        lutTab[i]=(lutTab[i]-param)*(255/(255-2*(float)param));
    }
}

void dimcon(int param, int *lutTab) {
    for (int i = 0; i <= 255; i++){
        if (param>128){
            param=128;
        }
        lutTab[i]=lutTab[i]*((255-2*(float)param)/255)+param;
    }
}

void invert(int *lutTab) {
    for(int i = 0; i <= 255; i++) {
        lutTab[i]=255-i;
    }
}