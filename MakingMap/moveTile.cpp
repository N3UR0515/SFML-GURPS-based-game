#include "moveTile.h"

void MoveTileStrategy::execute(int side, Tile*& tile)
{
    Tile* next = tile->getTile(side);
    if (next != nullptr)
    {
        tile = next;
    }
}