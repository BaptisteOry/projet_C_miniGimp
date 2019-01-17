#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "mathf.h"
#include "lut.h"

int main(int argc, char *argv[]){

    char imageToEdit[255];
    if (argv[1]){
        if (strstr(argv[1], ".ppm")){
            strcpy(imageToEdit, argv[1]);
            printf("%s\n", imageToEdit);
        }else{
            printf("%s\n", "Please enter the address of the ppm image to edit.");
            printf("usage : %s mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }else{
        printf("%s\n", "Please enter the address of the ppm image to edit.");
        printf("usage : %s mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char imageOutput[255]="default_output.ppm";
    if (strstr(argv[argc-2], "-o")){
        if (strstr(argv[argc-1], ".ppm")){
            strcpy(imageOutput, argv[argc-1]);
            printf("%s\n", imageOutput);
        }else{
            printf("%s\n", "Please enter the address of an output ppm image.");
            printf("usage : %s mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }else{
        printf("%s\n", "Please enter the address of an output ppm image.");
        printf("usage : %s mon_image.ppm [-h] [-histo] [<code_lut>[_<param1>]*]* [-o image_sortie.ppm]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // create an image
    Image image;

    // load a ppm file
    if(loadImagePPM(&image,"images/image.ppm") != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }

    lut luts[3]= {DIMLUM, ADDLUM, INVERTLUT};
    int params[3]= {100, 20, 150};

    applyLut(&image, luts, params);

    // save the image (if the directory "images" already exists)
    saveImagePPM(&image, "images/output.ppm");

    // free the image memory
    freeImage(&image);

    //modify the image => !LUT to code later!
    /*red pixel in the center
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
    printf("%u\n", image.data[0]);*/

    return 0;
}
   

