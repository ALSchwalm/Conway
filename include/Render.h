#ifndef RENDER_H
#define RENDER_H

#include "SDL/SDL.h"
#include "Simulator.h"

class Simulator;

class Render
{
    public:
        Render();
        Render(Simulator *);
        void drawFrame();

    private:
        Simulator * sim;
};

#endif // RENDER_H
