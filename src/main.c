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

    char imageToEdit[255]="images/default_input.ppm";
    char imageOutput[255]="images/default_output.ppm";
    LutsToApply lutsChoosed;
    ChangesToApply changesChoosed;

    int histogram=0;
    int history=0;
    char modifications[255][255];
    int nbModifications=0;

    if(storeArguments(argc, argv, imageToEdit, imageOutput, &lutsChoosed, &changesChoosed, &histogram, &history) != EXIT_SUCCESS){
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

        char histogramImageInputName[255];
        nameHistogram(histogramImageInputName, imageToEdit);

        if(saveImagePPM(&histogramImageInput, histogramImageInputName)){
            return EXIT_FAILURE;
        }
        printf("Histogramme de l'image de départ enregistré ici : %s\n", histogramImageInputName);

        freeImage(&histogramImageInput);
    }

    if(lutsChoosed.nbLuts != 0){
        applyLuts(&image, &lutsChoosed, modifications, &nbModifications);
    }

    if(changesChoosed.nbChanges != 0){
        applyChanges(&image, &changesChoosed, modifications, &nbModifications);
    }
    
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

        char histogramImageOutputName[255];
        nameHistogram(histogramImageOutputName, imageOutput);

        if(saveImagePPM(&histogramImageOutput, histogramImageOutputName) != EXIT_SUCCESS){
            return EXIT_FAILURE;
        }
        printf("Histogramme de l'image éditée enregistré ici : %s\n", histogramImageOutputName);

        freeImage(&histogramImageOutput);
    }

    if(history){
        char historyInputName[255], historyOutputName[255];
        nameHistory(historyInputName, imageToEdit);
        nameHistory(historyOutputName, imageOutput);

        if(saveHistory(modifications, &nbModifications, historyInputName, historyOutputName) != EXIT_SUCCESS){
            return EXIT_FAILURE;
        }
        printf("Historique de l'image éditée enregistré ici : %s\n", historyOutputName);
    }

    // free the image memory
    freeImage(&image);

    return 0;
}
   

