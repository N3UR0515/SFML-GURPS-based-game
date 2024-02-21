#include "tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
    for (int i = 0; i < 6; i++)
    {
        if (this->getTile(i) != nullptr)
            this->unsetTiles(i, this);
    }
}

Tile::Tile(int x, int y, sf::Color color, int& count) {
    count++;

    id = count;

    for (int i = 0; i < 6; i++)
        adjacentTiles[i] = nullptr;
    this->x = x;
    this->y = y;
    this->hexagon = makeHexagon(color);

    this->lightningHexagon = makeHexagon(sf::Color{ 0, 0, 0, 0 });
}

void Tile::drawTile() {
    if (!visited)
    {
        sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
        visited = true;
        window.draw(hexagon);

        for (int i = 0; i < 6; i++) {
            if (adjacentTiles[i] != nullptr) {
                adjacentTiles[i]->drawTile();
            }
            else
                drawBorder(i);
        }
    }
}

void Tile::drawSingleTile()
{
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    hexagon.setFillColor(sf::Color::Cyan);
    window.draw(hexagon);
    window.draw(lightningHexagon);
}

void Tile::drawFlashLightTile(int side, int range, int maxRange)
{
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    if (range > 0)
    {
        int steps = 255 / maxRange;
        window.draw(hexagon);
        sf::ConvexShape coverHexagon;
        if (range == maxRange)
        {
            coverHexagon = makeHexagon(sf::Color{ 0,0,0, 200 });
        }
        else
        {
            coverHexagon = makeHexagon(sf::Color{ 0, 0, 0, sf::Uint8(0 + steps * (maxRange - range) + 50) });
        }
        window.draw(coverHexagon);

        for (int i = 0; i < 6; i++)
        {
            if (adjacentTiles[i] == nullptr)
            {
                drawBorder(i);
            }
        }

        if (adjacentTiles[side] != nullptr)
        {
            --range;
            adjacentTiles[side]->drawFlashLightTile(side, range, maxRange);
            adjacentTiles[side]->drawFlashLightTile((side + 1) % 6, range, maxRange);
            adjacentTiles[side]->drawFlashLightTile((6 + side - 1) % 6, range, maxRange);
        }
    }

}

void Tile::drawBorder(int side)
{
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    sf::Vector2f p1 = hexagon.getPoint((side + 1) % 6);
    sf::Vector2f p2 = hexagon.getPoint((side + 2) % 6);

    
    float angle = std::atan2(p2.y - p1.y, p2.x - p1.x) * 180.0f / static_cast<float>(3.14);
   
    float radius = std::sqrt(std::pow(p1.x - p2.x, 2) +
        std::pow(p2.y - p1.y, 2));

    sf::RectangleShape border;
    border.setPosition(p1);
    border.setSize(sf::Vector2f(radius, 5)); 
    border.setFillColor(sf::Color::Red);
    border.setRotation(angle);

    window.draw(border);
}



void Tile::move(int x, int y) {
    this->hexagon.setPosition(x, y);
}

bool Tile::createAdjacentTiles(sf::Color color, int& count) {

    bool newThing = false;

    for (int i = 0; i < 6; i++) {

        if (adjacentTiles[i] == nullptr)
        {
            adjacentTiles[i] = new Tile(x + this->xOffset[i], y + this->yOffset[i], color, count);
            newThing = true;
        }
        adjacentTiles[i]->setTile(refIds[i], this);
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j += 2)
        {
            adjacentTiles[i]->setTile(refs[i][j], adjacentTiles[refs[i][j + 1]]);
        }
    }
    return newThing;
}

Tile* Tile::getTile(int index)
{
    return adjacentTiles[index];
}
void Tile::setSurroundingTiles(int side, Tile* source, Tile* subject)
{
    for (int j = 0; j < 4; j += 2)
    {
        int newSide = refs[side][j];
        Tile* tile = source->getTile(refs[side][j + 1]);
        if (subject->getTile(newSide) == nullptr)
        {
            subject->setTile(newSide, tile);
            if (subject->getTile(newSide) != nullptr)
            {
                subject->getTile(newSide)->setTile(refIds[newSide], subject);

                setSurroundingTiles(refIds[newSide], subject->getTile(newSide), subject);
            }
        }

    }
}

void Tile::unsetTiles(int side, Tile* source)
{
    Tile* neighbour = source->getTile(side);
    neighbour->setTile(refIds[side], nullptr);
    source->setTile(side, nullptr);
}

sf::ConvexShape Tile::makeHexagon(sf::Color color)
{
    sf::ConvexShape hexagon;
    hexagon.setPointCount(6);

    for (int i = 0; i < 6; i++) {
        float angle = i * 60.0f;
        float x1 = radius * cos(angle * 3.14159265 / 180);
        float y1 = radius * sin(angle * 3.14159265 / 180);
        hexagon.setPoint(i, sf::Vector2f(this->x + x1, this->y + y1));
    }

    hexagon.setFillColor(color);
    return hexagon;
}

Tile* Tile::findTile(int x, int y)
{
    std::queue<Tile*> tileQueue;
    std::vector<Tile*> visited;

    tileQueue.push(this);
    visited.push_back(this);

    while (!tileQueue.empty())
    {
        Tile* current = tileQueue.front();
        tileQueue.pop();

        std::cout << x << " " << y << " " << current->x << " " << current->y << std::endl;

        if (current->x == x && current->y == y)
            return current;

        if (isPointInsideHexagon(x, y, current))
            return current;

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
    return nullptr;
}

int Tile::getSide(int x, int y)
{
    if (y < this->y - radius)
    {
        if (x > this->x + radius)
            return 4;
        if (x < this->x - radius)
            return 2;
        return 3;
    }

    if (y > this->y + radius)
    {
        if (x > this->x + radius)
            return 5;
        if (x < this->x - radius)
            return 1;
        return 0;
    }
    return -1;
}

bool Tile::isPointInsideHexagon(int x, int y, Tile* hexagon)
{
    /*// Hexagon vertices
    sf::Vector2f v0 = hexagon->hexagon.getPoint(0);
    sf::Vector2f v1 = hexagon->hexagon.getPoint(1);
    sf::Vector2f v2 = hexagon->hexagon.getPoint(2);
    sf::Vector2f v3 = hexagon->hexagon.getPoint(3);
    sf::Vector2f v4 = hexagon->hexagon.getPoint(4);
    sf::Vector2f v5 = hexagon->hexagon.getPoint(5);

    // Check if the point is inside the hexagon using the point-in-polygon algorithm
    bool oddNodes = false;

    if ((y >= v0.y && y <= v3.y) || (y <= v0.y && y >= v3.y))
    {
        if (x < (v3.x - v0.x) * (y - v0.y) / (v3.y - v0.y) + v0.x)
        {
            oddNodes = !oddNodes;
        }
    }

    if ((y >= v1.y && y <= v4.y) || (y <= v1.y && y >= v4.y))
    {
        if (x < (v4.x - v1.x) * (y - v1.y) / (v4.y - v1.y) + v1.x)
        {
            oddNodes = !oddNodes;
        }
    }

    if ((y >= v2.y && y <= v5.y) || (y <= v2.y && y >= v5.y))
    {
        if (x < (v5.x - v2.x) * (y - v2.y) / (v5.y - v2.y) + v2.x)
        {
            oddNodes = !oddNodes;
        }
    }

    return oddNodes;*/

    return sqrt(pow(x - hexagon->x, 2) + pow(y - hexagon->y, 2)) < radius;

}

void Tile::setPosition(sf::Vector2f position)
{
    this->x = position.x;
    this->y = position.y;

    this->hexagon = makeHexagon(sf::Color::Blue);

    //this->hexagon.setPosition(position);
    //this->hexagon.setPosition(15, 15);
    //std::cout << hexagon. << " " << hexagon.getOrigin().y << std::endl;
}

void Tile::setVisited()
{
    visitedByGrid = true;
}

bool Tile::isVisited() const
{
    return visitedByGrid;
}

float Tile::getRadius()
{
    return radius;
}

void Tile::createNewTile(int side, int& count)
{
    Tile* testTile = findTile(x + xOffset[side], y + yOffset[side]);

    Tile* tile;
    if (testTile == nullptr)
        tile = new Tile(x + xOffset[side], y + yOffset[side], sf::Color::Blue, count);
    else
    {
        tile = testTile;
        std::cout << "Hello" << std::endl;
    }


    setMutual(side, refIds[side], tile);

    setSurroundingTiles(side, this, adjacentTiles[side]);
}

void Tile::setTile(int index, Tile* tile)
{
    adjacentTiles[index] = tile;
}

void Tile::setMutual(int inIndex, int outIndex, Tile* tile)
{
    tile->setTile(outIndex, this);
    this->setTile(inIndex, tile);
}

void Tile::setMutualBetter(int inIndex, Tile* subject, Tile* source)
{
    if (subject != nullptr && source != nullptr)
    {
        subject->setTile(inIndex, source);
        source->setTile(refIds[inIndex], subject);
    }

}

bool Tile::getVisited()
{
    return visited;
}

void Tile::resetVisits() {
    if (visited) {
        visited = false;
        visitedByGrid = false;

        for (int i = 0; i < 6; i++) {
            if (adjacentTiles[i] != nullptr && adjacentTiles[i]->getVisited()) {
                adjacentTiles[i]->resetVisits();
            }
        }
    }
}

void Tile::connectsTo()
{
    std::cout << this->id << " connects to:" << std::endl;
    for (int i = 0; i < 6; i++)
    {
        if (adjacentTiles[i] != nullptr)
            std::cout << adjacentTiles[i]->id << std::endl;
    }
    std::cout << std::endl;
}

sf::Vector2<int> Tile::getCoords()
{
    return sf::Vector2<int>(x, y);
}
