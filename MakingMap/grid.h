#pragma once

#include <SFML/Graphics.hpp>
#include "renderWindowSingleton.h"
#include "tile.h"
#include "map.h"
#include "character.h"
#include <vector>

class Grid
{
public:
	Grid();
	void mapToGrid(Tile* mainTile) const;
	sf::Vector2f configPosition() const;
	void setSide(int toSet);

private:
	sf::Vector2f firstTile;
	sf::Vector2f steps;
	void mapToGridRecursion(Tile* currentTile, sf::Vector2f nextPosition) const;
	int side = -1;
};

