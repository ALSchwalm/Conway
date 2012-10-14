#include "Simulator.h"

Simulator::Simulator(SDL_Surface * s)
{
    srand(time(NULL));

    this->screen = s;
    this->rend = new Render(this);
    for (unsigned int i = 0 ; i < SCREEN_WIDTH; i++)
    {
        this->vField.push_back(*(new vector <Cell>));
        this->bUpdates.push_back( vector<bool>(SCREEN_HEIGHT, 0));
    }

    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (unsigned int j = 0; j < SCREEN_HEIGHT; j++)
        {
            int iRand = rand() % 100;

            if (iRand > 40)
            {
                vField[i].push_back(Cell(i, j, true));
            }
            else
            {
                vField[i].push_back(Cell(i, j, false)); //Does this cause problems when you exit function?
            }
        }
    }

    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (unsigned int j = 0; j < SCREEN_HEIGHT; j++)
        {
            vField[i][j].iNeighbors = getNeighbors(i, j);
        }
    }
}

int Simulator::getNeighbors(int i, int j)
{
    int iNeighbors = 0;

    for (int k = -1; k < 2; k++)
    {
        for (int h = -1; h < 2; h++)
        {
            if (i + k < SCREEN_WIDTH && j + h < SCREEN_HEIGHT && vField[i+k][j+h].bLive)
                iNeighbors++;
        }
    }
    if (vField[i][j].bLive)
        iNeighbors--;

    return iNeighbors;
}

void Simulator::updateField()
{
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            if (!vField[i][j].bLive)
            {
                if ( vField[i][j].iNeighbors == 3) bUpdates[i][j] = true;
                else bUpdates[i][j] = false;
            }
            else
            {
                if ( vField[i][j].iNeighbors < 2 || vField[i][j].iNeighbors > 3) bUpdates[i][j] = false;
                else bUpdates[i][j] = true;
            }
        }
    }

    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            if (vField[i][j].bLive != bUpdates[i][j])
            {
                if (bUpdates[i][j]) //cell has come alive
                {
                    vField[i][j].bLive = true;
                    for (int k = -1; k < 2; k++)
                    {
                        for (int h = -1; h < 2; h++)
                        {
                            if (i + k < SCREEN_WIDTH && j + h < SCREEN_HEIGHT)
                                vField[i+k][j+h].iNeighbors++;
                        }
                    }
                    vField[i][j].iNeighbors--; //A cell is not its own neighbor
                }
                else //cell has died
                {
                    vField[i][j].bLive = false;
                    for (int k = -1; k < 2; k++)
                    {
                        for (int h = -1; h < 2; h++)
                        {
                            if (i + k < SCREEN_WIDTH && j + h < SCREEN_HEIGHT)
                                vField[i+k][j+h].iNeighbors--;
                        }
                    }
                    vField[i][j].iNeighbors++; //A cell is not its own neighbor
                }
            }
        }
    }
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
