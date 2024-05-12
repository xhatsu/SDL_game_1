#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"map_process.h"
#include"background.h"
#include"playerScore.h"
#include"entity_control.h"
#include<vector>
extern void renderTransparentBlackRectangle(SDL_Renderer* renderer, SDL_Rect const& rect, int alpha);
extern TTF_Font* pixelFont;
extern SDL_Renderer* renderer;
extern int desiredDelta;
extern std::string playerName;
extern std::vector<playerScore> leaderBoardList;
class mainMenu
{   
    bool menuChoosed = false;
    bool nameInputFlag = true;
    SDL_Color textColorDefault = { 255,66,0 };
    SDL_Color textColorStart = { 255, 255, 255 };
    SDL_Color textColorExit = { 255, 255, 255 };
    // Create the menu items
    std::string startGame= "Start Game";
    std::string exitGame = "Exit";
    std::string welcomeNameString;
    // Render the menu items
    SDL_Rect leaderBoardRect;
    SDL_Rect startGameRect;
    SDL_Rect welcomeNameRect;
    SDL_Rect exitGameRect;
    SDL_Rect nameInputRect;
    SDL_Surface* textSurface=NULL;
    SDL_Texture* textTexture=NULL;
    backGround menuBackGround;
    entityControl menuEntityControl;
    mapProcess menuMapProcess;
public:
    int menuChoose = 0;
    mainMenu() {
        printf("\n main menu class init");
        welcomeNameString = "ANONYMOUS";
        welcomeNameRect.x = 250;
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
        printf("\n dd");
        menuMapProcess.getChunkList("mapData.json");
        printf("mapData loaded");
        leaderBoardRect.x = 800;
        leaderBoardRect.y = 150;
        leaderBoardRect.w = 400;
        leaderBoardRect.h = 400;
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
            SDL_SetRenderDrawColor(renderer, 224, 251, 226, 255);
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
                std::string welcomeString = "Welcome " + welcomeNameString + " to Hunt 2D";
                textSurface = TTF_RenderText_Blended(pixelFont, welcomeString.c_str(), textColorDefault);
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
                textSurface = TTF_RenderText_Blended(pixelFont, startGame.c_str(), textColorStart);
                textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_FreeSurface(textSurface);
                textRect = startGameRect;
                SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
                //SDL_RenderFillRect(renderer, &startGameRect);
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);

                //render exit game
                textSurface = TTF_RenderText_Blended(pixelFont, exitGame.c_str(), textColorExit);
                textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_FreeSurface(textSurface);
                textRect = exitGameRect;
                SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
                //SDL_RenderFillRect(renderer, &exitGameRect);
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);
                //render leader board
                renderTransparentBlackRectangle(renderer, leaderBoardRect, 128);
                std::string leaderBoardtext = "Leader Board";
                textSurface = TTF_RenderText_Blended(pixelFont, leaderBoardtext.c_str(), textColorDefault);
                textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_FreeSurface(textSurface);
                SDL_Rect temp;
                temp.x = leaderBoardRect.x+20;
                temp.y = leaderBoardRect.y+20;
                temp.w = textSurface->w;
                temp.h = textSurface->h;
                SDL_QueryTexture(textTexture, NULL, NULL, &temp.w, &temp.h);
                //SDL_RenderFillRect(renderer, &exitGameRect);
                SDL_RenderCopy(renderer, textTexture, NULL, &temp);
                SDL_DestroyTexture(textTexture);
                //render leader board item
                int currentY = leaderBoardRect.y+100; // Y position to start drawing text
                for (int i = 0; i < leaderBoardList.size(); i++) {
                    // Create surface from the text
                    SDL_Color textColor = { 255,255,255 };
                    std::string text = std::to_string(i+1) + ".  " + leaderBoardList.at(i).playerName +"  "+ std::to_string(leaderBoardList.at(i).maxLevel);
                    SDL_Surface* surface = TTF_RenderText_Blended(pixelFont, text.c_str(), textColor);
                    if (surface == nullptr) {
                        SDL_Log("Unable to create text surface: %s\n", TTF_GetError());
                        continue;
                    }

                    // Create texture from the surface
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                    if (texture == nullptr) {
                        SDL_Log("Unable to create texture from surface: %s\n", SDL_GetError());
                        SDL_FreeSurface(surface);
                        continue;
                    }

                    // Set the rendering space and render the text
                    SDL_Rect renderQuad = { leaderBoardRect.x+20, currentY, surface->w, surface->h };
                    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

                    // Update the Y position for the next line of text
                    currentY +=  surface->h+20;

                    // Clean up the surface and texture
                    SDL_FreeSurface(surface);
                    SDL_DestroyTexture(texture);
                }
            }
            if (nameInputFlag == true) {
                StartTextInput(nameInputRect,renderer,pixelFont);
            }
            if (playerName.size() != 0) {
                welcomeNameString = playerName;
            }
            else {
            }
            //render to screen
            SDL_RenderPresent(renderer);
            //handle input
            SDL_Event event_input;
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
        textSurface = TTF_RenderText_Blended(font, inputText.c_str(), textColorDefault);
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
            while (SDL_WaitEvent(&e) != 0) {
                // User requests quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                    menuChoose = -1;
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
                        printf( inputText.c_str());
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
                            inputText="";
                            typed = true;
                        }
                        inputText += e.text.text;
                        renderText = true;
                    }
                }
            }
            if (quit == true) {
                printf(inputText.c_str());
            }
            textSurface = TTF_RenderText_Blended(font, inputText.c_str(), textColorDefault);
            SDL_DestroyTexture(textTexture);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            //set input rect
            if (true) {
                inputRect.w = textSurface->w;
                inputRect.h = textSurface->h;
                inputRect.x = (1280 - inputRect.w) / 2;
                inputRect.y = (720 - inputRect.h) / 2;
            }
            SDL_FreeSurface(textSurface);
            textSurface = NULL;
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
            //SDL_RenderFillRect(renderer, &backgroundRect);
            renderTransparentBlackRectangle(renderer, backgroundRect, 135);
            SDL_RenderCopy(renderer, textTexture, NULL, &inputRect);
            SDL_DestroyTexture(textTexture);
            // Update screen
            SDL_RenderPresent(renderer);
            int delta = SDL_GetTicks() - start_loop;
            if (delta < desiredDelta) {
                printf("\n %d", desiredDelta - delta);
                SDL_Delay(desiredDelta - delta);
            }
        }
        // Disable text input
        printf("fa");
        if (textSurface != NULL) { SDL_FreeSurface(textSurface); }
        SDL_DestroyTexture(textTexture);
        SDL_StopTextInput();
        nameInputFlag = false;
    }
};

