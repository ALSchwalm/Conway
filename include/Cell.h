#ifndef CELL_H
#define CELL_H


class Cell
{
    public:
        Cell(){};
        Cell(unsigned int, unsigned int, bool);
        unsigned int iNeighbors;
        bool bLive;
        unsigned int x;
        unsigned int y;
};

#endif // CELL_H
