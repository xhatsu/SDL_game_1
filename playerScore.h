#pragma once
#include<string>

class playerScore
{
public:
	std::string playerName;
	int maxLevel;
	playerScore() {
		playerName = "None";
		maxLevel = -1;
	}

};

