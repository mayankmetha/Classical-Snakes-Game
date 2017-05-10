//define header
#ifndef _GAME_H
#define _GAME_H

//include headers 
#include"platforms.h"
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<cmath>

//constants
#define ROWS 40 //yaxis
#define COLUMNS 40 //xaxis
#define FPS 15 //frame per seconds
#define MIN_FPS 5 //minimum FPS

//directions numbers
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

//max length of snake
#define MAX_LEN 60;

//colors
typedef float colors[3];
const colors GREY = { 0.5,0.5,0.5 };
const colors WHITE = { 1.0,1.0,1.0 };
const colors RED = { 1.0,0.0,0.0 };
const colors GREEN = { 0.0,1.0,0.0 };
const colors BLUE = { 0.0,0.0,1.0 };

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
void turnUp();
void turnDown();
void turnRight();
void turnLeft();

#endif
