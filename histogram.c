#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "histogram.h"
#include "mathf.h"

void tabhisto(Image image, int tab[], colour colour) {
    int compt=0;
    for(int i=0; i<256; i++) {
        tab[i]=0;
    }
    for(int i=colour; i<(image.width)*(image.height)*3; i=i+3) {
        int value = image.data[i];
        tab[value]=tab[value]+1;
 //       printf("nb %d\n", tab[value]);
    }
    for(int i=0; i<256; i++) {
        compt=compt+tab[i];
//        printf("%d\n", tab[i]);
    }
//    printf("compteur test %d\n", compt);
//    printf("taille image %d\n", (image.width)*(image.height));
}

void histogram(Image* histo, int tab[]) {
    int max = maxInArray(tab, 256);
    printf("max = %d\n", max);
    newImage(histo, 256*50, max);
//    int cont=0;
    for(int i=0; i<(histo->height)*(histo->width)*3-2; i=i+3*((histo->width)/256)) {
//        printf("ligne %d\n", i/(histo->width*3));
//        printf("ligne inv %d\n", (histo->height)-(i/(256*3)));
        if(tab[(i/((histo->width/256)*3))%256]>=(histo->height)-(i/((histo->width)*3))) {
//                printf("testest %d\n", (i/(40*3))%256);
            for(int j=0; j<3*((histo->width)/256); j++) {
                histo->data[i+j]=255;
            }
        }
        else {
            for(int j=0; j<3*((histo->width)/256); j++) {
                histo->data[i+j]=0;
            }
        }
//        cont++;
    }
//    printf("cont =%d\n", cont);
//    printf("nb pixels =%d\n", (histo->height)*(histo->width));
}
