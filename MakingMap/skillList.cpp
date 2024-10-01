#include "skillList.h"

SkillList::SkillList()
	:
	gen(rd())
{
	skills["Lockpicking"] = Skill("Lockpicking", Skill::Difficulty::EASY, Skill::Attribute::DX, std::vector<std::string>{"DX-4", "Kicking-2"});
	skills["Kicking"] = Skill("Kicking", Skill::Difficulty::VH, Skill::Attribute::DX, std::vector<std::string>{});
}

bool SkillList::rollAgainst(const Character& character, int modifier, std::string skillName)
{
	int highest = 0;
	if (character.personalSkills.find(skillName) != character.personalSkills.end())
	{
		highest = character.personalSkills.at(skillName) + modifier;
	}
	else
	{
		int skillLevel = 0;
		for (auto& alternative : skills.at(skillName).defaults) {
			std::string name;
			int mod = 0;
			std::size_t hyphenPos = alternative.find('-');
			if (hyphenPos != std::string::npos) {
				// Split the string at the hyphen
				name = alternative.substr(0, hyphenPos);
				std::string intPartStr = alternative.substr(hyphenPos);

				// Convert the second part to an integer
				mod = std::stoi(intPartStr);
			}
			else
				name = alternative;

			std::cout << "SKILL: " << name << std::endl;

			if (character.personalSkills.find(name) != character.personalSkills.end())
			{
				if (skills.find(name) == skills.end())
					skillLevel = character.personalSkills.at(name) + mod + modifier;
				else
				{
					std::string attrib;
					
					switch (skills.at(name).attribute)
					{
					case Skill::Attribute::DX: attrib = "DX"; break;
					case Skill::Attribute::HT: attrib = "HT"; break;
					case Skill::Attribute::IQ: attrib = "IQ"; break;
					case Skill::Attribute::Will: attrib = "Will"; break;
					}
					skillLevel = skills.at(name).getLevel(character.personalSkills.at(name), character.personalSkills.at(attrib)) + mod + modifier;
					std::cout << "SKILL LEVEL: " << skillLevel << std::endl;
				}
					
			}

			if (skillLevel > highest)
				highest = skillLevel;
		}
	}
	if (highest >= 3)
	{
		std::uniform_int_distribution<int> dis(1, 6);

		int dice1 = dis(gen);
		int dice2 = dis(gen);
		int dice3 = dis(gen);

		if (dice1 + dice2 + dice3 <= highest)
		{
			std::cout << "SUCCESS BY: " << highest - (dice1 + dice2 + dice3) << std::endl;
			return true;
		}
		else
		{
			std::cout << "FAILURE BY: " << (dice1 + dice2 + dice3) - highest << std::endl;
		}
	}
	else
		std::cout << "Can't do it" << std::endl;
	return false;
}
