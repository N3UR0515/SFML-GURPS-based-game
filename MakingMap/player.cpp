#include "player.h"

Player::Player(Tile* tile)
{
    setStrategy(std::make_unique<MoveTileStrategy>());
    strategy_.get()->addDrawingImplementation(new SingleTileDrawingImplementation());
    setDirStrategy(std::make_unique<KeyboardInputDirectionStrategy>());
    //std::move(std::make_unique<KeyboardInputDirectionStrategy>());
    this->tile = tile;

    std::cout << "ID: " << tile->id << std::endl;

    playerShape.setPointCount(3);
    playerShape.setPoint(0, sf::Vector2f(0, 0));
    playerShape.setPoint(1, sf::Vector2f(20, 0));
    playerShape.setPoint(2, sf::Vector2f(10, -20));

    playerShape.setFillColor(sf::Color::Green);


    playerShape.setPosition(tile->getCoords().x, tile->getCoords().y);

}

void Player::move()
{
    side = dirStrategy_.get()->getSide();

    strategy_.get()->flagTile(tile);

    update();

    changePlacement();
}

void Player::drawPlayer()
{
    tile->drawFlashLightTile(side, 3, 3);
    tile->drawFlashLightTile((side + 1) % 6, 3, 3);
    tile->drawFlashLightTile((6 + side - 1) % 6, 3, 3);
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    window.draw(playerShape);
}

void Player::update()
{
    strategy_.get()->execute(side, tile);
}

void Player::draw()
{
    //strategy_.get()->drawFlaggedTiles();
    sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
    window.draw(playerShape);
}

Tile* Player::getTile()
{
    return tile;
}

void Player::changePlacement()
{
    playerShape.setPosition(tile->getCoords().x, tile->getCoords().y);
}
