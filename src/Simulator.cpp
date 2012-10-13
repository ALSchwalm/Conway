#include "Simulator.h"

Simulator::Simulator(SDL_Surface * s)
{
    this->screen = s;
    this->rend = new Render(this);
    for (unsigned int i = 0 ; i < SCREEN_WIDTH; i++)
    {
        this->bField.push_back(*(new vector <bool>(SCREEN_HEIGHT, false)));
    }

    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (unsigned int j = 0; j < SCREEN_HEIGHT; j++)
        {
            this->bField[i][j] = (rand() % 100) > 50 ? true : false;
        }
    }

}

void Simulator::start()
{
    srand(time(NULL));
    Uint32 startclock;
    Uint32 currentFPS = 0;
    Uint32 deltaclock = 0;

    Uint32 waittime = 1000.0f/FPS;
    Uint32 framestarttime = 0;
    Sint32 delaytime;

    while(true)
    {
        startclock = SDL_GetTicks();
        while( SDL_PollEvent( &event ) ){}
        rend->drawFrame();

        delaytime = waittime - (SDL_GetTicks() - framestarttime);
        if  (delaytime > 0)
            SDL_Delay((Uint32)delaytime);
        framestarttime = SDL_GetTicks();

        deltaclock = SDL_GetTicks() - startclock;

        if (deltaclock !=  0 )
        {
            currentFPS = 1000/deltaclock;
        }
    }

}
