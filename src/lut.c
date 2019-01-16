#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lut.h"
#include "image.h"
#include "mathf.h"

void DIMCON(Image* image, int n) {
    float coeff = 1.0/n;
    for (int i = 0; i < (image->width)*(image->height)*3-2; i=i+3){
        float a = (image->data[i]+image->data[i+1]+image->data[i+2])/3;
        float b = 255*exp(coeff*log(a/255));
		image->data[i]=max(0, min(255, image->data[i]+b-a));
		image->data[i+1]=max(0, min(255, image->data[i+1]+b-a));
		image->data[i+2]=max(0, min(255, image->data[i+2]+b-a));
}}



void INVERT(Image* image) {
    for (int i = 0; i < (image->width)*(image->height)*3; ++i){
        image->data[i]=255-image->data[i];
    }
}

int[] INVERTLUT() {
    int[] lut[256];
    for(int i=0; i<255; i++) {
        lut[i]=255-i;
    }
    return lut;
}

void SEPIA(Image* image, int coeff) {
    for (int i = 0; i < (image->width)*(image->height)*3-2; i=i+3) {
        int r = image->data[i];
        int g = image->data[i+1];
        int b = image->data[i+2];
        image->data[i] = max(min((r*0.393)+(g*0.769)+(b*0.189)+coeff, 255), 0);
        image->data[i+1] = max(min((r*0.349)+(g*0.686)+(b*0.168)+coeff, 255),0);
        image->data[i+2] = max(min((r*0.272)+(g*0.534)+(b*0.131), 255), 0);
    }
}

void appliqueLUT(Image* image, lut lut ) {
    int[] LUT = lut;
    for(int i = 0; i < (image->width)*(image->height)*3; ++1) {
        image->data[i]=LUT(image->data[i]),
    }
}
