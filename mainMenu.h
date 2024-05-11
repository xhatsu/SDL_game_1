#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"map_process.h"
#include"background.h"
#include"entity_control.h"
#include<vector>
extern TTF_Font* pixelFont;
extern SDL_Renderer* renderer;
extern int desiredDelta;
class mainMenu
{
    bool menuChoosed = false;
    
    SDL_Color textColor = { 255, 255, 255 }; // white color
    // Create the menu items
    std::string startGame= "Start Game";
    std::string exitGame = "Exit";
    // Render the menu items
    SDL_Rect startGameRect;
    SDL_Rect exitGameRect;
    SDL_Surface* textSurface=NULL;
    SDL_Texture* textTexture=NULL;
    backGround menuBackGround;
    entityControl menuEntityControl;
    mapProcess menuMapProcess;
    SDL_Event event_input;
public:
    int menuChoose = 0;
    mainMenu() {
        startGameRect.x = 100;
        startGameRect.y = 200;
        startGameRect.w = 180;
        startGameRect.h = 20;
        exitGameRect.x = 100;
        exitGameRect.y = 300;
        exitGameRect.w = 80;
        exitGameRect.h = 20;
        menuMapProcess.getChunkList("mapData.json");
    }
    int loadMenu() {
        menuChoose = 0;
        menuChoosed = false;
        menuEntityControl.entityList.clear();
        for (int i = 0; i < 100; i++) {
            menuEntityControl.spawnRandomEntity(1, true, 320, 320, 0.09, 1280);
        }
        menuMapProcess.arrangeChunk(0, 0);
        menuMapProcess.arrangeObject();
        menuMapProcess.updateCheckList();
        while (menuChoosed == false) {
            int start_loop = SDL_GetTicks64();
            //render back ground
            menuBackGround.updateChunk(-1);
            menuEntityControl.loadEntityList();
            menuMapProcess.updateMap(false);
            menuMapProcess.updateMap(true);
            // Render the menu items
            SDL_Rect textRect;
            //render Start Game
            textSurface = TTF_RenderText_Solid(pixelFont, startGame.c_str(), textColor);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
            textRect = startGameRect;
            SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
            SDL_RenderDrawRect(renderer, &startGameRect);
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
            //render exit game
            textSurface = TTF_RenderText_Solid(pixelFont, exitGame.c_str(), textColor);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
            textRect = exitGameRect;
            SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
            SDL_RenderDrawRect(renderer, &exitGameRect);
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
            //render to screen
            SDL_RenderPresent(renderer);
            //handle input
            while (SDL_PollEvent(&event_input)) {
                if (event_input.type == SDL_QUIT) {
                    menuChoose = -1;
                    menuChoosed = true;
                    return menuChoose;
                }
                if (event_input.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    SDL_Point mouse;
                    mouse.x = x;
                    mouse.y = y;
                    if (SDL_PointInRect(&mouse, &startGameRect)) {
                        menuChoose = 1;
                        menuChoosed = true;
                        return menuChoose;
                    }
                    if (SDL_PointInRect(&mouse, &exitGameRect)) {
                        menuChoose = -1;
                        menuChoosed = true;
                        return menuChoose;
                    }
                }
            }
            //fps cap
            int delta = SDL_GetTicks() - start_loop;
            if (delta < desiredDelta) {
                //printf("\n %d", desiredDelta - delta);
                SDL_Delay(desiredDelta - delta);
            }

        }
        printf("f");
        return menuChoose;
    }
};

