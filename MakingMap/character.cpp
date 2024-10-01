#include "character.h"

Character::Character(Tile* tile, int id)
    :
    id(id)
{
    setStrategy(std::make_unique<MoveTileStrategy>());
    //strategy_.get()->addDrawingImplementation(new SingleTileDrawingImplementation());
    setDirStrategy(std::make_unique<KeyboardInputDirectionStrategy>());
    //std::move(std::make_unique<KeyboardInputDirectionStrategy>());
    this->tile = tile;

    playerShape.setPointCount(3);
    playerShape.setPoint(0, sf::Vector2f(0, 0));
    playerShape.setPoint(1, sf::Vector2f(20, 0));
    playerShape.setPoint(2, sf::Vector2f(10, -20));

    playerShape.setFillColor(sf::Color::Green);


    playerShape.setPosition(tile->getCoords().x, tile->getCoords().y);

    personalSkills["IQ"] = 10;
    personalSkills["ST"] = 10;
    personalSkills["DX"] = 11;
    personalSkills["HT"] = 10;
    personalSkills["Will"] = 10;
    personalSkills["Kicking"] = 2;

    personalSkills["HP"] = 10;
    personalSkills["Brawling"] = 10;
    personalSkills["Dodge"] = 7;

}

void Character::move()
{
    side = dirStrategy_.get()->getSide();

    strategy_.get()->flagTile(tile);

    update();

    changePlacement();
}

void Character::drawPlayer()
{
    tile->resetVisits();
    tile->drawTile(false);
    tile->drawFlashLightTile(side, 3, 3);
    tile->drawFlashLightTile((side + 1) % 6, 3, 3);
    tile->drawFlashLightTile((6 + side - 1) % 6, 3, 3);  
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    window.draw(playerShape);
}

void Character::update()
{
    strategy_.get()->execute(side, tile);
}

void Character::draw()
{
    //strategy_.get()->drawFlaggedTiles();
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    window.draw(playerShape);
}

Tile* Character::getTile()
{
    return tile;
}

void Character::changePlacement()
{
    playerShape.setPosition(tile->getCoords().x, tile->getCoords().y);
}

void Character::moveOntoTile(Tile* tile)
{
    this->tile = tile;
}

void Character::serverSideDirectionStrategy(tempSide* s)
{
    //setDirStrategy(std::make_unique<ServerInput>(s));
}

void Character::attack(std::vector<Character>& players)
{
    Tile* attacked = this->tile->getTile(side);

    for (Character& c : players)
    {
        if (c.getTile() == attacked)
        {
            std::cout << c.id << " Got HIT " << std::endl;
            c.personalSkills["HP"]-=10;
        }
    }
}
