#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "image.h"
#include "lut.h"

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
        if(lutTab[i]>=128+param){
            if(lutTab[i]+param<255){
                lutTab[i]=lutTab[i]+param;
            }else{
                lutTab[i]=255;
            }
        }else if(lutTab[i]<=128-param){
            if(lutTab[i]-param>0){
                lutTab[i]=lutTab[i]-param;
            }else{
                lutTab[i]=0;
            }
        }
    }
}

void invertlut(int *lutTab) {
    for(int i = 0; i <= 255; i++) {
        lutTab[i]=255-i;
    }
}

void applyLut(Image *image, lut *luts, int *params){
    // initialise tab lut
    int lutTab[256];
    for (int i = 0; i <= 255; i++){
        lutTab[i]=i;
    }
    
    for (int i = 0; i<3; i++){
        switch ((int)luts[i]){
            case 0:
            addlum(params[i], lutTab);
            break;
            case 1:
            dimlum(params[i], lutTab);
            break;
            case 2:
            addcon(params[i], lutTab);
            break;
            case 4:
            invertlut(lutTab);
            break;
            default:
            addcon(params[i], lutTab);
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