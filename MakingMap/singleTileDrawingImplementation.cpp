#include "singleTileDrawingImplementation.h"

void SingleTileDrawingImplementation::drawTiles(std::vector<Tile*> flaggedTiles)
{
    for (const auto& tile : flaggedTiles)
    {
        if (tile != nullptr)
        {
            tile->drawSingleTile();
            for (int i = 0; i < 6; i++)
            {
                if (tile->getTile(i) == nullptr)
                {
                    tile->drawBorder(i);
                }
            }
        }
    }
}