#include "directionStrategy.h"
#include <SFML/Graphics.hpp>

#pragma once

class KeyboardInputDirectionStrategy : public DirectionStrategy
{
public:
    int getSide() override;
};