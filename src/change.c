#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "mathf.h"
#include "image.h"
#include "change.h"

void applyChanges(Image *image, ChangesToApply *changesChosen, char (*modifications)[255], int *nbModifications){
    for (int i = 0; i<changesChosen->nbChanges; i++){
        int behaviorChange=0;
        
        // apply the effect on the image for the desired change
        switch (convertStringToChange(changesChosen->changes[i])){
            case SEPIA:
            sepia(changesChosen->params[i], image);
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
            case REINEDGES:
            behaviorChange = 1;
            int reinEdgesMatrix[3][3]={{0, 0, 0}, {-1, 1, 0}, {0, 0, 0}};
            convolutionMatrix(reinEdgesMatrix, image);
            break;
            case DETECTEDGES:
            behaviorChange = 1;
            int detectEdgesMatrix[3][3]={{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
            convolutionMatrix(detectEdgesMatrix, image);
            break;
            case BUMP:
            behaviorChange = 1;
            int bumpMatrix[3][3]={{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};
            convolutionMatrix(bumpMatrix, image);
            break;
            case HIGHPASS:
            behaviorChange = 1;
            int highPassMatrix[3][3]={{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
            convolutionMatrix(highPassMatrix, image);
            break;
            case LOWPASS:
            behaviorChange = 1;
            int lowPassMatrix[3][3]={{1, 1, 1}, {1, 4, 1}, {1, 1, 1}};
            convolutionMatrix(lowPassMatrix, image);
            break;
            default: ;
            break;
        }

        // display and store the change
        char modificationText[255];
        if(behaviorChange==0){
            sprintf(modificationText, "Add %s, parameter %d\n", changesChosen->changes[i], changesChosen->params[i]);
        }else{
            sprintf(modificationText, "Add %s\n", changesChosen->changes[i]);
        }  
        printf("%s", modificationText);
        strcpy(modifications[*nbModifications], modificationText);
        (*nbModifications)++;
    }
}

change convertStringToChange(char *str){
    if(!(strcmp(str, "SEPIA"))) return SEPIA;
    else if(!(strcmp(str, "BLACKANDWHITE"))) return BLACKANDWHITE;
    else if(!(strcmp(str, "BLUR"))) return BLUR;
    else if(!(strcmp(str, "REINEDGES"))) return REINEDGES;
    else if(!(strcmp(str, "DETECTEDGES"))) return DETECTEDGES;
    else if(!(strcmp(str, "BUMP"))) return BUMP;
    else if(!(strcmp(str, "HIGHPASS"))) return HIGHPASS;
    else if(!(strcmp(str, "LOWPASS"))) return LOWPASS;
    else return -1;
}

void blackAndWhite(Image *image) {
    for (int i = 0; i < (image->width)*(image->height)*3; i=i+3) {
        int value = (image->data[i]+image->data[i+1]+image->data[i+2])/3;
        image->data[i] = value;
        image->data[i+1] = value;
        image->data[i+2] = value;
    }
}

void sepia(int param, Image *image) {
    for (int i = 0; i < (image->width)*(image->height)*3; i=i+3) {
        int r = image->data[i];
        int g = image->data[i+1];
        int b = image->data[i+2];
        image->data[i] = max(min((r*0.393)+(g*0.769)+(b*0.189)+param, 255), 0);
        image->data[i+1] = max(min((r*0.349)+(g*0.686)+(b*0.168)+param, 255),0);
        image->data[i+2] = max(min((r*0.272)+(g*0.534)+(b*0.131), 255), 0);
    }
}

void convolutionMatrix(int (*matrix)[3], Image *image) {
    // create another image to store the changed values
    Image imageWithEffect;
    newImage(&imageWithEffect, image->width, image->height);

    // related parameters of the convolution matrix
    int divisor=0, lag=0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            divisor=divisor+(matrix[i][j]);
        }
    }
    if(divisor==0){
        lag=128;
        divisor=1;
    }else if(divisor<0){
        lag=255;
        divisor=-divisor;
    }

    for(int i=image->width*3+3; i<(image->width)*(image->height)*3-(image->width)*3; i++) {
        // apply the convolution matrix to the value
        int value=0;
        for(int j=0; j<=2; j++) {
            value=value+(matrix[0][j]*image->data[i-(image->width)*3-3+3*j]);
        }
        for(int j=0; j<=2; j++) {
            value=value+(matrix[1][j]*image->data[i-3+3*j]);
        }
        for(int j=0; j<=2; j++) {
            value=value+(matrix[2][j]*image->data[i+(image->width)*3-3+3*j]);
        }
        // store the changed value in the new image (with correction and related parameters)
        value=value+lag;
        value=value/divisor;
        if(value<0){
            value=0;
        }else if(value>255) {
            value=255;
        }
        imageWithEffect.data[i]=value;
    }

    // replace the image with the new image
    for (int i = image->width*3+3; i<(image->width)*(image->height)*3-(image->width)*3; i++) {
        image->data[i] = imageWithEffect.data[i];
    }
}