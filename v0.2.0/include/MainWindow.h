#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SDL2/SDL.h>

// screen dimensions
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

// bar thicknesses
extern const int SIDE_BAR_OPEN_THICKNESS;
extern const int SIDE_BAR_CLOSED_THICKNESS;
extern bool IS_SIDE_BAR_OPEN;
extern const int TOP_BAR_THICKNESS;

// hitbox cubes for icons on the app
extern const int hitbox_width_or_height;

// top left bar
extern const int TOP_LEFT_BAR_HEIGHT;
extern const int TOP_LEFT_BAR_WIDTH;

// animation constants
extern const int ANIMATION_STEP;
extern int currentSideBarThickness;

// Functions
void renderWindow(SDL_Renderer* renderer);
void mouseClicked(SDL_Event e);
bool checkForQuit(SDL_Event e);
void updateSideBarThickness();

#endif
