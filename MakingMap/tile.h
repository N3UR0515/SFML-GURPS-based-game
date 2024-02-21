#include <SFML/Graphics.hpp>
#include <cmath>
#include <array>
#include <iostream>
#include <vector>
#include <queue>
#include "renderWindowSingleton.h"
#pragma once

class Tile {
public:
    Tile();
    ~Tile();
    Tile(int x, int y, sf::Color color, int& count);
    void drawTile();
    void drawSingleTile();
    void drawFlashLightTile(int side, int range, int maxRange);
    void drawBorder(int side);
    void move(int x, int y);
    bool createAdjacentTiles(sf::Color color, int& count);
    Tile* getTile(int index);
    void createNewTile(int side, int& count);
    void setTile(int index, Tile* tile);
    void setMutual(int inIndex, int outIndex, Tile* tile);
    void setMutualBetter(int inIndex, Tile* source, Tile* subject);
    bool getVisited();
    void resetVisits();
    void connectsTo();
    void setSurroundingTiles(int side, Tile* source, Tile* subject);
    void unsetTiles(int side, Tile* source);
    sf::ConvexShape makeHexagon(sf::Color color);
    Tile* findTile(int x, int y);
    int getSide(int x, int y);
    bool isPointInsideHexagon(int x, int y, Tile* hexagon);
    void setPosition(sf::Vector2f position);

    void setVisited();
    bool isVisited() const;

    static float getRadius();

    sf::Vector2<int> getCoords();

    int id;

private:
    int x;
    int y;
    sf::ConvexShape hexagon;
    sf::ConvexShape lightningHexagon;
    std::array<Tile*, 6> adjacentTiles;
    static constexpr float radius = 30.0f;
    bool visited;
    bool visitedByGrid = false;

    const int distance = 2 * radius;
    const int yOffset[6] = { distance, distance / 2, -distance / 2, -distance, -distance / 2, distance / 2 };
    const int xOffset[6] = { 0, int(- distance * sqrt(3) / 2), int(- distance * sqrt(3) / 2), 0, int(distance * sqrt(3) / 2), int(distance * sqrt(3) / 2)};
    const int refIds[6] = { 3, 4, 5, 0, 1, 2 };
    const int refs[6][6] = {
        {2, 1, 4, 5},
        {3, 2, 5, 0},
        {0, 1, 4, 3},
        {1, 2, 5, 4},
        {0, 5, 2, 3},
        {1, 0, 3, 4}

    };
};
