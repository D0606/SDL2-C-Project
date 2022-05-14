#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int SCR_WIDTH = 1024, SCR_HEIGHT = 768;

//Functions
int init(SDL_Window **parWindow, SDL_Surface **parSurface);
int loadMedia(SDL_Surface **parImage);
int closeDown(SDL_Window **parWindow, SDL_Surface **parSurface);

int main(int argc, char *argv[])
{
    //Create a window and a 2D surface for images
    
    SDL_Window *window = NULL;
    SDL_Surface *windowsSurface = NULL;
    SDL_Surface *image = NULL;


    //Begin the initialisation
    if (init(&window, &windowsSurface) != 0)
    {
        printf("Cannot initialise!");
        return 1;
    }
    else
    {
        //printf("Window after init: %s\n\rSurface after init: %s\n\r", window, windowsSurface);
        //Load the media
        if (loadMedia(&image) != 0)
        {
            printf("Cannot load media!");
        }
        else
        {
            //Blit to the surface
            SDL_BlitSurface(image, NULL, windowsSurface, NULL);
            //printf("Image: %s\n\rSurface: %s\n\r", image, windowsSurface);
        }
    }

    //Update the screen
    SDL_UpdateWindowSurface(window);

    //Wait
    SDL_Delay(3000);

    //Shutdown
    closeDown(&window, &windowsSurface);
    
    return 0;
}

int init(SDL_Window **parWindow, SDL_Surface **parSurface)
{
    //Initialise and test (SDL_Init return -1 on error)
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialise with error: %s\n\r", SDL_GetError());
        return 1;
    }
    //If no error, set up the window an test.
    else
    {
        *parWindow = SDL_CreateWindow("Attractive vs Sexy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        if (*parWindow == NULL)
        {
            printf("Could not create window with error: %s\n\r", SDL_GetError());
            return 1;
        }
        else
        {
            //Assign the window surface
            *parSurface = SDL_GetWindowSurface(*parWindow);
            //printf("Init window: %s\n\rInit Surface: %s\n\r", parWindow, parSurface);

            //Colour the surface
            //SDL_FillRect(parSurface, NULL, SDL_MapRGB(parSurface->format, 0xFF, 0xFF, 0xFF));
        }
    }

    return 0;
}

int loadMedia(SDL_Surface **parImage)
{
    //Set flag
    int success = 0;

    //Load the image
    *parImage = SDL_LoadBMP("src/Img/MattChris.bmp");
    if (*parImage == NULL)
    {
        printf("Unable to load image: %s, Error: %s\n\r", "Img/MattChris.bmp", SDL_GetError());
        success = 1;
    }
    //printf("loadMedia Image: %s\n\r", parImage);
    return success;
}

int closeDown(SDL_Window **parWindow, SDL_Surface **parSurface)
{
    //Deallocate surface
    SDL_FreeSurface(*parSurface);
    *parSurface = NULL;

    //Destroy window
    SDL_DestroyWindow(*parWindow);
    *parWindow = NULL;

    //Quit all SDL subsystems
    SDL_Quit();

    return 0;
}