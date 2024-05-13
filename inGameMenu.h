#pragma once
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_ttf.h"
#include<string>
extern TTF_Font* pixelFont;
extern SDL_Renderer* renderer;
extern void renderTransparentBlackRectangle(SDL_Renderer* renderer, SDL_Rect const &rect, int alpha);
class inGameMenu
{
public:
	SDL_Rect topLeftInfo;
	SDL_Rect startLevelInfo;
	SDL_Rect startLevelButton;
	SDL_Surface* textSurface=NULL;
	SDL_Texture* textTexture=NULL;
	int currentLevel;
	int levelTarget;
	int timeLeft;
	int targetKilled;
	int highestLevel=0;
	inGameMenu(int level,int time,int target) {
		topLeftInfo.x = 0;
		topLeftInfo.y = 0;
		topLeftInfo.w = 300;
		topLeftInfo.h = 110;
		startLevelInfo.x = 384;
		startLevelInfo.y = 104;
		startLevelInfo.w = 512;
		startLevelInfo.h = 512;
		startLevelButton.x = 540;
		startLevelButton.y = 500;
		startLevelButton.w = 210;
		startLevelButton.h = 50;
		currentLevel = level;
		timeLeft = time;
		targetKilled = 0;
		levelTarget = target;
	}
	void updateData(int level, int time, int killed,int target,int highest) {
		currentLevel = level;
		timeLeft = time;
		targetKilled = killed;
		levelTarget = target;
		highestLevel = highest;
	}
	void renderTopLeft() {
		renderTransparentBlackRectangle(renderer,topLeftInfo ,178);
		SDL_Color textColor = {255,255,255};
		std::string levelString = "Level: " + std::to_string(currentLevel);
		int minute = timeLeft / 60;
		int second = timeLeft - minute * 60;
		std::string secondString;
		if (second >= 10) {
			secondString = std::to_string(second);
		}
		else  {
			secondString = "0" + std::to_string(second);
		}
		std::string timeLeftString = "Time left: " + std::to_string(minute) + ":" + std::to_string(second);
		std::string killedString = "Target: " + std::to_string(targetKilled) + "/" + std::to_string(levelTarget);

		//print current level
		textSurface = TTF_RenderText_Blended(pixelFont, levelString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
		SDL_Rect textRect;
		textRect.x = 10;
		textRect.y = 5;
		textRect.w = topLeftInfo.w-128;
		textRect.h = topLeftInfo.h;
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		//print time left
		textSurface = TTF_RenderText_Blended(pixelFont, timeLeftString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
		textRect.y += 35;
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		//print killed target
		textSurface = TTF_RenderText_Blended(pixelFont, killedString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textRect.y += 35;
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
	}
	void renderStartLevel() {
		renderTransparentBlackRectangle(renderer, startLevelInfo, 178);
		std::string levelString = "Level: " + std::to_string(currentLevel);
		int minute = timeLeft / 60;
		int second = timeLeft - minute * 60;
		std::string timeString = "Time: " + std::to_string(minute) + ":" + std::to_string(second);
		std::string targetString = "Target: " + std::to_string(levelTarget);
		std::string highestString = "Highest level: " + std::to_string(highestLevel);
		SDL_Rect textRect;
		textRect.x = startLevelInfo.x+25;
		textRect.y = startLevelInfo.y+25;
		textRect.w = startLevelInfo.w;
		textRect.h = startLevelInfo.h;
		SDL_Color textColor = { 255,255,255 };
		//render level string
		textSurface = TTF_RenderText_Blended(pixelFont, levelString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
		//render time string
		textRect.y += 50;
		textSurface = TTF_RenderText_Blended(pixelFont, timeString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
		//render target string
		textRect.y += 50;
		textSurface = TTF_RenderText_Blended(pixelFont, targetString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
		//render highest level
		textRect.y += 50;
		textSurface = TTF_RenderText_Blended(pixelFont, highestString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
		//render start button
		SDL_SetRenderDrawColor(renderer, 0, 255, 127,128);
		SDL_RenderFillRect(renderer, &startLevelButton);
		std::string startLevel = "Start Level";
		textRect.x = startLevelButton.x+5;
		textRect.y = startLevelButton.y+15;
		textSurface = TTF_RenderText_Blended(pixelFont, startLevel.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
		
	}
};

