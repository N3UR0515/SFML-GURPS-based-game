#pragma once

#include <SFML/Graphics.hpp>
#include "renderWindowSingleton.h"
#include "tile.h"
#include "map.h"
#include "player.h"
#include <vector>

class Grid
{
public:
	Grid();
	void mapToGrid(Map& map) const;
	void playerToGrid(Player& player) const;

private:
	sf::Vector2f firstTile;
	sf::Vector2f steps;
	void mapToGridRecursion(Tile* currentTile, sf::Vector2<int>count, sf::Vector2f nextPosition) const;
};

