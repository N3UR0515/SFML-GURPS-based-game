#pragma once
#include "directionStrategy.h"
#include "tempSide.h"


class ServerInput : public DirectionStrategy
{
protected:
	tempSide* s;
public:
	int getSide() override;
	ServerInput(tempSide* set);
};

