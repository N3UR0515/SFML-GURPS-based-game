#include <unordered_map>
#include <random>
#include "skill.h"
#include "character.h"

#pragma once
class SkillList
{
public:
	SkillList();
	bool rollAgainst(const Character& character, int modifier, std::string skillName);
private:
	std::unordered_map<std::string, Skill> skills;
	std::random_device rd;
	std::mt19937 gen;
};

