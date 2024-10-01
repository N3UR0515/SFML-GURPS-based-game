#include "deleteTile.h"

void DeleteTileStrategy::execute(int side, Tile*& tile)
{
    if (!flaggedTiles.empty())
    {
        setTileToConnect(tile);
        Tile* flagged = flaggedTiles.back();
        flaggedTiles.pop_back();

        if (side == -1 && flagged != tile)
        {
            std::vector<Tile*> temp;
            for (int i = 0; i < 6; i++)
            {
                if (flagged->getTile(i) != nullptr)
                {
                    temp.push_back(flagged->getTile(i));
                    flagged->unsetTiles(i, flagged);
                }
                    
            }

            delete flagged;

            for (int i = 0; i < temp.size(); i++)
            {
                deleteUnconnected(temp.at(i));
            }
            temp.clear();
        }
        else if (side > -1 && side < 6 && flagged->getTile(side) != nullptr)
        {
            tile = flagged->getTile(side);
            setTileToConnect(tile);
            flagged->unsetTiles(side, flagged);
            deleteUnconnected(flagged);
        }
    }
}

void DeleteTileStrategy::setTileToConnect(Tile* toSet)
{
    connectTo = toSet;
}

bool DeleteTileStrategy::flagUnconnected(Tile* tile)
{
    if(tile == connectTo)
        return true;

    tile->setVisitedByDelete();
    
    toDelete.push_back(tile);

    bool connect = false;

    for (int i = 0; i < 6 && !connect; i++)
    {
        Tile* neighbour = tile->getTile(i);
        if (neighbour != nullptr && !neighbour->isVisitedByDelete())
        {
            std::cout << i << std::endl;
            connect = connect || flagUnconnected(neighbour);
            std::cout << "CONNECT " << connect << std::endl;
        }     
    }

    return connect;
}

void DeleteTileStrategy::deleteUnconnected(Tile* tile)
{
    if (!flagUnconnected(tile))
    {
        for (int i = 0; i < toDelete.size(); i++)
        {
            Tile* flagged = toDelete.at(i);
            for (int j = 0; j < 6; j++)
            {
                std::cout << j << std::endl;
                if (flagged->getTile(j) != nullptr)
                    flagged->unsetTiles(j, flagged);
            }
            delete flagged;
        }
    }
    tile->resetVisitedByDeleted();
    toDelete.clear();
}
