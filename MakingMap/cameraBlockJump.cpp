#include "cameraBlockJump.h"
#include <cmath>

void CameraBlockJump::execute(int side, Tile*& tile)
{
	if (side > -1)
	{
		/*sf::RenderWindow& window = RenderWindowSingleton::GetInstance()->getWindow();
		float radius = Tile::getRadius();

		double angle = 45;
		double radians = angle * (3.14 * 180);
		double cos_value = std::cos(radians);

		int xBlocks = window.getSize().x / (radius * 2) / cos_value;
		int yBlocks = window.getSize().y / (radius*2);

		Tile* next = tile->getTile(side);

		for (int i = 0; i < 1 && next != nullptr; i++)
		{
			tile = next;
			next = tile->getTile(side);
		}*/

		if (jumpTo != nullptr)
		{
			tile = jumpTo;
			Tile* next = tile->getTile(side);
			/*for (int i = 0; i < 2 && next != nullptr; i++)
			{
				tile = next;
				next = tile->getTile(side);
			}*/
		}
			
	}
	
}
