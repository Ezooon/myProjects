#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filter.h"

int main(int argc, char *argv[]){

  /* If the user doesn't enter 4 command line arguments, print error and terminate */
  if (argc != 5 )
  {
    printf("Usage error: ./denoise input.ppm output.ppm N F\nterminating...\n");
    return 0;
  }

  /* This program was designed to take only odd n inputs, so print error if n is even */
  if (atoi(argv[3]) % 2 == 0 && !(atoi(argv[3]) < 0))
  {
    printf("Error: Number must be odd and positive\nterminating...\n");
    return 0;
  }

  filter filtertype;

  /* Ensure that the user scpecified either a mean or median filter */
  /* If not,complain */
  if (*(argv[4]) == 'A')
    filtertype=MEAN;
  else if (*(argv[4])== 'M')
    filtertype=MEDIAN;
  else
  {
    printf("Invalid filter type %s, \nterminating...\n",argv[4]);
    return 0;
  }


  RGB *filein, *fileout;
  int width, height, max;
  double time,readtime,writetime, processtime;


  /* Read file */
  printf("\nReading file %s\n",argv[1]); 
  time=getTime(2);
  filein=readPPM(argv[1], &width, &height, &max);
  readtime=getTime(2)-time;
  /* If input file is NULL, return error */
    if (filein == NULL)
    {
        printf("Error in reading file\nterminating...\n");
        return 0;
    }
  printf("***    %s read\tin %.1e seconds\n\n",argv[1],readtime);



  /*Filter file */
  printf("Processing %d x %d image using %d x %d window and %s filter...\n",width,height,atoi(argv[3]),atoi(argv[3]),(filtertype == 0) ? "mean" : "median");
  time=getTime(2);
  fileout=denoiseImage(width,height,filein,atoi(argv[3]),filtertype);
  processtime=getTime(2)-time;
  printf("***    image processed in  %.1e seconds\n\n",processtime);


  /*Write file */
  printf("Writing file %s\n",argv[2]);
  time=getTime(2);
  writePPM(argv[2],width,height,max,fileout);
  writetime=getTime(2)-time;
  /* If output file is NULL, return error */
    if (fileout == NULL)
    {
        printf("Error in writing file\nterminating...\n");
        return 0;
    }
  printf("***    %s written in %.1e seconds\n\n",argv[2],writetime);

  return 0;
}
