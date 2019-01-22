#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "ihm.h"
#include "histogram.h"
#include "history.h"

int main(int argc, char *argv[]){

    char imageToEdit[255]="images/default_input.ppm";
    char imageOutput[255]="images/default_output.ppm";
    LutsToApply lutsChoosed;

    int histogram=0;
    int history=0;
    char modifications[255][255];
    int nbModifications=0;

    if(storeArguments(argc, argv, imageToEdit, imageOutput, &lutsChoosed, &histogram, &history) != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }

    // create an image
    Image image;

    // load a ppm file
    if(loadImagePPM(&image,imageToEdit) != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }

    // histogram input
    if(histogram){
        int histogramInputTab[256];

        buildHistogram(&image, histogramInputTab, all);
        Image histogramImageInput;
        buildHistogramImage(&histogramImageInput, histogramInputTab);

        char histogramImageInputName[255]="";
        strncpy(histogramImageInputName, imageToEdit, strlen(imageToEdit)-4);
        strcat(histogramImageInputName, "_histogram.ppm");

        if(saveImagePPM(&histogramImageInput, histogramImageInputName)){
            return EXIT_FAILURE;
        }
        printf("Histogramme de l'image de départ enregistré ici : %s\n", histogramImageInputName);

        freeImage(&histogramImageInput);
    }

    applyLut(&image, &lutsChoosed, modifications, &nbModifications);

    // save the image (if the directory "images" already exists)
    if(saveImagePPM(&image, imageOutput) != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }
    printf("Image éditée enregistrée ici : %s\n", imageOutput);

    // histogram output
    if(histogram){
        int histogramOutputTab[256];

        buildHistogram(&image, histogramOutputTab, all);
        Image histogramImageOutput;
        buildHistogramImage(&histogramImageOutput, histogramOutputTab);

        char histogramImageOutputName[255]="";
        strncpy(histogramImageOutputName, imageOutput, strlen(imageOutput)-4);
        strcat(histogramImageOutputName, "_histogram.ppm");

        if(saveImagePPM(&histogramImageOutput, histogramImageOutputName) != EXIT_SUCCESS){
            return EXIT_FAILURE;
        }
        printf("Histogramme de l'image éditée enregistré ici : %s\n", histogramImageOutputName);

        freeImage(&histogramImageOutput);
    }

    if(history){
        char historyInputName[255]="";
        strncpy(historyInputName, imageToEdit, strlen(imageToEdit)-4);
        strcat(historyInputName, "_history.txt");

        char historyOutputName[255]="";
        strncpy(historyOutputName, imageOutput, strlen(imageOutput)-4);
        strcat(historyOutputName, "_history.txt");

        if(saveHistory(modifications, &nbModifications, historyInputName, historyOutputName) != EXIT_SUCCESS){
            return EXIT_FAILURE;
        }
    }

    // free the image memory
    freeImage(&image);

    return 0;
}
   

