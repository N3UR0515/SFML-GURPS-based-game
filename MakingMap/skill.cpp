#include "skill.h"

Skill::Skill(std::string nameToSet, Difficulty diffToSet, Attribute attribToSet, std::vector<std::string> defaultsToSet)
	:
	name(nameToSet),
	difficulty(diffToSet),
	defaults(defaultsToSet),
	attribute(attribToSet)
{
}

Skill::Skill()
	:
	difficulty(Difficulty::EASY)
{
}


int Skill::getLevel(int points, int attribute)
{
	int level = attribute;

	level -= difficulty;

	level += points / 4;
	if (points >= 2) level++;

	return level;
}
