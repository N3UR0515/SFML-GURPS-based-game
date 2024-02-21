#include "tileStrategy.h"
#pragma once

class SingleTileDrawingImplementation : public DrawingImplementation
{
public:
    void drawTiles(std::vector<Tile*> flaggedTiles) override;
};