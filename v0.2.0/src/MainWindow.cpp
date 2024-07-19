#include "MainWindow.h"
#include "Utils.h"
#include <iostream>

// screen dimensions
int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 900;

// bar thicknesses
const int SIDE_BAR_OPEN_THICKNESS = 60;
const int SIDE_BAR_CLOSED_THICKNESS = 20;
bool IS_SIDE_BAR_OPEN = true;
const int TOP_BAR_THICKNESS = 20;

// hitbox cubes for icons on the app
const int hitbox_width_or_height = 40;

// top left bar
const int TOP_LEFT_BAR_HEIGHT = 70;
const int TOP_LEFT_BAR_WIDTH = 60;

// animation constants
const int ANIMATION_STEP = 2;
int currentSideBarThickness = SIDE_BAR_OPEN_THICKNESS;

void renderWindow(SDL_Renderer* renderer) {
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

    if (currentSideBarThickness > SIDE_BAR_CLOSED_THICKNESS) {
        // Render remaining hitboxes for icons only if the sidebar is open
        hitboxLocY += 60;
        for (int i = 1; i < 9; i++) {
            int offsetX = (SIDE_BAR_OPEN_THICKNESS - currentSideBarThickness);
            SDL_Rect hitboxRect = { hitboxLocX - offsetX, hitboxLocY, hitbox_width_or_height, hitbox_width_or_height };
            SDL_RenderFillRect(renderer, &hitboxRect);
            hitboxLocY += 60;
        }
    }

    // Update screen
    SDL_RenderPresent(renderer);
}

void mouseClicked(SDL_Event e) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    // button hitboxes
    SDL_Rect toggleButton = { 10, 20, hitbox_width_or_height, hitbox_width_or_height };
    SDL_Rect addToBalance = {10, 80, hitbox_width_or_height, hitbox_width_or_height};
    SDL_Rect removeFromBalance = {10, 140, hitbox_width_or_height, hitbox_width_or_height };
    SDL_Rect viewMonthlyReport {10, 200, hitbox_width_or_height, hitbox_width_or_height};
    SDL_Rect changeCurrency {10, 260, hitbox_width_or_height, hitbox_width_or_height};
    SDL_Rect changeResolution = {10, 320, hitbox_width_or_height, hitbox_width_or_height};
    SDL_Rect printToPDF = {10, 380, hitbox_width_or_height, hitbox_width_or_height};
    SDL_Rect resetAppData = {10, 440, hitbox_width_or_height, hitbox_width_or_height};
    SDL_Rect quitApp = {10, 500, hitbox_width_or_height, hitbox_width_or_height};

    if (isPointInsideRect(x, y, toggleButton)) {
        IS_SIDE_BAR_OPEN = !IS_SIDE_BAR_OPEN; // Toggle sidebar state
    }
    else if (isPointInsideRect(x, y, addToBalance)) {
        std::cout << "testing addToBalance";
    }
}

bool checkForQuit(SDL_Event e) {
    // User requests quit
    if (e.type == SDL_QUIT) {
        return true;
    }
    return false;
}

void updateSideBarThickness() {
    if (IS_SIDE_BAR_OPEN && currentSideBarThickness < SIDE_BAR_OPEN_THICKNESS) {
        currentSideBarThickness += ANIMATION_STEP;
        if (currentSideBarThickness > SIDE_BAR_OPEN_THICKNESS) {
            currentSideBarThickness = SIDE_BAR_OPEN_THICKNESS;
        }
    } 
    else if (!IS_SIDE_BAR_OPEN && currentSideBarThickness > SIDE_BAR_CLOSED_THICKNESS) {
        currentSideBarThickness -= ANIMATION_STEP;
        if (currentSideBarThickness < SIDE_BAR_CLOSED_THICKNESS) {
            currentSideBarThickness = SIDE_BAR_CLOSED_THICKNESS;
        }
    }
}
