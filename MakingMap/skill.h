#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#pragma once
class Skill
{
public:
	static enum Difficulty {
		EASY,
		AVERAGE,
		HARD,
		VH
	};
	static enum Attribute {
		IQ,
		DX,
		HT,
		Will
	};

	Skill(std::string nameToSet, Difficulty diffToSet, Attribute attribToSet, std::vector<std::string> defaultsToSet);
	Skill();
	std::string name;
	Difficulty difficulty;
	Attribute attribute;
	std::vector<std::string> defaults;
	int getLevel(int points, int attribute);
};

