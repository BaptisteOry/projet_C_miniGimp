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