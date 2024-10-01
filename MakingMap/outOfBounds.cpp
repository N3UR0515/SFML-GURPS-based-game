#include "outOfBounds.h"
#include "tile.h"

int OutOfBounds::getSide()
{
    if (trackable != nullptr)
    {
        sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
        int xBound = window.getSize().x;
        int yBound = window.getSize().y;


        sf::Vector2<int> coords = trackable->getTile()->getCoords();

        int radius = Tile::getRadius();

        if (coords.y < radius || coords.y + radius > yBound || coords.x < radius || coords.x + radius > xBound)
            return trackable->getLastSide();
        
    }
    return -1;
}

void OutOfBounds::setTrack(Character* player)
{
    trackable = player;
}
