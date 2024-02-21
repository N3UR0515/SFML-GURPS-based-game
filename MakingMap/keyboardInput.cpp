#include "keyboardInput.h"

int KeyboardInputDirectionStrategy::getSide()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        return 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        return 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        return 2;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        return 3;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        return 4;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return 5;
    }
}