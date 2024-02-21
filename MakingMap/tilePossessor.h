#include "tile.h"
#include "tileStrategy.h"
#include "directionStrategy.h"

#pragma once

class TilePossessor
{
protected:
    Tile* tile;
    int side = 0;
    std::unique_ptr<TileStrategy> strategy_;
    std::unique_ptr<DirectionStrategy> dirStrategy_;

public:
    virtual void update() = 0;
    virtual void draw() = 0;
    void setStrategy(std::unique_ptr<TileStrategy>&& strategy)
    {
        strategy_ = std::move(strategy);
    }
    void setDirStrategy(std::unique_ptr<DirectionStrategy>&& dirStrat)
    {
        dirStrategy_ = std::move(dirStrat);
    }
};