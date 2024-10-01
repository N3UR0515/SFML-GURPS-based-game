#include <SFML/Graphics.hpp>
#include "tile.h"
#include "tilePossessor.h"
#include "deleteTile.h"
#include "createTile.h"
#include "moveTile.h"
#include "directionStrategy.h"
#include "keyboardInput.h"
#include "singleTileDrawingImplementation.h"
#include "tempSide.h"
#include "serverInput.h"
#include <unordered_map>

#pragma once

class Character : TilePossessor
{
public:
    Character(Tile* tile, int id);
    void move();
    void drawPlayer();
    void update();
    void draw();
    Tile* getTile();
    void changePlacement();
    int getLastSide() { return side; }
    void moveOntoTile(Tile* tile);
    void serverSideDirectionStrategy(tempSide* s);
    void attack(std::vector<Character>&players);
    int id;

private:
    int x;
    int y;
    Tile* tile;
    sf::ConvexShape playerShape;

public:
    /*struct personalSkill
    {
        std::string name;
        int level;
    };*/

    std::unordered_map<std::string, int> personalSkills;

    //std::vector<personalSkill> personalSkills;
};