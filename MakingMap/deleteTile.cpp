#include "deleteTile.h"

void DeleteTileStrategy::execute(int side, Tile*& tile)
{
    if (!flaggedTiles.empty())
    {
        Tile* flagged = flaggedTiles.front();
        flaggedTiles.pop_back();

        if (side == -1 && flagged != tile)
        {
            for (int i = 0; i < 6; i++)
            {
                if (flagged->getTile(i) != nullptr)
                    flagged->unsetTiles(i, flagged);
            }

            delete flagged;
        }
        else if (side > -1 && side < 6 && flagged->getTile(side) != nullptr)
        {
            tile = flagged->getTile(side);
            flagged->unsetTiles(side, flagged);
        }
    }
}