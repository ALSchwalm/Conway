#include "Render.h"

Render::Render(Simulator * s)
{
    this->sim = s;
}

void Render::drawFrame()
{
    SDL_FillRect(sim->getSurface(), NULL, 0x000000);

    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (unsigned int j = 0 ; j < SCREEN_HEIGHT; j++)
        {
            if ( sim->getField()[i][j]){
                SDL_Rect cell = {0+i, 0+j, 1+1, 1+1};
                SDL_FillRect(sim->getSurface(), &cell, 0xffffff);
            }

        }
    }

    SDL_Flip(sim->getSurface());
}
