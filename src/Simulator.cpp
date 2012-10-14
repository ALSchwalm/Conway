#include "Simulator.h"

Simulator::Simulator(SDL_Surface * s)
{
    srand(time(NULL));

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
            this->bField[i][j] = (rand() % 100) > 20 ? true : false;
        }
    }
}

void Simulator::updateField()
{
    vector <vector <bool> > bNewField(bField);

    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            int iNeighbors = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < SCREEN_WIDTH && j + h < SCREEN_HEIGHT && bField[i+k][j+h])
                        iNeighbors++;
                }
            }
            if (bField[i][j])
                iNeighbors--;

            if (!bField[i][j])
            {
                if ( iNeighbors == 3) bNewField[i][j] = true;
            }
            else
            {
                if ( iNeighbors < 2 || iNeighbors > 3) bNewField[i][j] = false;
            }
        }
    }
    bField = bNewField;
}


void Simulator::start()
{


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

        updateField();
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
