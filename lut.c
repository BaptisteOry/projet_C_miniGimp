#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "ihm.h"

void addlum(int param, int *lutTab) {
    for (int i = 0; i <= 255; i++){
        if(lutTab[i]+param<255){
            lutTab[i]=lutTab[i]+param;
        }else{
            lutTab[i]=255;
        }
    }
}

void dimlum(int param, int *lutTab) {
    for (int i = 0; i <= 255; i++){
        if(lutTab[i]-param>0){
            lutTab[i]=lutTab[i]-param;
        }else{
            lutTab[i]=0;
        }
    }
}

void addcon(int param, int *lutTab) {
    for (int i = 0; i <= 255; i++){
        if(lutTab[i]>=128){
            if(lutTab[i]+param<255){
                lutTab[i]=lutTab[i]+param;
            }else{
                lutTab[i]=255;
            }
        }else{
            if(lutTab[i]-param>0){
                lutTab[i]=lutTab[i]-param;
            }else{
                lutTab[i]=0;
            }
        }
    }
}

void dimcon(int param, int *lutTab) {
    for (int i = 0; i <= 255; i++){
        if(lutTab[i]>=128){
            if(lutTab[i]-param>=128){
                lutTab[i]=lutTab[i]-param;
            }else{
                lutTab[i]=128;
            }
        }else{
            if(lutTab[i]+param<128){
                lutTab[i]=lutTab[i]+param;
            }else{
                lutTab[i]=128;
            }
        }
    }
}

void invert(int *lutTab) {
    for(int i = 0; i <= 255; i++) {
        lutTab[i]=255-i;
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

void applyLut(Image *image, LutsToApply *lutsChoosed){
    // initialise tab lut
    int lutTab[256];
    for (int i = 0; i <= 255; i++){
        lutTab[i]=i;
    }
    
    for (int i = 0; i<lutsChoosed->nbLuts; i++){
        switch (convertStringToLut(lutsChoosed->luts[i])){
            case ADDLUM:
            printf("Ajout de %s paramètre %d\n", lutsChoosed->luts[i], lutsChoosed->params[i]);
            addlum(lutsChoosed->params[i], lutTab);
            break;
            case DIMLUM:
            printf("Ajout de %s paramètre %d\n", lutsChoosed->luts[i], lutsChoosed->params[i]);
            dimlum(lutsChoosed->params[i], lutTab);
            break;
            case ADDCON:
            printf("Ajout de %s paramètre %d\n", lutsChoosed->luts[i], lutsChoosed->params[i]);
            addcon(lutsChoosed->params[i], lutTab);
            break;
            case DIMCON:
            printf("Ajout de %s paramètre %d\n", lutsChoosed->luts[i], lutsChoosed->params[i]);
            dimcon(lutsChoosed->params[i], lutTab);
            break;
            case INVERT:
            printf("Ajout de %s\n", lutsChoosed->luts[i]);
            invert(lutTab);
            break;
            default: 
            printf("Cette LUT n'a pas été programmée.\n");
            break;
        }
    }

    // apply tab lut
    for(int i = 0; i < (image->width)*(image->height)*3; i++) {
        image->data[i]=lutTab[image->data[i]];
    }
}

/*
void dimcon(Image* image, int n) {
    float coeff = 1.0/n;
    for (int i = 0; i < (image->width)*(image->height)*3-2; i=i+3){
        float a = (image->data[i]+image->data[i+1]+image->data[i+2])/3;
        float b = 255*exp(coeff*log(a/255));
		image->data[i]=max(0, min(255, image->data[i]+b-a));
		image->data[i+1]=max(0, min(255, image->data[i+1]+b-a));
		image->data[i+2]=max(0, min(255, image->data[i+2]+b-a));
    }
}

void sepia(Image* image, int coeff) {
    for (int i = 0; i < (image->width)*(image->height)*3-2; i=i+3) {
        int r = image->data[i];
        int g = image->data[i+1];
        int b = image->data[i+2];
        image->data[i] = max(min((r*0.393)+(g*0.769)+(b*0.189)+coeff, 255), 0);
        image->data[i+1] = max(min((r*0.349)+(g*0.686)+(b*0.168)+coeff, 255),0);
        image->data[i+2] = max(min((r*0.272)+(g*0.534)+(b*0.131), 255), 0);
    }
}
*/