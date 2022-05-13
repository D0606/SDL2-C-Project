#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int SCR_WIDTH = 800, SCR_HEIGHT = 600;

int main(int argc, char *argv[])
{
    //Create a window and a 2D surface for images
    
    SDL_Window *window = NULL;
    SDL_Surface *windowsSurface = NULL;

    //Initialise and test (SDL_Init return -1 on error)
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialise with error: %s", SDL_GetError());
        printf("\n\r");
        return 1;
    }
    //If no error, set up the window an test.
    else
    {
        window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == NULL)
        {
            printf("Could not create window with error: %s", SDL_GetError());
            printf("\n\r");
            return 1;
        }
        else
        {
            //Assign the window surface
            windowsSurface = SDL_GetWindowSurface(window);

            //Colour the surface
            SDL_FillRect(windowsSurface, NULL, SDL_MapRGB(windowsSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the window surface
            SDL_UpdateWindowSurface(window);

            //Wait for a while
            SDL_Delay(3000);
        }
    }

    //Destroy the window and close all SDL subsystems
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}