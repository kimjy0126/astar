#include "coord.h"

Coord::Coord(int row, int col) : row(row), col(col)
{
}

Coord& Coord::operator=(const Coord& c)
{
    row = c.row;
    col = c.col;
    return *this;
}

bool Coord::operator==(const Coord& c)
{
    return (row == c.row) && (col == c.col);
}
