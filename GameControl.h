#pragma once
#include<chrono>

class GameControl
{
public:
	int level;
	int spawnRate;
	bool gameStart;
	int levelTarget;
	int targetKilled;
	std::chrono::steady_clock::time_point startTime;
	std::chrono::seconds levelDuration;
	std::chrono::seconds levelTimeLeft;
	GameControl() {
		level = 1;
		spawnRate = 0;
		gameStart = false;
		levelTarget = 5;
		targetKilled = 0;
		levelDuration = std::chrono::seconds(30);
		levelTimeLeft = levelDuration;
	}
	void startGame() {
		gameStart = true;
		startTime = std::chrono::steady_clock::now();
	}

	void setSpawnRate(int spawnRateNew) {
		spawnRate = spawnRateNew;
	}
	void getTimeLeft() {
		levelTimeLeft = timeLeft();
	}
	std::chrono::seconds timeLeft() {
		if (gameStart) {
			auto now = std::chrono::steady_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
			if (elapsed < levelDuration) {
				return levelDuration - elapsed;
			}
			else {
				return std::chrono::seconds(0);
			}
		}
		else {
			return levelDuration;
		}
	}

};