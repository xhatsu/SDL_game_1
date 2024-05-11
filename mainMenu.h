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
extern std::string playerName;
class mainMenu
{
    bool menuChoosed = false;
    bool nameInputFlag = true;
    SDL_Color textColorDefault = { 255,255,255 };
    SDL_Color textColorStart = { 255, 255, 255 };
    SDL_Color textColorExit = { 255, 255, 255 };
    // Create the menu items
    std::string startGame= "Start Game";
    std::string exitGame = "Exit";
    std::string welcomeNameString;
    // Render the menu items
    SDL_Rect startGameRect;
    SDL_Rect welcomeNameRect;
    SDL_Rect exitGameRect;
    SDL_Rect nameInputRect;
    SDL_Surface* textSurface=NULL;
    SDL_Texture* textTexture=NULL;
    backGround menuBackGround;
    entityControl menuEntityControl;
    mapProcess menuMapProcess;
    SDL_Event event_input;
public:
    int menuChoose = 0;
    mainMenu() {
        welcomeNameString = "ANONYMOUS";
        welcomeNameRect.x = 300;
        welcomeNameRect.y = 300;
        welcomeNameRect.w = 0;
        welcomeNameRect.h = 0;
        nameInputRect.x = 400;
        nameInputRect.y = 400;
        nameInputRect.w = 200;
        nameInputRect.h = 200;
        startGameRect.x = 300;
        startGameRect.y = 400;
        startGameRect.w = 180;
        startGameRect.h = 30;
        exitGameRect.x = 300;
        exitGameRect.y = 500;
        exitGameRect.w = 80;
        exitGameRect.h = 30;
        nameInputRect.x = (1280 - 200) / 2;
        nameInputRect.y = 0;
        nameInputRect.w = 0;
        nameInputRect.h = 0;
        menuMapProcess.getChunkList("mapData.json");
    }
    int loadMenu() {
        
        SDL_SetRenderDrawColor(renderer, 224, 251, 226, 255);
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
            if (nameInputFlag==false) {
                SDL_Rect textRect;

                //render welcome name
                std::string welcomeString = "Welcome " + welcomeNameString;
                textSurface = TTF_RenderText_Solid(pixelFont, welcomeString.c_str(), textColorDefault);
                textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                welcomeNameRect.w = textSurface->w;
                welcomeNameRect.h = textSurface->h;
                textRect = welcomeNameRect;
                SDL_FreeSurface(textSurface);
                SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
                //SDL_RenderFillRect(renderer, &startGameRect);
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);

                //render Start Game
                textSurface = TTF_RenderText_Solid(pixelFont, startGame.c_str(), textColorStart);
                textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_FreeSurface(textSurface);
                textRect = startGameRect;
                SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
                //SDL_RenderFillRect(renderer, &startGameRect);
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);

                //render exit game
                textSurface = TTF_RenderText_Solid(pixelFont, exitGame.c_str(), textColorExit);
                textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_FreeSurface(textSurface);
                textRect = exitGameRect;
                SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
                //SDL_RenderFillRect(renderer, &exitGameRect);
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);
            }
            if (nameInputFlag == true) {
                StartTextInput(nameInputRect,renderer,pixelFont);
            }
            if (playerName.size() != 0) {
                welcomeNameString = playerName;
            }
            //render to screen
            SDL_RenderPresent(renderer);
            //handle input
            while (SDL_PollEvent(&event_input)) {
                if (event_input.type == SDL_QUIT) {
                    menuChoose = -1;
                    menuChoosed = true;
                    return menuChoose;
                }
                if (event_input.type == SDL_MOUSEMOTION) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    SDL_Point mouse;
                    mouse.x = x;
                    mouse.y = y;
                    if (SDL_PointInRect(&mouse, &startGameRect)) {
                        textColorStart.r = 225;
                        textColorStart.g = 10;
                        textColorStart.b = 10;
                    }
                    else {
                        textColorStart.r = 255;
                        textColorStart.g = 255;
                        textColorStart.b = 255;
                    }
                    if (SDL_PointInRect(&mouse, &exitGameRect)) {
                        textColorExit.r = 225;
                        textColorExit.g = 10;
                        textColorExit.b = 10;
                    }
                    else {
                        textColorExit.r = 255;
                        textColorExit.g = 255;
                        textColorExit.b = 255;
                    }
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
    void StartTextInput(SDL_Rect inputRect, SDL_Renderer* renderer, TTF_Font* font) {
        SDL_Rect backgroundRect;
        backgroundRect.x = (1280 - 200) / 2;
        backgroundRect.y = inputRect.y;
        backgroundRect.w = inputRect.w;
        backgroundRect.h = inputRect.h;
        SDL_Rect nextBackGroundRect = {1280/2-100,backgroundRect.y,backgroundRect.w,backgroundRect.h};
        
        SDL_StartTextInput();
        SDL_SetTextInputRect(&inputRect);

        // The color of the text
        //SDL_Color textColor = { 255, 255, 255, 255 }; // White color
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        // The input text
        std::string inputText = "Enter Your Name Here";

        // Render the initial text
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColorDefault);
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);

        // Main loop flag
        bool quit = false;
        // first letter flag
        bool typed = false;
        // Event handler
        SDL_Event e;
        int start_loop = SDL_GetTicks64();
        // Enable text input
        SDL_StartTextInput();

        // While application is running
        while (!quit) {
            // The rerender text flag
            bool renderText = false;

            // Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                // User requests quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                // Special key input
                else if (e.type == SDL_KEYDOWN) {
                    //printf("\n enter: %d", e.key.keysym.sym);
                    // Handle backspace
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                    else if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                        // Remove character from the end
                        inputText.pop_back();
                        renderText = true;
                    }
                    else if (e.key.keysym.sym == 13) {
                        printf("xx");
                        quit = true;
                        playerName = inputText;
                    }
                    // Handle copy
                    else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(inputText.c_str());
                    }
                    // Handle paste
                    else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                        inputText = SDL_GetClipboardText();
                        renderText = true;
                    }
                }
                // Special text input event
                else if (e.type == SDL_TEXTINPUT) {
                    // Not copy or pasting
                    if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V'))) {
                        // Append character
                        if (typed == false) {
                            inputText.clear();
                            typed = true;
                        }
                        inputText += e.text.text;
                        renderText = true;
                    }
                }
            }

            // Rerender text if needed
            if (renderText||typed==false) {
                // Text is not empty
                if (inputText != "") {
                    // Render new text
                    textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColorDefault);
                }
                // Text is empty
                else {
                    // Render space texture
                    textSurface = TTF_RenderText_Solid(font, " ", textColorDefault);
                }
                // Create texture from surface pixels
                SDL_DestroyTexture(textTexture);
                textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                
            }
            //set input rect
            if (textSurface != NULL) {
                inputRect.w = textSurface->w;
                inputRect.h = textSurface->h;
                inputRect.x = (1280 - inputRect.w) / 2;
                inputRect.y = (720 - inputRect.h) / 2;
            }
            // set background text
            backgroundRect.x = inputRect.x-25;
            backgroundRect.y = inputRect.y-5;
            backgroundRect.w = inputRect.w+50;
            backgroundRect.h = inputRect.h+10;
            // render background
            menuBackGround.updateChunk(-1);
            //menuEntityControl.loadEntityList();
            menuMapProcess.updateMap(false);
            menuMapProcess.updateMap(true);
            // Render text textures
            SDL_RenderFillRect(renderer, &backgroundRect);
            SDL_RenderCopy(renderer, textTexture, NULL, &inputRect);

            // Update screen
            SDL_RenderPresent(renderer);
            int delta = SDL_GetTicks() - start_loop;
            if (delta < desiredDelta) {
                printf("\n %d", desiredDelta - delta);
                SDL_Delay(desiredDelta - delta);
            }
        }

        // Disable text input
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        SDL_StopTextInput();
        nameInputFlag = false;
    }
};

