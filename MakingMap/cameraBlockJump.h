#include "tileStrategy.h"
#pragma once

class CameraBlockJump : public TileStrategy
{
protected:
	Tile* jumpTo;
public:
	void execute(int side, Tile*& tile) override;
	void setJump(Tile* tile) {
		jumpTo = tile;
	}
};

