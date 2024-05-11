#pragma once
#include<chrono>

class GameControl
{
public:
	int level;
	bool fail = false;
	double spawnRate;
	bool gameStart;
	int levelTarget;
	int targetKilled;
	int targetSpeed;
	int spawnRange;
	int highestLevel = 1;
	std::chrono::steady_clock::time_point startTime;
	std::chrono::seconds levelDuration;
	std::chrono::seconds levelTimeLeft;
	GameControl() {
		targetSpeed = 1;
		spawnRange = 1280 * 3;
		level = 1;
		spawnRate = 0.1;
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
	void updateLevel() {
		if (highestLevel < level) {
			highestLevel = level;
		}
		level++;
		levelDuration = levelDuration + std::chrono::seconds(5) + std::chrono::seconds(level - int(double(level) * 0.4));
		targetKilled = 0;
		levelTarget += 5;
		spawnRate = 0.1 - double(level) * 0.01;
		gameStart = false;
		levelTimeLeft = levelDuration;
		targetSpeed = targetSpeed + int(double(level) / 5);
	}
	void resetGame() {
		level = 1;
		spawnRate = 0.1;
		gameStart = false;
		levelTarget = 5;
		targetKilled = 0;
		levelDuration = std::chrono::seconds(30);
		levelTimeLeft = levelDuration;
	}
	int gameUpdate() {
		getTimeLeft();
		if (targetKilled >= levelTarget) {
			updateLevel();
			return 1;
		}
		if (targetKilled < levelTarget) {
			if (levelTimeLeft < std::chrono::seconds(1)) {
				fail=true;
				printf("fail");
				resetGame();
				return -1;
				
			}
		}
		if (gameStart == false) {
			return 2;
		}
		return 0;
	}

};