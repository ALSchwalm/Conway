#include "Simulator.h"

Simulator::Simulator(SDL_Surface * s)
{
    srand(time(NULL)); //still worst random ever

    this->screen = s;
    this->rend = new Render(this);
    this->bPaused = false;
    this->bRunning = true;
    this->bMousePressed = false;

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
                vField[i].push_back(Cell(i, j, false));
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

void Simulator::addRandom()
{
    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (unsigned int j = 0; j < SCREEN_HEIGHT; j++)
        {
            int iRand = rand() % 100;

            if (iRand > 80)
                liveCell(i*CELL_SIZE, j*CELL_SIZE);
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
    if (vField[i][j].bLive) //cell is not its own neighbor
        iNeighbors--;

    return iNeighbors;
}

void Simulator::updateField()
{
    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (unsigned int j = 0; j < SCREEN_HEIGHT; j++)
        {
            if (!vField[i][j].bLive)
            {
                if ( vField[i][j].iNeighbors == 3) bUpdates[i][j] = true;  //2
                else bUpdates[i][j] = false;
            }
            else
            {
                if ( vField[i][j].iNeighbors < 2 || vField[i][j].iNeighbors > 3) bUpdates[i][j] = false; // <1 > 3 give maze
                else bUpdates[i][j] = true;
            }
        }
    }

    for (unsigned int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (unsigned int j = 0; j < SCREEN_HEIGHT; j++)
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

void Simulator::liveCell( int x, int y)
{
    int iTempX = (x - (x % CELL_SIZE))/CELL_SIZE;
    int iTempY = (y - (y % CELL_SIZE))/CELL_SIZE;

    if (!vField[iTempX][iTempY].bLive)
    {
        vField[iTempX][iTempY].bLive = true;

        for (int k = -1; k < 2; k++)
        {
            for (int h = -1; h < 2; h++)
            {
                if (iTempX + k < SCREEN_WIDTH && iTempY + h < SCREEN_HEIGHT)
                    vField[iTempX+k][iTempY+h].iNeighbors++;
            }
        }
        vField[iTempX][iTempY].iNeighbors--; //A cell is not its own neighbor
    }
}


void Simulator::handleEvents()
{
    int mouse_x, mouse_y;

    while( SDL_PollEvent( &event ) )
    {
        switch (event.type)
        {
            case SDL_QUIT:
                bRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        bRunning = false;
                        break;
                    case SDLK_SPACE:
                        bPaused = !bPaused;
                        break;
                    case SDLK_r:
                        addRandom();
                        break;
                    case SDLK_RIGHT:
                        updateField();
                        break;
                    default:
                        continue;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                bMousePressed = true;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                liveCell(mouse_x, mouse_y);
                break;

            case SDL_MOUSEBUTTONUP:
                bMousePressed = false;
                break;

            case SDL_MOUSEMOTION:
                if (bMousePressed)
                {
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    liveCell(mouse_x, mouse_y);
                    liveCell(mouse_x + CELL_SIZE, mouse_y);
                }
                break;
            default:
                break;
        }
    }
}

void Simulator::start()
{

    Uint32 waittime = 1000.0f/FPS;
    Uint32 framestarttime = 0;
    Sint32 delaytime;

    while(bRunning)
    {
        handleEvents();

        if(!bPaused) updateField();
        rend->drawFrame();

        delaytime = waittime - (SDL_GetTicks() - framestarttime);
        if  (delaytime > 0)
            SDL_Delay((Uint32)delaytime);
        framestarttime = SDL_GetTicks();
    }

}
