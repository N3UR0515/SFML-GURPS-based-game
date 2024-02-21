#pragma once

#include "tile.h"
#include <SFML/Graphics.hpp>
#include "tilePossessor.h"
#include <cmath>
#include <cstdlib> 
#include <vector>
#include <iostream>
#include <queue>
#include "deleteTile.h"
#include "createTile.h"
#include "moveTile.h"

class Map : TilePossessor
{
public:
    Map();
    void drawMap();
    Tile* getMainTile();
    void generateLineMap(Tile* curr, int c);
    void fillUp(Tile* curr, int c);
    void createMaze(Tile* start, int removals);
    bool isMazeConnected(Tile* start);
    void update();
    void flag();
    void draw();
    void setMapStrategy(int strat);
private:
    //Tile* tile;
    Tile* flagged = nullptr;
    int count;
    std::queue<Tile*> tileQueue;
};