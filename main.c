#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int SCR_WIDTH = 1024, SCR_HEIGHT = 768;

//Functions
bool init(SDL_Window **parWindow, SDL_Surface **parSurface);
bool loadMedia(SDL_Surface **parImage);
bool closeDown(SDL_Window **parWindow, SDL_Surface **parSurface);

int main(int argc, char *argv[])
{
    //Variables    
    SDL_Window *window = NULL;
    SDL_Surface *windowsSurface = NULL;
    SDL_Surface *image = NULL;
    SDL_Event ev;
    bool quit = false;


    //Begin the initialisation by calling and checking init() function
    if (!init(&window, &windowsSurface))
    {
        printf("Cannot initialise!");
        return 1;
    }
    else
    {
        //Load the media byy calling and checking loadMedia() function
        if (!loadMedia(&image))
        {
            printf("Cannot load media!");
        }
        else
        {
            //Main loop
            while (!quit)
            {
                //Handling events in queue
                while (SDL_PollEvent(&ev) != 0)
                {
                    //User is requesting to quit so change flag to exit loop
                    if (ev.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
            
                //Blit to the surface
                SDL_BlitSurface(image, NULL, windowsSurface, NULL);

                //Update the screen
                SDL_UpdateWindowSurface(window);

            }
        }
    }

    //Wait
    //SDL_Delay(3000);

    //Shutdown
    closeDown(&window, &windowsSurface);
    
    return 0;
}


bool init(SDL_Window **parWindow, SDL_Surface **parSurface)
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
            return false;
        }
        else
        {
            //Assign the window surface
            *parSurface = SDL_GetWindowSurface(*parWindow);

            //Colour the surface
            //SDL_FillRect(parSurface, NULL, SDL_MapRGB(parSurface->format, 0xFF, 0xFF, 0xFF));
        }
    }

    return true;
}

bool loadMedia(SDL_Surface **parImage)
{
    //Set flag
    bool success = true;

    //Load the image
    *parImage = SDL_LoadBMP("src/Img/MattChris.bmp");
    if (*parImage == NULL)
    {
        printf("Unable to load image: %s, Error: %s\n\r", "Img/MattChris.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

bool closeDown(SDL_Window **parWindow, SDL_Surface **parSurface)
{
    //Deallocate surface
    SDL_FreeSurface(*parSurface);
    *parSurface = NULL;

    //Destroy window
    SDL_DestroyWindow(*parWindow);
    *parWindow = NULL;

    //Quit all SDL subsystems
    SDL_Quit();

    return true;
}