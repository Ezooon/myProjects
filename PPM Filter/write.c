#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

void writePPM(const char *file, int width, int height, int max, const RGB *image)
{
  FILE *newfile;
  newfile=fopen(file,"w");
  /*Print the first 3 lines of newfile*/
  fprintf(newfile, "P3\n%d %d\n%d\n",width,height,max);

  int newlines=0, j;

  /* Iterate over the entire in RGB array and 
  store each RGB value into the new ppm file */
  for (j=0;j<(width)*(height); j++)
  {
  	newlines++;
  	fprintf(newfile,"%d %d %d ",(image+j)->r,(image+j)->g,(image+j)->b);
  	
  	/* Print a newline every 21 entires so a line doesnt get too large */
  	if (newlines%7==0)     
  	fprintf(newfile,"\n");
  }
	fclose(newfile);
}
