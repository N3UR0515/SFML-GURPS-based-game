#include "tileStrategy.h"
#include <iostream>

#pragma once

class DeleteTileStrategy : public TileStrategy
{
public:
    void execute(int side, Tile*& tile) override;
};