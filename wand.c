#include <stdio.h>
#include <stdlib.h>
#include <wand/MagickWand.h>

int main(int argc,char **argv)
{
#define ThrowWandException(wand) \
{ \
  char \
    *description; \
 \
  ExceptionType \
    severity; \
 \
  description=MagickGetException(wand,&severity); \
  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
  description=(char *) MagickRelinquishMemory(description); \
  exit(-1); \
}
  
  /* DEFINE PARAMETERS required for output:
     x size
     y wize
     
    TODO: default values
    TODO: arg parameters
  */


  MagickBooleanType
    status;

  MagickWand
    *magick_wand;
    
  PixelWand
    *bgcolor;

  DrawingWand
    *drawing_wand;
  /*
  if (argc != 3)
    {
      (void) fprintf(stdout,"Usage: %s image thumbnail\n",argv[0]);
      exit(0);
    }
  */
  
  /*
    Initialize an image.
  */
  MagickWandGenesis();

  magick_wand=NewMagickWand();
  bgcolor=NewPixelWand();
  PixelSetColor(bgcolor, "#0000ff");
  
  MagickSetBackgroundColor(magick_wand, bgcolor);
  MagickSetSize(magick_wand, 600, 600);
  MagickNewImage(magick_wand, 600, 600, bgcolor);
  
  drawing_wand = NewDrawingWand();
  DrawCircle(drawing_wand, 100, 100, 120, 120);

  MagickDrawImage(magick_wand, drawing_wand);
  
  //MagickConstituteImage(wand,600,600,"RGB",CharPixel,pixels);

  if (status == MagickFalse)
    ThrowWandException(magick_wand);
  /*
    Write the image then destroy it.
  */
  status=MagickWriteImages(magick_wand,"output.png",MagickTrue);
  if (status == MagickFalse)
    ThrowWandException(magick_wand);
  magick_wand=DestroyMagickWand(magick_wand);
  MagickWandTerminus();
  return(0);
}