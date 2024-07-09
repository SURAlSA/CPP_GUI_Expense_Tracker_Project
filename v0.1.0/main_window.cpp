#include <iostream>
#include <SDL2/SDL.h>
// functions
bool isPointInsideRect(int x, int y, SDL_Rect rect); // function checks if cursor inside Rectangle
void updateSideBarThickness(); // updates side bar

// screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// bar thicknesses
const int SIDE_BAR_OPEN_THICKNESS = 60; // default state + thickness of the side bar being open
const int SIDE_BAR_CLOSED_THICKNESS = 20; // thickness when closed
bool IS_SIDE_BAR_OPEN = true; // default state is true, change this to false if bar is closed
const int TOP_BAR_THICKNESS = 20;

// hitbox cubes for icons on the app
const int hitbox_width_or_height = 40;

// top left bar
const int TOP_LEFT_BAR_HEIGHT = 70;
const int TOP_LEFT_BAR_WIDTH = 60; 

// animation constants
const int ANIMATION_STEP = 2; // step size for the animation
int currentSideBarThickness = SIDE_BAR_OPEN_THICKNESS; // current thickness of the side bar

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
            // User requests quit
            if (e.type == SDL_QUIT) 
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) 
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Rect toggleButton = { 10, 20, hitbox_width_or_height, hitbox_width_or_height };
                if (isPointInsideRect(x, y, toggleButton)) 
                {
                    IS_SIDE_BAR_OPEN = !IS_SIDE_BAR_OPEN; // Toggle sidebar state
                }
            }
        }

        // Update the sidebar thickness for animation
        updateSideBarThickness();

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);

        // Render black bars
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color

        // Top bar
        SDL_Rect topBar = { currentSideBarThickness, 0, SCREEN_WIDTH - currentSideBarThickness, TOP_BAR_THICKNESS };
        SDL_RenderFillRect(renderer, &topBar);

        // Left bar
        SDL_Rect leftBar = { 0, TOP_LEFT_BAR_HEIGHT, currentSideBarThickness, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &leftBar);

        // Top left bar note: always display this so that the left bar can be opened and closed.
        SDL_Rect topLeftBar = {0, 0, TOP_LEFT_BAR_WIDTH, TOP_LEFT_BAR_HEIGHT};
        SDL_RenderFillRect(renderer, &topLeftBar);

        // Render top-left icon (always visible)
        int hitboxLocX = 10;
        int hitboxLocY = 20;
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Grey hitbox for top-left icon
        SDL_Rect toggleButton = { hitboxLocX, hitboxLocY, hitbox_width_or_height, hitbox_width_or_height};
        SDL_RenderFillRect(renderer, &toggleButton);

        if (currentSideBarThickness > SIDE_BAR_CLOSED_THICKNESS) 
        {
            // Render remaining hitboxes for icons only if the sidebar is open
            hitboxLocY += 60;
            for (int i = 1; i < 9; i++) 
            {
                int offsetX = (SIDE_BAR_OPEN_THICKNESS - currentSideBarThickness);
                SDL_Rect hitboxRect = { hitboxLocX - offsetX, hitboxLocY, hitbox_width_or_height, hitbox_width_or_height };
                SDL_RenderFillRect(renderer, &hitboxRect);
                hitboxLocY += 60;
            }
        }

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay to control the frame rate
        SDL_Delay(16); // approximately 60 frames per second
    }

    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}

bool isPointInsideRect(int x, int y, SDL_Rect rect) 
{
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

void updateSideBarThickness() 
{
    if (IS_SIDE_BAR_OPEN && currentSideBarThickness < SIDE_BAR_OPEN_THICKNESS) 
    {
        currentSideBarThickness += ANIMATION_STEP;
        if (currentSideBarThickness > SIDE_BAR_OPEN_THICKNESS) 
        {
            currentSideBarThickness = SIDE_BAR_OPEN_THICKNESS;
        }
    } 
    else if (!IS_SIDE_BAR_OPEN && currentSideBarThickness > SIDE_BAR_CLOSED_THICKNESS) 
    {
        currentSideBarThickness -= ANIMATION_STEP;
        if (currentSideBarThickness < SIDE_BAR_CLOSED_THICKNESS) 
        {
            currentSideBarThickness = SIDE_BAR_CLOSED_THICKNESS;
        }
    }
}
