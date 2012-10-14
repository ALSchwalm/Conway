#include "SDL/SDL.h"
#include "Simulator.h"
#include "Global.h"

#include <iostream>


int main(int argc, char* args[])
{

    SDL_Surface * screen;

    SDL_Init (SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode (CELL_SIZE*SCREEN_WIDTH, CELL_SIZE*SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Game of Live v0.2", NULL);

    Simulator sim(screen);
    sim.start();

    return 0;
}
