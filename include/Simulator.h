#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "SDL/SDL.h"
#include "Render.h"
#include "Global.h"
#include "Cell.h"
#include <vector>
#include <time.h>
#include <iostream>

class Render;
using namespace std;

class Simulator
{
    public:
        Simulator(SDL_Surface * s);
        void start();
        void updateField();
        void handleEvents();
        SDL_Surface * getSurface(){return screen;}

        vector <vector <Cell> > & getField(){return vField;}

    private:
        int getNeighbors(int, int);
        void addRandom();

        vector <vector <bool> >bUpdates;
        vector <vector <Cell> >vField;

        void liveCell( int, int);
        bool bMousePressed;
        bool bPaused;
        bool bRunning;

        SDL_Surface * screen;
        Render * rend;
        SDL_Event event;
};

#endif // SIMULATOR_H
