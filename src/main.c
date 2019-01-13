#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"


int main(int argc, char *argv[]){
    /*
    //check arguments => !code later!
    if(argc<=6){
        printf("usage : %s mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char imageToEdit[255];
    strcpy(imageToEdit, argv[1]);
    printf("%s ", imageToEdit);
    */

    // create an image
    Image image;

    // load a ppm file
    if(loadImagePPM(&image,"images/image.ppm") != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }

    //modify the image => !LUT to code later!
    //red pixel in the center
    unsigned int pixel = (image.width*(image.height/2) + (image.width/2))*3;
    printf("%d\n",pixel);
    image.data[pixel + 0] = 255;
    image.data[pixel + 1] = 0;
    image.data[pixel + 2] = 0;
    //augmentation de luminosité
    for (int i = 0; i < image.width*image.height*3; ++i){
        if(image.data[i]>=205){
            image.data[i]=255;
        }else{
            image.data[i]+=50;
        }
    }
    //printf("%u\n", image.data[0]);

    // save the image (if the directory "images" already exists)
    saveImagePPM(&image, "images/output.ppm");

    // free the image memory
    freeImage(&image);

    return 0;
}
   

