#pragma once

#include "tile.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "tilePossessor.h"
#include <cmath>
#include <cstdlib> 
#include <vector>
#include <iostream>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include "deleteTile.h"
#include "createTile.h"
#include "moveTile.h"
#include "cameraBlockJump.h"
#include "DoNothingTile.h"
#include "outOfBounds.h"
#include "character.h"
#include "json.hpp"
#include "serverInput.h"
#include "tempSide.h"

using json = nlohmann::json;

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
    int update1();
    void update();
    std::string constructPacket() const;
    void flag();
    void draw();
    void setMapStrategy(int strat);
    void saveMap();
    void loadMap();
    void deleteMap(Tile* tileToDelete);
    void clientSideDirectionStraregy(tempSide* s);
private:
    //Tile* tile;
    Tile* flagged = nullptr;
    int count;
    std::queue<Tile*> tileQueue;
    int strat = 4;
};