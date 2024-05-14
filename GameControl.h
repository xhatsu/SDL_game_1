#pragma once
#include<chrono>
#include<vector>
#include"playerScore.h";
#include"SDL.h"
#include"leaderBoard.h"
extern std::vector<playerScore> leaderBoardList;
extern leaderBoard leaderBoard1;
extern SDL_Texture* submittingScore;
extern std::string playerName;
extern SDL_Renderer* renderer;
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
	void checkForNewHighScore() {
		for (int i = 0; i < leaderBoardList.size(); i++) {
			if (highestLevel > leaderBoardList.at(i).maxLevel) {
				SDL_RenderCopy(renderer, submittingScore, NULL, NULL);
				SDL_RenderPresent(renderer);
				playerScore newHighScore;
				newHighScore.maxLevel = highestLevel;
				newHighScore.playerName = playerName;
				leaderBoard1.setLeaderBoard(newHighScore);
				leaderBoard1.updateLeaderBoard();
				SDL_Delay(1000);
				return;
			}
		}
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
		checkForNewHighScore();
		level++;
		targetKilled = 0;
		gameStart = false;
		levelTarget = 5 + level*3 + 2;
		levelDuration = std::chrono::seconds(30) + std::chrono::seconds(10) + std::chrono::seconds(levelTarget * 2) + std::chrono::seconds(level - int(double(level) * 0.4));
		levelTimeLeft = levelDuration;
		targetSpeed = 1 + int(double(level) / 3);
		if (level % 5 == 0) {
			targetSpeed++;
		}
	}
	void resetGame() {
		level = 1;
		spawnRate = 0.05;
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