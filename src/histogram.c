#include <stdio.h>
#include <stdlib.h>

#include "mathf.h"
#include "image.h"
#include "histogram.h"

void buildHistogram(Image *image, int *histogramTab, colour colourChoosed) {
    int compt=0;
    for(int i=0; i<256; i++) {
        histogramTab[i]=0;
    }
    for(int i=colourChoosed; i<(image->width)*(image->height)*3; i=i+3) {
        int value = image->data[i];
        histogramTab[value]=histogramTab[value]+1;
    }
    for(int i=0; i<256; i++) {
        compt=compt+histogramTab[i];
    }
}

int buildHistogramImage(Image *histogramImage, int *histogramTab) {
    int max = maxInArray(histogramTab, 256);
    if(newImage(histogramImage, 256*50, max)){
        printf("newImage for histogram : memory allocation error\n");
        return EXIT_FAILURE;
    }
    for(int i=0; i<(histogramImage->height)*(histogramImage->width)*3-2; i=i+3*((histogramImage->width)/256)) {
        if(histogramTab[(i/((histogramImage->width/256)*3))%256]>=(histogramImage->height)-(i/((histogramImage->width)*3))) {
            for(int j=0; j<3*((histogramImage->width)/256); j++) {
                histogramImage->data[i+j]=255;
            }
        }
        else {
            for(int j=0; j<3*((histogramImage->width)/256); j++) {
                histogramImage->data[i+j]=0;
            }
        }
    }
    return EXIT_SUCCESS;
}
