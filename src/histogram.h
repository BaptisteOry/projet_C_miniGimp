#ifndef HISTOGRAM_H__
#define HISTOGRAM_H__

void nameHistogram(char *histogramImageName, char *nameImage);
void buildHistogram(Image *image, int *histogramTab, colour colourChoosed);
int buildHistogramImage(Image *histogramImage, int *histogramTab);

#endif

