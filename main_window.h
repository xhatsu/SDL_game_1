#pragma once
#include<SDL.h>
#include<stdio.h>
#include<SDL_image.h>>
extern SDL_Window* main_window;
extern SDL_Renderer* renderer;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
void close_window();
bool InitWindow();