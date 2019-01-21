#include <stdio.h>

#include "mathf.h"

float max(float a, float b) {
    if(a>b) {
        return a;
    }
    return b;
}

float min(float a, float b) {
    if(a<b) {
    	return a;
    }
    return b;
}

int maxInArray(int *tab, int sizeTab) {
    int max=tab[0];
    for(int i=1; i<sizeTab-1; i++) {
        if(tab[i]>max) {
            max=tab[i];
        }
    }
    return max;
}
