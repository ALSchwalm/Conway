#include "Render.h"

Render::Render(Simulator* s) :
	sim(s)
{
}

void Render::drawFrame()
{
    SDL_FillRect(sim->getSurface(), NULL, 0x000000);

    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (unsigned int j = 0 ; j < SCREEN_HEIGHT; j++)
        {
            if ( sim->getField()[i][j].bLive){
                SDL_Rect cell = {CELL_SIZE*i, CELL_SIZE*j, CELL_SIZE, CELL_SIZE};
                SDL_FillRect(sim->getSurface(), &cell, 0xffffff);
            }
        }
    }

    SDL_Flip(sim->getSurface());
}
