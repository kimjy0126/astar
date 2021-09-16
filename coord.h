#ifndef __COORD_H
#define __COORD_H

class Coord {
public:
    int row;
    int col;

    Coord(int row = -1, int col = -1);

    Coord& operator=(const Coord& c);
    bool operator==(const Coord& c);
};

#endif
