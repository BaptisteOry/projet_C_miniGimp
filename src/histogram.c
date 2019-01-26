#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mathf.h"
#include "image.h"
#include "histogram.h"

void nameHistogram(char *histogramImageName, char *nameImage){
    strncpy(histogramImageName, nameImage, strlen(nameImage)-4);
    histogramImageName[strlen(nameImage)-4] = '\0';
    strcat(histogramImageName, "_histogram.ppm");
}

void buildHistogram(Image *image, int *histogramTab, colour chosenColour) {
    // initialize the histogram table
    for(int i=0; i<256; i++) {
        histogramTab[i]=0;
    }

    // create the histogram for the 3 colors (gray level)
    if(chosenColour==all) {
        for(int i=0; i<(image->width)*(image->height)*3; i++) {
            int value = image->data[i];
            histogramTab[value]=histogramTab[value]+1;
        }

    // create the histogram for one color (red, green or blue)
    }else {
        for(int i=chosenColour; i<(image->width)*(image->height)*3; i=i+3) {
            int value = image->data[i];
            histogramTab[value]=histogramTab[value]+1;
        }
    }
}

int buildHistogramImage(Image *histogramImage, int *histogramTab) {
    // initialize the height and width of the histogram image
    int widthHistogramImage=256*2, heightHistogramImage=200;
    
    // make the histogram table proportional to the height of the histogram image
    int max = maxInArray(histogramTab, 256);
    for(int i=0; i<256; i++) {
        histogramTab[i]=histogramTab[i]*heightHistogramImage/max;
    }

    // create the histogram image
    if(newImage(histogramImage, widthHistogramImage, heightHistogramImage)){
        return EXIT_FAILURE;
    }

    // fill in the histogram image according to the histogram table
    for(int i=0; i<heightHistogramImage*widthHistogramImage*3; i=i+3*(widthHistogramImage/256)) {
        if(histogramTab[(i/((widthHistogramImage/256)*3))%256]>=(heightHistogramImage)-(i/((widthHistogramImage)*3))) {
            for(int j=0; j<3*((widthHistogramImage)/256); j++) {
                histogramImage->data[i+j]=255;
            }
        }else {
            for(int j=0; j<3*((widthHistogramImage)/256); j++) {
                histogramImage->data[i+j]=0;
            }
        }
    }

    return EXIT_SUCCESS;
}
