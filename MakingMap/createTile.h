#include "tileStrategy.h"

#pragma once

class CreateTileStrategy : public TileStrategy
{
public:
    void execute(int side, Tile*& tile) override;
};