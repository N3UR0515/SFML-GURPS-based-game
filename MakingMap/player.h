#include <SFML/Graphics.hpp>
#include "tile.h"
#include "tilePossessor.h"
#include "deleteTile.h"
#include "createTile.h"
#include "moveTile.h"
#include "directionStrategy.h"
#include "keyboardInput.h"
#include "singleTileDrawingImplementation.h"

#pragma once

class Player : TilePossessor
{
public:
    Player(Tile* tile);
    void move();
    void drawPlayer();
    void update();
    void draw();
    Tile* getTile();
    void changePlacement();

private:
    int x;
    int y;
    Tile* tile;
    sf::ConvexShape playerShape;
    int lastSide = 0;
};