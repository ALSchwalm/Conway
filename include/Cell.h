#ifndef CELL_H
#define CELL_H


class Cell
{
    public:
        Cell(unsigned int, unsigned int);
        unsigned int x;
        unsigned int y;
        bool bLive;
};

#endif // CELL_H
