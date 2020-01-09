#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

/* Function used for sorting array with qsort */
int compare(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}



RGB *denoiseImage(int width, int height, const RGB *image, int n, filter f){

/***** MEAN FILTER ******/
if (f == MEAN)
{

  static RGB* newimage;
  newimage=malloc((width)*(height) * sizeof(RGB)); /*Create new RGB array and allocate storage */

  int i,j,r,m,rsum,gsum,bsum,centerpixel, pixelinwindow, numofentries;

  /* Sum over all of the pixels in the image.
  i and j represent the row and column of image.
  Within each pixel, sum over an r by m window of size n*n centered around
  the corresponding pixel. Add the RGB values in each pixel to their corresponding
  sumrs; rsum, gsum, and bsum, then compute the average for 
  each sum. If a pixel in the window is oustide the image, don't include 
  its RGB values in the sums. Keep track of the number of pixels 
  you added with numofentries */

  for (i=0;i<height;i++)
  {
    for (j=0;j<width;j++)
    {
      centerpixel=i*width+j;
      numofentries=0;
      rsum=0;
      gsum=0;
      bsum=0;

      for (r=0;r<n;r++) 
      {
        for (m=0;m<n;m++)
        {
          /*Compute the indexes of the pixels in the window. Start with the
          top most left pixel */
          pixelinwindow=((centerpixel-n/2)-(n/2)*(width))+r*width + m;

          /* Determine if the pixelinwindow is outside the image */
          if ((pixelinwindow < 0) ||              /* Determines if pixel is above the image */
            (pixelinwindow > width*height) ||     /* Determines if pixel is below the image */
            ((centerpixel < (i*width +n/2)) && (j - (j-(n/2)+m)) > j) ||                     /* Determines if pixel is outside to the left of the image */
            ((centerpixel >= ((i+1)*width - n/2)) && ((j-((n/2)-m)) - j > ((width-1) - j)))) /* Determines if pixel is outsideto the right of the image */
          {
            /*If pixel is outside of image, don't add it to the sum */
          }

          else
          {
            /*If pixel is inside image, update numofentries by 1 and add its RGB values to rsum, gsum, bsum */
            numofentries++;
            rsum+=(image+pixelinwindow)->r;
            gsum+=(image+pixelinwindow)->g;
            bsum+=(image+pixelinwindow)->b;
          }
        }
      }
      /*Compute the averages of rsum, gsum, and bsum and store in the center pixel */
      /* This method of integer division rounds to the nearest integers= */
      (newimage+centerpixel)->r = (rsum + (numofentries/2)) / numofentries;
      (newimage+centerpixel)->g = (gsum + (numofentries/2)) / numofentries;
      (newimage+centerpixel)->b = (bsum + (numofentries/2)) / numofentries;
    }

  }
  return newimage;
}

/***** MEDIAN FILTER ******/
if (f == MEDIAN)
{

  static RGB* newimage;
  newimage=malloc((width)*(height) * sizeof(RGB));

  int j,i,r,m,centerpixel, pixelinwindow;

  int red[n*n], green[n*n], blue[n*n]; /*Create 3 arrays to store pixel values */

  /* Sum over all of the pixels in the image.
  i and j represent row and column of image.
  Within each pixel, iterate over an r by m window of size n*n.
  Store the RGB values of each pixel in the window into
  the arrays red, green, blue. Assume pixels in a window outside the image have 
  RGB values of 0 0 0. After entering all pixel values from
  a window into the arrays, sort the arrays with qsort and find the median values*/
  for (i=0;i<height;i++)
  {
    for (j=0;j<width;j++)
    {
      centerpixel=i*width+j;

      for (r=0;r<n;r++) 
      {
        for (m=0;m<n;m++)
        {
          /*Compute the indexes of the pixels in the window. Start with the
          top most left pixel */
          pixelinwindow=((centerpixel-n/2)-(n/2)*(width))+r*width + m;

          if ((pixelinwindow < 0) ||          /* Determines if pixel is above the image */
            (pixelinwindow > width*height) || /* Determines if pixel is below the image */
            ((centerpixel < (i*width +n/2)) && (j - (j-(n/2)+m)) > j) ||                     /* Determines if pixel is outside to the left of the image */
            ((centerpixel >= ((i+1)*width - n/2)) && ((j-((n/2)-m)) - j > ((width-1) - j)))) /* Determines if pixel is outside to the right of the image */
          {
            /*If a pixel in the window is not in the image, assume R G B values of 0 */
            red[n*r+m]=0;
            green[n*r+m]=0;
            blue[n*r+m]=0;
          }
          else
          {
            /* If a pixel in the window is in the image, store the R G B values into the corresponding arrays */
            red[n*r+m]=(image+pixelinwindow)->r;
            green[n*r+m]=(image+pixelinwindow)->g;
            blue[n*r+m]=(image+pixelinwindow)->b;
          }
        }
      }
      /* Sort the arrays in ascending order*/
      qsort(&red,(sizeof(red)/sizeof(red[0])),sizeof(red[0]),compare);
      qsort(&green,(sizeof(green)/sizeof(green[0])),sizeof(green[0]),compare);
      qsort(&blue,(sizeof(blue)/sizeof(blue[0])),sizeof(blue[0]),compare);
      /*Find the median value and store into the R G B values of the center pixel*/
      (newimage+centerpixel)->r = red[(n*n)/2];
      (newimage+centerpixel)->g = green[(n*n)/2];
      (newimage+centerpixel)->b = blue[(n*n)/2];
    }

  }
  return newimage;
}

/*This function will never take a filter value other than MEAN or MEDIAN becuase 
I error checked that the user entered 'A' or 'M' in the main.c program.
However to satisfy compiler warnings, I added this return NULL statement */
return NULL;

}
