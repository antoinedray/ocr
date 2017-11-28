/*
 * PIXEL OPERATIONS
 * file: pixel_operations.c
 * description: In this file we'll put all the preprocessing of the image
 * & necessary fonctions for sdl
 */

#include"preproc.h"

// Grayscale
SDL_Surface* grayscale(SDL_Surface* img) {
  Uint32 pixl;
  Uint8 r, g, b;
  float avg;
  for(int i = 0; i < img->w; i++) {
    for(int j = 0; j < img->h; j++) {
      pixl = getpixel(img, i, j);
      SDL_GetRGB(pixl, img->format, &r, &g, &b);

      /* Grayscale formula */
      avg = (r*0.3) + (g*0.59) + (b*0.11);
      r = (Uint8)avg;

      putpixel(img, i, j, SDL_MapRGB(img->format, r, r, r));
    }
  }
  return img;
}

// Constrast function based on the Histogram Equalisation
SDL_Surface* contrast(SDL_Surface* img) {
  Uint32 pixl;
  Uint8 r, g, b;

  int height = img->h;
  int width = img->w;
  int sum = 0;
  int max_intensity = 255;
  int histogram[256];
  int lut[256];

  for(int i = 0; i <= max_intensity; i++)
    histogram[i] = 0;

  // We build the histogram
  for(int i = 0; i < img->w; i++) {
    for(int j = 0; j < img->h; j++) {
      pixl = getpixel(img, i, j);
      SDL_GetRGB(pixl, img->format, &r, &g, &b);

      histogram[(int)r]++;
    }
  }

  // build a LUT containing scale factor
  for (int i = 0; i <= max_intensity; i++)
  {
    sum += histogram[i];
    lut[i] = sum * max_intensity / (height * width);
  }

  // transform image using sum histogram as a LUT
  // We apply the changes
   for(int h = 0; height > h; h++) {
    for (int w = 0; width > w; w++) {
      SDL_GetRGB(getpixel(img,w,h),img->format,&r,&g,&b);

      putpixel(img, w, h, SDL_MapRGB(img->format, lut[r], lut[r], lut[r]));
    }
  }
  return img;
}

SDL_Surface* split(SDL_Surface* img) {
  // We cut in 4
  SDL_Surface *tmp[4];
  for(int p = 0; p < 4; p++)
    tmp[p] = malloc(sizeof(SDL_Surface*));
  SDL_Rect crop;
  int w = img->w;
  int h = img->h;
  int k = 0;

  crop.w = img->w/2;
  crop.h = img->h/2;

  for(int i = 0; i <= w/2+1; i += w/2+1) {
    for(int j = 0; j <= h/2+1; j += h/2+1) {
        crop.x = i;
        crop.y = j;
        SDL_BlitSurface(img, &crop, tmp[k], NULL);
        tmp[k] = otzu(tmp[k]);
        SDL_BlitSurface((tmp[k]), NULL, img, &crop);
	printf("In da loop");
	k++;
    }
  }
  printf("here");
  return img;
}

// Otzu method for Black and White
SDL_Surface* otzu(SDL_Surface* img) {
  Uint32 pixl;
  Uint8 r, g, b;

  int sigsq;
  int N = img->h * img->w;
  int threshold = 0, var_max= 0, sum= 0, sumB= 0, q1= 0, q2= 0, m1= 0, m2 = 0;
  int max_intensity = 255;
  int histogram[256];

  for(int i = 0; i <= max_intensity; i++)
    histogram[i] = 0;

  // We build the histogram
  for(int i=0;i<img->w;i++) {
    for(int j=0;j<img->h;j++) {
      pixl = getpixel(img, i, j);
      SDL_GetRGB(pixl, img->format, &r, &g, &b);

      histogram[(int)r]++;
    }
  }

  // auxiliary value for computing μ2
  for(int i=0; i<=max_intensity;i++)
    sum += i * histogram[i];

  // update qi(t)
  for(int t=0;t<=max_intensity;t++)
  {
    q1 += histogram[t];
    q2 = N - q1;

    sumB += t * histogram[t];

    if (q1 != 0)
      m1 = sumB / q1;
    if (q2 != 0)
      m2 = (sum - sumB) / q2;

    sigsq = q1 * q2 * (m1 - m2) * (m1 - m2);

    if(sigsq > var_max)
    {
      threshold = t;
      var_max = sigsq;
    }
  }

  // We apply the changes
  int height = img->h;
  int width = img->w;
  for(int h = 0; height > h; h++)
  {
    for (int w = 0; width > w; w++)
    {
      SDL_GetRGB(getpixel(img,w,h),img->format,&r,&g,&b);
      if (r <= threshold)
        putpixel(img, w, h, SDL_MapRGB(img->format, 0, 0, 0));
      else
        putpixel(img, w, h, SDL_MapRGB(img->format, 255, 255, 255));
    }
  }
  return img;
}
