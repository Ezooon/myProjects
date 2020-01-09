#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filter.h"


RGB *readPPM(const char *file, int *width, int *height, int *max)
{
  FILE *filein;
  char line[200];         /*Create line buffer to store line in file*/

  filein=fopen(file, "r");
  if (filein == NULL)     /* If file cannot be opened, return NULL*/
  {
    return NULL;
  }

  fgets(line,sizeof(line),filein);     /* Skip first line */
  fgets(line,sizeof(line),filein);     /* Go to the second line to get width and height */
  sscanf(line, "%d %d", width, height);
  fgets(line,sizeof(line),filein);     /* Go to the third line to get max RBG value */
  sscanf(line, "%d", max);



  static RGB* fileout;                   /*Create array of RGB structures to store RGB values */
  char *value = line, *newline = "\n";   /*value is the RGB value in the .ppm file that will be stored in the line buffer */
  int i=0;

  fileout=malloc((*width)*(*height) * sizeof(RGB));

  /* While a line is not null (which indicates end of file), extract a line and 
  split the elements in the line by the space character using strtok. Do this 3 times 
  to extract the red green and blue values. Continue to the next line when your 
  value is a newline character */
 
while ((fgets(line,sizeof(line), filein)) != NULL)
{
    value=strtok(line, " ");

  while(strcmp(value,newline) != 0)
  {
  	(fileout+i)->r=atoi(value);
  	value=strtok(NULL, " ");
  	(fileout+i)->g=atoi(value);
  	value=strtok(NULL, " ");
  	(fileout+i)->b=atoi(value);
	value=strtok(NULL, " ");
	i++;
  }
}
  fclose(filein);

  return fileout;

}
