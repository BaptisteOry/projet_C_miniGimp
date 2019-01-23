#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "mathf.h"
#include "image.h"
#include "lut.h"

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

void sepia(int param, Image* image) {
    for (int i = 0; i < (image->width)*(image->height)*3-2; i=i+3) {
        int r = image->data[i];
        int g = image->data[i+1];
        int b = image->data[i+2];
        image->data[i] = max(min((r*0.393)+(g*0.769)+(b*0.189)+param, 255), 0);
        image->data[i+1] = max(min((r*0.349)+(g*0.686)+(b*0.168)+param, 255),0);
        image->data[i+2] = max(min((r*0.272)+(g*0.534)+(b*0.131), 255), 0);
    }
}

lut convertStringToLut(char *str){
    if(!(strcmp(str, "ADDLUM"))) return ADDLUM;
    else if(!(strcmp(str, "DIMLUM"))) return DIMLUM;
    else if(!(strcmp(str, "ADDCON"))) return ADDCON;
    else if(!(strcmp(str, "DIMCON"))) return DIMCON;
    else if(!(strcmp(str, "INVERT"))) return INVERT;
    else if(!(strcmp(str, "SEPIA"))) return SEPIA;
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

void applyLut(Image *image, LutsToApply *lutsChoosed, char (*modifications)[255], int *nbModifications){
    // initialise tab lut
    int lutTab[256];
    for (int i = 0; i <= 255; i++){
        lutTab[i]=i;
    }
    
    for (int i = 0; i<lutsChoosed->nbLuts; i++){
        int behaviorLut=0;
        switch (convertStringToLut(lutsChoosed->luts[i])){
            case ADDLUM:
            addlum(lutsChoosed->params[i], lutTab);
            break;
            case DIMLUM:
            dimlum(lutsChoosed->params[i], lutTab);
            break;
            case ADDCON:
            addcon(lutsChoosed->params[i], lutTab);
            break;
            case DIMCON:
            dimcon(lutsChoosed->params[i], lutTab);
            break;
            case INVERT:
            behaviorLut = 1;
            invert(lutTab);
            break;
            case SEPIA:
            sepia(lutsChoosed->params[i], image);
            break;
            default: ;
            break;
        }
        char modificationText[255];
        if(behaviorLut==0){
            sprintf(modificationText, "Ajout de %s paramètre %d\n", lutsChoosed->luts[i], lutsChoosed->params[i]);
        }else{
            sprintf(modificationText, "Ajout de %s\n", lutsChoosed->luts[i]);
        }  
        printf("%s", modificationText);
        strcpy(modifications[*nbModifications], modificationText);
        (*nbModifications)++;
    }

    // apply tab lut
    updateLutTab(lutTab);
    for(int i = 0; i < (image->width)*(image->height)*3; i++) {
        image->data[i]=lutTab[image->data[i]];
    }
}