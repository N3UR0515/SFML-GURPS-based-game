#include "tileStrategy.h"
#include <iostream>

#pragma once

class DeleteTileStrategy : public TileStrategy
{
private:
    Tile* connectTo;
    std::vector<Tile*> toDelete;
public:
    void execute(int side, Tile*& tile) override;
    void setTileToConnect(Tile* toSet);
    bool flagUnconnected(Tile* tile);
    void deleteUnconnected(Tile* tile);
};