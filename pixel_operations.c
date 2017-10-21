
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

SDL_Surface* BlackNWhite(SDL_Surface* img) // plz do not delete aur shange zis plzplz
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
            if(r > 200) // Black and white Threshold
                r = 255;
            else
                r = 0;

            putpixel(img, i, j, SDL_MapRGB(img->format, r, r, r)); 
        }
    }
    return img;
}

// Otzu method
struct BIN_Matrix *Otzu(SDL_Surface* img)
{
    Uint32 pixl;
    Uint8 r;
    Uint8 g;
    Uint8 b;

    int sigsq;
    int N = img->h * img->w;
    int threshold=0, var_max=0, sum=0, sumB=0, q1=0, q2=0, m1=0, m2 = 0;
    int max_intensity = 255;
    int histogram[255];

    for(int i=0;i<=max_intensity;i++)
    {
        histogram[i] = 0;
    }

    for(int i=0;i<img->w;i++)
    {
        for(int j=0;j<img->h;j++)
        {
            pixl = getpixel(img, i, j);
            SDL_GetRGB(pixl, img->format, &r, &g, &b);

            histogram[(int)r]++;
        }
    }

    // auxiliary value for computing μ2
    for(int i=0; i<max_intensity;i++)
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

    int height = img->h;
    int width = img->w;
    int *mat = calloc(width*height, sizeof(int));
    for(int h = 0; height > h; h++)
    {
        for (int w = 0; width > w; w++)
        {
            SDL_GetRGB(getpixel(img,w,h),img->format,&r,&g,&b);
            if (r <= threshold)
                mat[w + h * width] = 0;
            else
                mat[w + h * width] = 1;
        }
    }
    struct BIN_Matrix *bin = malloc(sizeof(struct BIN_Matrix));
    bin->mat = mat;
    bin->lines = height;
    bin->cols = width;
    return bin;
}

SDL_Surface* Line_Detection(SDL_Surface* img)
{
    Uint32 pxl;
    Uint8 pxlcolor;
    img = BlackNWhite(img);
    int list_lines[img->h];             //img->BnW(img) + init list line
    for (int x = 0; x < img->h; x++)
        list_lines[x] = -1;
    int i = 0; //list index
    int prev_pxl = 0; //true or false depending on if the previous pixel was black


    for (int y = 0; y < img->h; y++)
    {
        for (int x = 0; x < img->w; x++)
        {
            pxl = getpixel(img, x, y);
            SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
            if (pxlcolor == 0)
            {
                if(prev_pxl == 1) //is previous pixel black?
                {
                    list_lines[y] = 1; //consider curr line to be a line written on if at least two pixels follow each other
                    i++;
                    break;
                }
                else
                {
                    prev_pxl = 1;
                }
            }
            else
            {
                prev_pxl = 0;
            }
        }
    }
    int list[img->h];
    checklines(list_lines, img->h, list);
    return(DisplayLines(img, list, img->h));
}



int checklines(int l[], int nb_elts, int res[]) //removes lines from list when less than 5 consecutive lines
{
    for (int x = 0; x < nb_elts; x++)
        res[x] = -1;
    int consecutive_lines = 0;
    int top = 0;
    int bot = 0;
    for (int index = 0; index < nb_elts; index++)
    {
        if (l[index] == 1)
        {
            if (l[index] == l[index+1] && top == 0)
            {
                top = index;
                consecutive_lines++;
            }
            else if (l[index] == l[index+1] && top != 0) //top already found, continue onwards to find bot
            { 
                consecutive_lines++;
                continue;
            }
            else // line is not followed by any other
            {
                if (l[index] == l[index-1] && bot == 0) //it's the last of a sequence (bot of letter)
                {
                    bot = index;
                    consecutive_lines++;
                }
                else if (l[index] == l[index-1] && bot != 0) //it's the last of a sequence (bot of letter)
                {
                    consecutive_lines++;
                    continue;
                }
                else
                {
                    consecutive_lines = 0;
                    continue; //ignores line for res (line is noise.)
                }
            }

            if (consecutive_lines >= 6)
            {
                res[top] = 1;
                res[bot] = 2;
                top = 0;
                bot = 0;
                consecutive_lines = 0;
            }
        }
    }
    return *res;
}

int char_detection(SDL_Surface* img, int list_lines[] /*FIXME*/)
{
    img = BlackNWhite(img); 
    int height = img->h;
    int width = img->w;
    int list[width];
    int column_list_index = 0;
    int white_column = 0; //char has ended only if white_column >= 2
    int white = 1; //line might be white. Is changed upon black pxl encounter
    int startchar = 0; //set to 1 if 2 consecutive vertical pxl are found
    int endchar = 0; //set to 1 if whole white column is found
    for (int i = 0; i < height; i++) //Goes through the line list
    {
        if (list_lines[i] == 1) //We found the top of a char line
        {
            for (int x = 0; x < img->w; x++) //goes through the whole char line
                // Deserves a FIXME to implement not going past last char 
                // (aka having white columns at the end of text)
            {
                for (int y = 0; list_lines[i + y] != 2; y++) //goes from the top of char line to its bottom
                    // Since bot of a char line is 2 in the line list we're going through.
                {
                    white = 1; //This might be a white column.
                    if (getpixel(img,x,y) == 0 && //if pxl is black
                            getpixel(img,x,y) == getpixel(img, x, y+1))//and next vertical pxl is black too
                    {
                        white = 0; //This isn't a white column (aka not end of a char)
                        if (startchar == 0) //if startchar isnt registered
                        {
                            if (getpixel(img, x-1, y) == getpixel(img, x, y)) //should never happen
                                // It would mean there was a black pxl left of ours, 
                                // and that said black pxl isn't startchar yet. Abnormal.
                            {
                                list[column_list_index] = x-1; //if a pxl was black before, it should be startchar
                                startchar = 1;
                                column_list_index++;
                                endchar = 0; //if startchar is found, it means we have a new char to check
                                    //hence the need to reset endchar in order to find its new value
                            }
                            else // current pxl is leftmost pxl of char
                            {
                                list[column_list_index] = x;
                                startchar = 1;
                                column_list_index++;
                                endchar = 0;                                                                                                //FIXME, no need to go through whole column after setting startchar
                                                                                                                                            //no char is 1 pxl wide. nor 2 actually, so next column can also be
                                                                                                                                            //skipped (theoritically)
                            }
                        }
                        else //startchar is found. aka we're looking for a final end char
                        {
                            if (endchar == 0) //we have no endchar yet, this one will do
                            {
                                if (getpixel(img, x+1, y) != getpixel(img, x, y)) //iff right pxl is white
                                {
                                    endchar = 1;
                                    list[column_list_index] = x;
                                    // Since there might be another further endcha
                                    // startchar is still 1 until we're sure this is the final one
                                }
                            }
                            else //endchar has been found
                            {
                                if (x >= list[column_list_index-1]) //if x of this endchar is bigger than previous'
                                                                    // (this pxl is left of our previous endchar)
                                                                    // or if it's equal (in that case, this pxl is lower
                                                                    // than our previous endchar, which is a
                                                                    // valid cause for being replaced too)
                                {
                                    column_list_index--; //go back to previous endchar and change it
                                    list[column_list_index] = x;
                                }
                            }
                            column_list_index++;
                        }

                    }
                    /*
                       else (pxl is white)
                       {
                       white indicator doesn't change : whole column might be white, in which case default value of
                       " white = 1 " is good. If the column isn't white, it should already have been changed earlier
                       }
                    */
                }
                if (white == 1) //if the whole column is white (exiting the for with lines[i+y])
                    white_column++;
                else
                    white_column = 0; //consecutive white columns is reset
                if (white_column >= 2)
                {
                    startchar = 0;
                    //Scenarios at this point :
                    // - if startchar was 1 and we found two consecutive white columns, that startchar was noise/a bug
                    // - if startchar is not found... well, still haven't met a black pxl, so resetting it doesn't matter.
                    // - if we're in the middle of a char, there's no way we'll have two white pxl columns
                    // - if startchar = 1, and endchar = 1, and we reach here, it means we found two white columns after a
                    //          last pxl. Hence, this pxl was the true endchar, and we start looking for the next char
                }
            }
            list[column_list_index] = -1; //we reached end of text line, signaling it to the list.
        }
    }
    return *list;
}

SDL_Surface* DisplayLines (SDL_Surface* img, int y[], int nb_elts)
{
    for (int i = 0; i < nb_elts; i++)
    {
        if (y[i] == 2 || y[i] == 1)
        {
            for (int x = 0; x < img->w; x++)
                putpixel(img, x, i, SDL_MapRGB(img->format, 255, 0, 0));
        }
    }
    return img;
}


//BINARIZATION

struct BIN_Matrix *IMGtoBIN(SDL_Surface* img)
{   
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int height = img->h;
    int width = img->w;
    int *mat = calloc(width*height, sizeof(int));
    for(int h = 0; height > h; h++)
    {
        for (int w = 0; width > w; w++)
        {
            SDL_GetRGB(getpixel(img,w,h),img->format,&r,&g,&b);
            if (r ==255)
                mat[w + h * width] = 0;
            else
                mat[w + h * width] = 1;
        }
    }
    struct BIN_Matrix *bin = malloc(sizeof(struct BIN_Matrix));
    bin->mat = mat;
    bin->lines = height;
    bin->cols = width;
    return bin;
}
