#include "map.h"

Map::Map()
{
    setStrategy(std::make_unique<MoveTileStrategy>());
    count = 0;
    tile = new Tile(500, 600, sf::Color::Blue, count);
    /*tile->createNewTile(0, count);
    tile->createNewTile(5, count);
    tile->getTile(5)->createNewTile(5, count);
    tile->getTile(0)->createNewTile(0, count);
    tile->getTile(0)->createNewTile(5, count);
    tile->getTile(0)->getTile(5)->createNewTile(4, count);
    tile->getTile(0)->getTile(5)->getTile(4)->createNewTile(3, count);
    tile->getTile(0)->getTile(5)->getTile(4)->getTile(3)->createNewTile(2, count);
    tile->getTile(0)->getTile(5)->getTile(4)->getTile(3)->getTile(2)->createNewTile(1, count);*/

    /*tile->createNewTile(0, count);
    tile->createNewTile(5, count);*/
    tile->createAdjacentTiles(sf::Color::Blue, count);
    fillUp(tile, 50);
    //generateLineMap(tile, 100);
    //createMaze(tile, 10000);
}

void Map::drawMap()
{
    tile->resetVisits();
    tile->drawTile();
    tile->drawSingleTile();
}

Tile* Map::getMainTile()
{
    return tile;
}

void Map::generateLineMap(Tile* curr, int c)
{
    if (c > 0)
    {
        c--;
        int side = rand() % 4 + 2;
        while (curr->getTile(side) != nullptr)
            side = rand() % 4 + 2;
        curr->createNewTile(side, count);
        Tile* next = curr->getTile(side);
        generateLineMap(next, c);
    }
}

void Map::fillUp(Tile* curr, int c)
{
    if (c > 0)
    {
        bool newThing = false;
        for (int i = 0; i < 6; i++)
        {
            bool localNewThing = curr->getTile(i)->createAdjacentTiles(sf::Color::Blue, count);
            newThing = newThing || localNewThing;
            if (localNewThing)
            {
                tileQueue.push(curr->getTile(i));
            }
        }

        if (newThing)
        {
            c--;
        }

        Tile* next = tileQueue.front();
        tileQueue.pop();
        fillUp(next, c);
    }

}

void Map::createMaze(Tile* start, int removals)
{
    std::srand(std::time(0));

    std::queue<Tile*> tileQueue;
    tileQueue.push(start);

    while (removals > 0 && !tileQueue.empty())
    {
        Tile* current = tileQueue.front();
        tileQueue.pop();

        int randomNeighbor = std::rand() % 6;
        Tile* neighbourTile = current->getTile(randomNeighbor);
        if (neighbourTile != nullptr)
            current->unsetTiles(randomNeighbor, current);
        //current->setTile(randomNeighbor, nullptr);

        if (isMazeConnected(start))
        {
            removals--;
        }
        else
        {
            //current->setTile(randomNeighbor, current->getOriginalNeighbor(randomNeighbor));
            current->setMutualBetter(randomNeighbor, current, neighbourTile);
        }

        for (int i = 0; i < 6; i++)
        {
            Tile* neighbor = current->getTile(i);
            if (neighbor != nullptr)
            {
                tileQueue.push(neighbor);
            }
        }
    }
}

bool Map::isMazeConnected(Tile* start)
{
    std::queue<Tile*> tileQueue;
    std::vector<Tile*> visited;

    tileQueue.push(start);
    visited.push_back(start);

    while (!tileQueue.empty())
    {
        Tile* current = tileQueue.front();
        tileQueue.pop();

        for (int i = 0; i < 6; i++)
        {
            Tile* neighbor = current->getTile(i);
            if (neighbor != nullptr && std::find(visited.begin(), visited.end(), neighbor) == visited.end())
            {
                tileQueue.push(neighbor);
                visited.push_back(neighbor);
            }
        }
    }

    // Check if all tiles are reachable
    return visited.size() == count;
}

void Map::update()
{
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    int x = sf::Mouse::getPosition(window).x;
    int y = sf::Mouse::getPosition(window).y;
    side = strategy_.get()->getFlagged()->getSide(x, y);
    strategy_.get()->execute(side, tile);

    //strategy_.get()->execute(window, tile);
    /*int x = sf::Mouse::getPosition(window).x;
    int y = sf::Mouse::getPosition(window).y;
    int side = flagged->getSide(x, y);

    if(side > -1 && side < 6)
        flagged->createNewTile(flagged->getSide(x, y), count);
    flagged = nullptr;*/
}

void Map::flag()
{
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    strategy_.get()->flagTile(tile->findTile(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
    //strategy_.get()->execute(window, tile);
    /*flagged = tile->findTile(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    std::cout << flagged->id << std::endl;*/
}

void Map::draw()
{
}

void Map::setMapStrategy(int strat)
{
    switch (strat)
    {
    case 1:
        setStrategy(std::make_unique<CreateTileStrategy>());
        break;
    case 2:
        setStrategy(std::make_unique<DeleteTileStrategy>());
        break;
    }
}
