#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "SDL/SDL.h"
#include "Render.h"
#include "Global.h"
#include <vector>
#include <time.h>

class Render;
using namespace std;

class Simulator
{
    public:
        Simulator(SDL_Surface * s);
        void start();

        SDL_Surface * getSurface(){return screen;}
        vector <vector <bool> > & getField(){return bField;}

    private:
        vector <vector <bool> >bField;
        SDL_Surface * screen;
        Render * rend;
        SDL_Event event;
};

#endif // SIMULATOR_H
