#include "serverInput.h"

int ServerInput::getSide()
{
	return s->getSide();
}

ServerInput::ServerInput(tempSide* set)
	:
	s(set)
{
}

