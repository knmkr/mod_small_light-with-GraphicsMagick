#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wand/magick_wand.h>

int main(int argc,char **argv)
  {
    MagickWand *magick_wand;
    MagickPassFail status = MagickPass;
    const char *infile, *outfile;

    // Parameters for resizing
    const unsigned long DST_WIDTH = 140;
    const unsigned long DST_HEIGHT = 140;
    /* const FilterTypes DST_FILTERTYPE = LanczosFilter; */
    /* const double DST_BLUR = 1.0; */

    if (argc != 3)
          {
            fprintf(stderr,"Usage: %s: infile outfile\n",argv[0]);
            return 1;
          }

    infile=argv[1];
    outfile=argv[2];

    // Initialize GraphicsMagick API
    InitializeMagick(*argv);

    // Allocate Wand handle
    magick_wand=NewMagickWand();

    // Read input image file
    if (status == MagickPass)
          {
            status = MagickReadImage(magick_wand,infile);
          }

    // Set the size of the magick wand
    if (status == MagickPass)
          {
            status = MagickSetSize(magick_wand, (long)300, (long)300);
          }

    // Resize image
    if (status == MagickPass)
          {
            status = MagickResizeImage(magick_wand, DST_WIDTH, DST_HEIGHT,
                                       (FilterTypes)LanczosFilter, (double)1.0);
          }


    // Write output file
    if (status == MagickPass)
          {
            status = MagickWriteImage(magick_wand,outfile);
          }

    // Diagnose any error
    if (status != MagickPass)
          {
            char *description;
            ExceptionType severity;

            description=MagickGetException(magick_wand,&severity);
            (void) fprintf(stderr,"%.1024s (severity %d)\n",
                           description,severity);
          }

    // Release Wand handle
    DestroyMagickWand(magick_wand);

    // Destroy GraphicsMagick API
    DestroyMagick();

    return (status == MagickPass ? 0 : 1);
  }
