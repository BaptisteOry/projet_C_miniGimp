#include <stdio.h>
#include <stdlib.h>

#include "image.h"

int newImage(Image *image, unsigned int width, unsigned int height)
{
  // memory allocation
  image->data = (unsigned char*) malloc(sizeof(unsigned char) * width*height*3);
  if(image->data == NULL){
    printf("newImage: error bad memory allocation.\n");
    return EXIT_FAILURE;
  }

  // update width and height
  image->width  = width;
  image->height = height;

  return EXIT_SUCCESS;
}

void freeImage(Image *image)
{
  if(image != NULL) {
    if(image->data != NULL)	{
	    free(image->data);
      image->data= NULL;
    }

    image->width  = 0;
    image->height = 0;
	}
}

int saveImagePPM(Image *image, char *filename)
{
  // open the file for writing (wt)
  FILE *myfile;
  myfile = fopen(filename,"wt");

  // save the data
  if (myfile)
  {
    // generate the header
    char header[100];
    sprintf(header,"P6\n%d %d\n255\n",image->width,image->height);
    fprintf(myfile,"%s",header);

    // write the data
    fwrite(image->data,sizeof(unsigned char),image->width*image->height*3,myfile);

    // close the file
    fclose(myfile);
  }else{
    printf("saveImagePPM: error opening file %s.\n",filename);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

// reads only P6
int loadImagePPM(Image *image, char *filename){
  FILE *myFile = NULL;
  char chaine[255];
  unsigned int width,height;

  // open the file for reading (rt)
  if (!(myFile = fopen(filename, "rt"))){ 
    printf("loadImagePPM: error opening file %s.\n",filename);
    return EXIT_FAILURE;
  }

  // read header "P6"
  fscanf(myFile,"%s\n",chaine);

  // read comments
  do{ 
    fgets(chaine,255,myFile);
  } while (chaine[0]=='#');
  
  // read width and height
  sscanf(chaine,"%d %d",&width,&height);

  // read the "255"
  fscanf(myFile,"%s\n",chaine);

  // memory allocation
  if(newImage(image,width,height) == EXIT_FAILURE){
    printf("newImage: memory allocation error\n");
    return EXIT_FAILURE;
  }

  // read the store data
  fread(image->data, sizeof(unsigned char), width*height*3, myFile);

  // close the file
  fclose(myFile);

  return EXIT_SUCCESS;
}
