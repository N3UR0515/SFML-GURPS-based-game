#include "tileStrategy.h"

#pragma once

class MoveTileStrategy : public TileStrategy
{
public:
    void execute(int side, Tile*& tile) override;
};