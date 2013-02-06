#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wand/magick_wand.h>

int main(int argc,char **argv)
  {
    MagickWand *magick_wand;
    MagickPassFail status = MagickPass;
    const char *infile, *outfile;

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

    // Rotate image clockwise 30 degrees with black background
    if (status == MagickPass)
          {
            PixelWand *background;
            background=NewPixelWand();
            PixelSetColor(background,"#000000");
            status = MagickRotateImage(magick_wand,background,30);
            DestroyPixelWand(background);
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
