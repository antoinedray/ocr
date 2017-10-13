/*

  PIXEL OPERATIONS

  pixel_operations.c
  In this file we'll put all the preprocessing of the image

*/ 

# include "pixel_operations.h"
 
static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}

/***************** OUR FUNCTIONS ********************/

/*
  Grayscale & Black N White
*/

int comdiv(int w, int h)
{
    //
}

SDL_Surface* Grayscale(SDL_Surface* img)
{
	Uint32 pixl;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	float avg;
	for(int i = 0; i < img->w; i++)
	{
		for(int j = 0; j < img->h; j++)
		{
			pixl = getpixel(img, i, j);
			SDL_GetRGB(pixl, img->format, &r, &g, &b);

      /* Grayscale formula */
			avg = (r*0.3) + (g*0.59) + (b*0.11);

			putpixel(img, i, j, SDL_MapRGB(img->format, (Uint8)avg, (Uint8)avg, (Uint8)avg));	
		}
	}
	return img;
}

SDL_Surface* BlackNWhite(SDL_Surface* img)
{
    Uint32 pixl;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    for(int i = 0; i < img->w; i++)
    {
        for(int j = 0; j < img->h; j++)
        {
            pixl = getpixel(img, i, j);
            SDL_GetRGB(pixl, img->format, &r, &g, &b);

            /* Black N White */
            if(r > 255 / 2) // We compare here the variable r but could be g or b also
                r = 255;
            else
                r = 0;

            putpixel(img, i, j, SDL_MapRGB(img->format, r, r, r)); 
        }
    }
    return img;
}
