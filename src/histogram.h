#ifndef HISTOGRAM_H__
#define HISTOGRAM_H__

/// \brief create the name for the histogram image
/// \param histogramImageName: pointer on the name of the histogram image
/// \param nameImage: pointer on the image associated with the histogram image
void nameHistogram(char *histogramImageName, char *nameImage);

/// \brief create the histogram table for an image
/// \param image: pointer on the image from which the histogram will be created
/// \param histogramTab: histogram table to fill according to the image
/// \param colourChosen: color of the chosen image (enumeration), according to which to fill the histogram table
void buildHistogram(Image *image, int *histogramTab, colour colourChosen);

/// \brief create the image histogram according to the histogram table
/// \param histogramImage: pointer on the histogram image to fill according to the histogram table
/// \param histogramTab: histogram table with the values to create the histogram image
/// \return EXIT_FAILURE in case of problem, else EXIT_SUCCESS
int buildHistogramImage(Image *histogramImage, int *histogramTab);

#endif

