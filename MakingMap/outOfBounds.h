#pragma once
#include "directionStrategy.h"
#include "character.h"

class OutOfBounds : public DirectionStrategy
{
protected:
	Character* trackable;
public:
	int getSide() override;
	void setTrack(Character* player);
};

