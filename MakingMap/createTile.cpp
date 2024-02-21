#include "createTile.h"

void CreateTileStrategy::execute(int side, Tile*& tile)
{
    if (!flaggedTiles.empty())
    {
        Tile* flagged = flaggedTiles.front();
        if (side > -1 && side < 6)
        {
            int a = 0;
            flagged->createNewTile(side, a);
            tile = flagged->getTile(side);
        }
        flaggedTiles.pop_back();

    }

}