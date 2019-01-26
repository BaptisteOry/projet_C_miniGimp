#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "lut.h"
#include "change.h"
#include "ihm.h"
#include "histogram.h"
#include "history.h"

int main(int argc, char *argv[]){

    // initialization of the options chosen by the user
    char imageToEdit[255]="images/default_input.ppm";
    char imageOutput[255]="images/default_output.ppm";
    LutsToApply chosenLuts;
    ChangesToApply chosenChanges;
    int histogram=0;
    int history=0;
    char modifications[255][255];
    int nbModifications=0;

    // storage of options chosen by the user
    if(storeArguments(argc, argv, imageToEdit, imageOutput, &chosenLuts, &chosenChanges, &histogram, &history) != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }

    // create an image
    Image image;

    // load a ppm file chosen by the user
    if(loadImagePPM(&image,imageToEdit) != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }

    // create the histogram input
    if(histogram){
        int histogramInputTab[256];

        buildHistogram(&image, histogramInputTab, all);
        Image histogramImageInput;
        buildHistogramImage(&histogramImageInput, histogramInputTab);

        char histogramImageInputName[255];
        nameHistogram(histogramImageInputName, imageToEdit);

        if(saveImagePPM(&histogramImageInput, histogramImageInputName)){
            return EXIT_FAILURE;
        }
        printf("Histogram of the input image saved here: %s\n", histogramImageInputName);

        freeImage(&histogramImageInput);
    }

    // application of the luts (effects) chosen by the user
    if(chosenLuts.nbLuts != 0){
        applyLuts(&image, &chosenLuts, modifications, &nbModifications);
    }

    // // application of the changes (effects) chosen by the user
    if(chosenChanges.nbChanges != 0){
        applyChanges(&image, &chosenChanges, modifications, &nbModifications);
    }
    
    // save the image (if the directory "images" already exists)
    if(saveImagePPM(&image, imageOutput) != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }
    printf("Output image saved here: %s\n", imageOutput);

    // create the histogram ouput
    if(histogram){
        int histogramOutputTab[256];

        buildHistogram(&image, histogramOutputTab, all);
        Image histogramImageOutput;
        buildHistogramImage(&histogramImageOutput, histogramOutputTab);

        char histogramImageOutputName[255];
        nameHistogram(histogramImageOutputName, imageOutput);

        if(saveImagePPM(&histogramImageOutput, histogramImageOutputName) != EXIT_SUCCESS){
            return EXIT_FAILURE;
        }
        printf("Histogram of the output image saved here: %s\n", histogramImageOutputName);

        freeImage(&histogramImageOutput);
    }

    // create the history
    if(history){
        char historyInputName[255], historyOutputName[255];
        nameHistory(historyInputName, imageToEdit);
        nameHistory(historyOutputName, imageOutput);

        if(saveHistory(modifications, &nbModifications, historyInputName, historyOutputName) != EXIT_SUCCESS){
            return EXIT_FAILURE;
        }
        printf("History of the output image saved here: %s\n", historyOutputName);
    }

    // free the image memory
    freeImage(&image);

    return 0;
}
   

