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
	std::cout << steps.x << std::endl;
	steps.y = radius*2;

}

void Grid::mapToGrid(Map& map) const
{
	Tile* tile = map.getMainTile();
	//tile->setPosition(firstTile);
	tile->setVisited();

	sf::Vector2<int> count = { 0, 0 };

	mapToGridRecursion(tile, count, firstTile);


	/*while (tile->getTile(0) != nullptr)
	{
		tile = tile->getTile(0);
		count.y++;
		float yCoord = steps.y * count.y + firstTile.y;
		tile->setPosition(sf::Vector2f{ firstTile.x, steps.y * count.y + firstTile.y });
	}*/
}

void Grid::playerToGrid(Player& player) const
{
	Tile* tile = player.getTile();
	tile->setVisited();

	sf::Vector2<int> count = { 4, 5 };

	mapToGridRecursion(tile, count, firstTile);
}

void Grid::mapToGridRecursion(Tile* currentTile, sf::Vector2<int> count, sf::Vector2f nextPosition) const
{
	float xPos = firstTile.x + count.x * steps.x;
	float yPos = firstTile.y + count.y * steps.y;
	std::cout << "STUFF" << std::endl;
	std::cout << xPos << " " << yPos << std::endl;

	if (count.x % 2 != 0)
		yPos += firstTile.y;

	//currentTile->setPosition(sf::Vector2f(xPos, yPos));
	currentTile->setPosition(nextPosition);

	for (int i = 0; i < 6; i++)
	{
		Tile* neighbour = currentTile->getTile(i);
		if (neighbour != nullptr && !neighbour->isVisited())
		{
			neighbour->setVisited();
			sf::Vector2<int> nextCount = count;
			sf::Vector2f nextNextPosition = nextPosition;

			if (i == 0) {
				nextCount.y++;
				nextNextPosition.y += steps.y;
			}
			else if (i == 1) {
				nextNextPosition.y += steps.y / 2;
				nextNextPosition.x -= steps.x;
				nextCount.y++;
				nextCount.x--;
			}
			else if (i == 2) {
				nextNextPosition.y -= steps.y / 2;
				nextNextPosition.x -= steps.x;
				nextCount.x--;
			}
			else if (i == 3) {
				nextNextPosition.y -= steps.y;
				nextCount.y--;
			}
			else if (i == 4) {
				nextNextPosition.y -= steps.y / 2;
				nextNextPosition.x += steps.x;
				nextCount.x++;
			}
			else if (i == 5) {
				nextNextPosition.y += steps.y / 2;
				nextNextPosition.x += steps.x;
				//nextCount.y++;
				nextCount.x++;
			}
			mapToGridRecursion(neighbour, nextCount, nextNextPosition);
		}
	}
}
