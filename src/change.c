#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "mathf.h"
#include "image.h"
#include "change.h"

change convertStringToChange(char *str){
    if(!(strcmp(str, "SEPIA"))) return SEPIA;
    else if(!(strcmp(str, "BLACKANDWHITE"))) return BLACKANDWHITE;
    else if(!(strcmp(str, "BLUR"))) return BLUR;
    else if(!(strcmp(str, "EDGE"))) return EDGE;
    else return -1;
}

void applyChanges(Image *image, ChangesToApply *changesChoosed, char (*modifications)[255], int *nbModifications){
    for (int i = 0; i<changesChoosed->nbChanges; i++){
        int behaviorChange=0;
        switch (convertStringToChange(changesChoosed->changes[i])){
            case SEPIA:
            sepia(changesChoosed->params[i], image);
            break;
            case BLACKANDWHITE:
            behaviorChange = 1;
            blackAndWhite(image);
            break;
            case BLUR:
            behaviorChange = 1;
            int blurMatrix[3][3]={{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
            convolutionMatrix(blurMatrix, image);
            break;
            case EDGE:
            behaviorChange = 1;
            int edgeMatrix[3][3]={{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
            convolutionMatrix(edgeMatrix, image);
            break;
            default: ;
            break;
        }
        char modificationText[255];
        if(behaviorChange==0){
            sprintf(modificationText, "Ajout de %s paramètre %d\n", changesChoosed->changes[i], changesChoosed->params[i]);
        }else{
            sprintf(modificationText, "Ajout de %s\n", changesChoosed->changes[i]);
        }  
        printf("%s", modificationText);
        strcpy(modifications[*nbModifications], modificationText);
        (*nbModifications)++;

        //int contraste[3][3]={{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    }
}

void blackAndWhite(Image *image) {
    for (int i = 0; i < (image->width)*(image->height)*3-2; i=i+3) {
        int value = (image->data[i]+image->data[i+1]+image->data[i+2])/3;
        image->data[i] = value;
        image->data[i+1] = value;
        image->data[i+2] = value;
    }
}

void sepia(int param, Image *image) {
    for (int i = 0; i < (image->width)*(image->height)*3-2; i=i+3) {
        int r = image->data[i];
        int g = image->data[i+1];
        int b = image->data[i+2];
        image->data[i] = max(min((r*0.393)+(g*0.769)+(b*0.189)+param, 255), 0);
        image->data[i+1] = max(min((r*0.349)+(g*0.686)+(b*0.168)+param, 255),0);
        image->data[i+2] = max(min((r*0.272)+(g*0.534)+(b*0.131), 255), 0);
    }
}

void convolutionMatrix(int (*matrix)[3], Image *image) {
    Image imageWithEffect;
    newImage(&imageWithEffect, image->width, image->height);
    for(int i=image->width*3+1; i<image->width*image->height*3-image->width*3; i++) {
        int value=1;
        for(int j=0; j<2; j++) {
            value=value*matrix[0][j]*image->data[i-image->width*3-1+j];
        }
        for(int j=0; j<2; j++) {
            value=value*matrix[1][j]*image->data[i-1+j];
        }
        for(int j=0; j<2; j++) {
            value=value*matrix[2][j]*image->data[i+image->width*3-1+j];
        }
        imageWithEffect.data[i]=value;
    }
    
    for (int i = 0; i < (image->width)*(image->height)*3-2; i=i+3) {
        image->data[i] = imageWithEffect.data[i];
    }
}