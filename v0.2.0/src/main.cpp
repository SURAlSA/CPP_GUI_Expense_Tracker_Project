#include <iostream>
#include <SDL2/SDL.h>
#include "MainWindow.h"

int main() 
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Initializer
    SDL_Init(SDL_INIT_EVERYTHING);

    // Creates window and renderer
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // While application is running
    while (!quit) 
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) 
        {
            quit = checkForQuit(e); // check if user requests quit
            if (e.type == SDL_MOUSEBUTTONDOWN) 
            {
                mouseClicked(e);
            }
        }

        // Update the sidebar thickness for animation
        updateSideBarThickness();

        // Render the window
        renderWindow(renderer);

        // Delay to control the frame rate
        SDL_Delay(17); // approximately 60 frames per second
    }

    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
