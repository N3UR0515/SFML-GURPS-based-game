#include "tileStrategy.h"

#pragma once
class DoNothingTile : public TileStrategy
{
public:
    void execute(int side, Tile*& tile) override;
};