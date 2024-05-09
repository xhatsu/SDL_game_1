#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
extern TTF_Font* pixelFont;
extern SDL_Renderer* renderer;
extern void renderTransparentBlackRectangle(SDL_Renderer* renderer, SDL_Rect const &rect, int alpha);
class inGameMenu
{
public:
	SDL_Rect topLeftInfo;
	SDL_Rect firstGameGuide;
	SDL_Rect startLevelButton;
	int currentLevel;
	int levelTarget;
	int timeLeft;
	int targetKilled;
	inGameMenu(int level,int time,int target) {
		topLeftInfo.x = 0;
		topLeftInfo.y = 0;
		topLeftInfo.w = 300;
		topLeftInfo.h = 110;
		firstGameGuide.x = 300;
		firstGameGuide.y = 300;
		firstGameGuide.w = 512;
		firstGameGuide.h = 512;
		startLevelButton.x = 600;
		startLevelButton.y = 600;
		startLevelButton.w = 50;
		startLevelButton.h = 50;
		currentLevel = level;
		timeLeft = time;
		targetKilled = 0;
		levelTarget = target;
	}
	void updateData(int level, int time, int killed,int target) {
		currentLevel = level;
		timeLeft = time;
		targetKilled = killed;
		levelTarget = target;
	}
	void renderTopLeft() {
		renderTransparentBlackRectangle(renderer,topLeftInfo ,178);
		SDL_Color textColor = {255,255,255};
		std::string levelString = "Level: " + std::to_string(currentLevel);
		int minute = timeLeft / 60;
		int second = timeLeft - minute * 60;
		std::string timeLeftString = "Time left: " + std::to_string(minute) + ":" + std::to_string(second);
		std::string killedString = "Target: " + std::to_string(targetKilled) + "/" + std::to_string(levelTarget);
		SDL_Surface* textSurface;
		SDL_Texture* textTexture;
		//print current level
		textSurface = TTF_RenderText_Solid(pixelFont, levelString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect textRect;
		textRect.x = 10;
		textRect.y = 5;
		textRect.w = topLeftInfo.w-128;
		textRect.h = topLeftInfo.h;
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		//print time left
		textSurface = TTF_RenderText_Solid(pixelFont, timeLeftString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textRect.y += 35;
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		//print killed target
		textSurface = TTF_RenderText_Solid(pixelFont, killedString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textRect.y += 35;
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_FreeSurface(textSurface);
	}
};

