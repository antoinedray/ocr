
/*
   PIXEL OPERATIONS
   pixel_operations.c
   In this file we'll put all the preprocessing of the image & necessary fonctions for sdl
   */
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include "pixel_operations.h"

// Waiting for a key function 

void wait_for_keypressed(void) {
    SDL_Event             event;
    // Infinite loop, waiting for event
    for (;;) {
        // Take an event
        SDL_PollEvent( &event );
        // Switch on event type
        switch (event.type) {
            // Someon e pressed a key -> leave the function
            case SDL_KEYDOWN: return;
            default: break;
        }
        // Loop until we got the expected event
    }
}

// Init SDL function

void init_sdl(void) {
    // Init only the video part
    if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
        // If it fails, die with an error message
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    }
    // We don't really need a function for that ...
}

// Loading image from a file

SDL_Surface* load_image(char *path) {
    SDL_Surface          *img;
    // Load an image using SDL_image with format detection
    img = IMG_Load(path);
    if (!img)
        // If it fails, die with an error message
        errx(3, "can't load %s: %s", path, IMG_GetError());
    return img;
}

// Create window from image

SDL_Surface* display_image(SDL_Surface *img) {
    SDL_Surface          *screen;
    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if ( screen == NULL ) {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    /* Blit onto the screen surface */
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // wait for a key
    wait_for_keypressed();

    // return the screen for further uses
    return screen;
}

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
            if(r > 255 / 2) // Black and white Threshold
                r = 255;
            else
                r = 0;

            putpixel(img, i, j, SDL_MapRGB(img->format, r, r, r)); 
        }
    }
    return img;
}

SDL_Surface* Line_Detection(SDL_Surface* img)
{
    Uint32 pxl;
    Uint8 pxlcolor;
    img = BlackNWhite(img);
    int list_lines[img->h];
    for (int x = 0; x < img->h; x++)
        list_lines[x] = -1;
    int i = 0; //list index
    //Settle optimization after finishing line detection. int sum; //Will allow easier malloc usage
    int prev_pxl = 0; //true or false depending on if the previous pixel was black. (No letters are 1 pixel wide)
    for (int y = 0; y < img->h; y++)
    {
        for (int x = 0; x < img->w; x++)
        {
            pxl = getpixel(img, x, y);
            SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
            if (pxlcolor != 0) //current pixel is black
            {
                if(prev_pxl == 1) //is previous pixel black?
                {
                    list_lines[i] = y; //consider curr line to be a line written on if at least two pixels follow each other
                    i++;
                    break;
                }
                else
                {
                    prev_pxl = 1;
                }
            }
            else    //Move aside a pxl, and change so previous pixel (the one we're looking at currently) is white.
            {
                prev_pxl = 0;
            }
        }
    }
    *list_lines = checklines(list_lines, img->h);
}

int checklines(int l[], int nb_elts) //removes lines from list when less than 5 consecutive lines
{
    //Add second check over list_lines tk if two lines follow each other. If yes, => Line. Else noise.

    int res[sizeof(l)];
    for (int x = 0; x < nb_elts; x++)
        res[x] = -1;
    int consecutive_lines = 0;
    for (int index = 0; index < sizeof(l); index++)
    {
        if (l[index] == l[index+1] && consecutive_lines < 6)
            consecutive_lines++;
        else if (l[index] == l[index+1])
        {
            for (int x = index - 6; x < index; x++)
                res[x]= 1;
        }
        else // line is not followed by any other
        {
            if (l[index] == l[index-1]) //it's the last of a sequence (bot of letter)
                consecutive_lines++;
            else
                continue; //ignores line for res (line is noise.)
        }
    }
    return res;
}
