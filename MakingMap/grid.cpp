#include "grid.h"

Grid::Grid()
{
	sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();

	std::cout << "SIZE: ";
	std::cout << window.getSize().x << " " << window.getSize().y << std::endl;

	const float radius = Tile::getRadius();

	firstTile.x = radius;
	firstTile.y = radius;
	
	steps.x = radius + radius * (static_cast<float>(2) / 3);
	steps.y = radius*2;

}

void Grid::mapToGrid(Tile* mainTile) const
{
	mainTile->setVisited();


	sf::Vector2f position = configPosition();
	

	mapToGridRecursion(mainTile, position);
}

void Grid::setSide(int toSet)
{
	side = toSet;
}

sf::Vector2f Grid::configPosition() const
{
	sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
	float centerX = (window.getSize().x / 2) / (firstTile.x * 2);
	float centerY = (window.getSize().y / 2) / (firstTile.y * 2);
	float topY = (window.getSize().y) / (firstTile.y * 2) - 1;
	float bottomY = 0;
	float rightX = 0;
	float leftX = (window.getSize().x) / (firstTile.x * 2) + 1;
	sf::Vector2f pos = { centerX, centerY };
	
	switch (side)
	{
	case -1:
		break;
	case 0:
		pos.x = centerX;
		pos.y = bottomY;
		break;
	case 1:
		pos.x = leftX;
		pos.y = bottomY;
		break;
	case 2:
		pos.x = leftX;
		pos.y = topY;
		break;
	case 3:
		pos.x = centerX;
		pos.y = topY;
		break;
	case 4:
		pos.x = rightX;
		pos.y = topY;
		break;
	case 5:
		pos.x = rightX;
		pos.y = bottomY;
		break;
	}
	return { firstTile.x + steps.x * pos.x, firstTile.y + steps.y * pos.y };
}

void Grid::mapToGridRecursion(Tile* currentTile, sf::Vector2f nextPosition) const
{
	currentTile->setPosition(nextPosition);

	for (int i = 0; i < 6; i++)
	{
		Tile* neighbour = currentTile->getTile(i);
		if (neighbour != nullptr && !neighbour->isVisited())
		{
			neighbour->setVisited();
			sf::Vector2f nextNextPosition = nextPosition;

			switch (i)
			{
			case 0: 
				nextNextPosition.y += steps.y;
				break;
			case 1:
				nextNextPosition.y += steps.y / 2;
				nextNextPosition.x -= steps.x;
				break;
			case 2:
				nextNextPosition.y -= steps.y / 2;
				nextNextPosition.x -= steps.x;
				break;
			case 3:
				nextNextPosition.y -= steps.y;
				break;
			case 4:
				nextNextPosition.y -= steps.y / 2;
				nextNextPosition.x += steps.x;
				break;
			case 5:
				nextNextPosition.y += steps.y / 2;
				nextNextPosition.x += steps.x;
				break;
			}

			mapToGridRecursion(neighbour, nextNextPosition);
		}
	}
}
