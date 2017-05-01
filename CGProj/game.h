//define header
#ifndef _GAME_H
#define _GAME_H

//include headers 
#include"platforms.h"
#include<stdio.h>
#include<stdlib.h>
#include<cstring>

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define MAX_LEN 60;

//sharable functions
void initGame();
void initGrid(int, int);
void drawGrid();
void drawSnake();
void drawFood();
void makeGameOver();
void random(int&, int&);
void renderWelcome();
void renderGame();
void renderPause();
void renderExit();
#endif
