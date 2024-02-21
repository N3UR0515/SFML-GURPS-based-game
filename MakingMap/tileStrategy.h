#include "tile.h"
#include <vector>

#pragma once

class DrawingImplementation
{
public:
    virtual ~DrawingImplementation() = default;
    virtual void drawTiles(std::vector<Tile*> flaggedTiles) = 0;
};

class TileStrategy
{
protected:
    std::vector<Tile*> flaggedTiles;
    std::vector<DrawingImplementation*> drawingImplementations;

public:
    virtual ~TileStrategy()
    {
        for (DrawingImplementation* impl : drawingImplementations)
        {
            delete impl;
        }
    }

    virtual void execute(int side, Tile*& tile) = 0;

    void flagTile(Tile* flagged)
    {
        if (std::find(flaggedTiles.begin(), flaggedTiles.end(), flagged) == flaggedTiles.end())
        {
            flaggedTiles.push_back(flagged);
        }
    }

    void addDrawingImplementation(DrawingImplementation* implementation)
    {
        drawingImplementations.push_back(implementation);
    }

    Tile* getFlagged()
    {
        return flaggedTiles.front();
    }

    void drawFlaggedTiles()
    {
        for (DrawingImplementation* impl : drawingImplementations)
        {
            impl->drawTiles(flaggedTiles);
        }
    }
};