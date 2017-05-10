//header
#include"game.h"

//variables
int gridX, gridY; //grid lines
extern short sDir; //snake motion animation
extern bool sDirFlag; //snake direction keyboard flag
int snake_length;//snake length
int posX[60], posY[60]; //snake initial position
extern bool gameOver; //gameOver flag
extern bool gamePause; //gamePause flag
bool food; //place food or not
int foodX, foodY; // food position
extern int score; //score
char text[50]; //score string
extern int fps; //animations frame rate
extern bool hiddenFlag; //easter Egg flag

//init game variables
void initGame() {
	fps = MIN_FPS;
	score = 0;
	sDir = RIGHT;
	sDirFlag = true;
	snake_length = 5;
	for (int i = 0; i < snake_length; i++) {
		posX[i] = 20;
		posY[i] = 20 - i;
	}
	food = true;
}

//initalize the grid
void initGrid(int rows, int columns) {
	gridX = columns;
	gridY = rows;
}

//draw grid cell
void drawCell(int x, int y, float thickness) {
	glLineWidth(thickness);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x, y);
	glVertex2d(x + 1, y);
	glVertex2d(x + 1, y + 1);
	glVertex2d(x, y + 1);
	glEnd();
}
//draw grid
void gridUnit(int x, int y) {
	if (hiddenFlag && !gamePause && !gameOver) {
		glColor3fv(GREY);
		drawCell(x, y, 1.0);
	}
	//red border
	if ((x == 0 || x == gridX - 1 || y == 0 || y == gridY - 1)) {
		glColor3fv(RED);
		drawCell(x, y, 3.0);
	}

}

// draw cells to form grid
void drawGrid() {
	for (int x = 0; x < gridX; x++) {
		for (int y = 0; y < gridY; y++) {
			gridUnit(x, y); 
		}
	}
}

//draw food
void drawFood() {
	//get new location
	if (food) {
		random(foodX, foodY);
		//is food at same loc with snake body then redraw at new location
		for (int i = 0; i < snake_length; i++) {
			for (int j = 0; j < snake_length; j++) {
				if (foodX == posX[i] && foodY == posY[j])
					drawFood();
			}

		}
	}
	food = false;
	//food color
	glColor3fv(BLUE);
	//draw food rectangle
	glRectd(foodX, foodY, foodX + 1, foodY + 1);
}

//2 random number generator
void random(int &x, int &y) {
	//range 
	int minX = 1;
	int maxX = gridX - 2;
	int minY = 1;
	int maxY = gridY - 2;
	x = minX + rand() % (maxX - minX);
	y = minY + rand() % (maxY - minY);
}

//draw snake
void drawSnake() {
	if (!gamePause) {
		//body location without head
		for (int i = snake_length - 1; i > 0; i--) {
			posX[i] = posX[i - 1];
			posY[i] = posY[i - 1];
		}
		//snake direction change on key input and enable keyboard
		switch (sDir) {
		case UP:
			posY[0]++;
			sDirFlag = true;
			break;
		case DOWN:
			posY[0]--;
			sDirFlag = true;
			break;
		case RIGHT:
			posX[0]++;
			sDirFlag = true;
			break;
		case LEFT:
			posX[0]--;
			sDirFlag = true;
			break;
		}
	}

	//draw body segments
	for (int i = 0; i < snake_length; i++) {
		glColor3fv(GREEN);
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
	}

	if (!gamePause) {
		//collision detection with border
		if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1) {
			glColor3fv(RED);
			glRectd(posX[0], posY[0], posX[0] + 1, posY[0] + 1);
			makeGameOver();
		}
		//collison with own body
		for (int i = 1; i < snake_length; i++) {
			if (posY[0] == posY[i] && posX[0] == posX[i]) {
				glColor3fv(RED);
				glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
				makeGameOver();
			}
		}
		//collision with food
		if (posX[0] == foodX && posY[0] == foodY) {
			snake_length++;
			if (snake_length >= 60)
				snake_length = MAX_LEN;
			food = true;
			score++;
		}
	}
}

//game over engine
void makeGameOver() {
	gameOver = true;
	gamePause = true;
}

//stroke text generator
void drawStrings(char *str, float sx, float sy, float tx, float ty,float thickness) {
	glColor3fv(WHITE);
	glPushMatrix();
	glScalef(sx, sy,0);
	glTranslatef(tx, ty, 0);
	for (int i = 0; str[i] != '\0'; i++) {
		glLineWidth(thickness);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

//print score string
void getScoreString() {
    sprintf(text, "%s%d", (char*)"SCORE : ", score);
	drawStrings(text, 0.02, 0.02, 60, 70,2.0);
}

//render game screen
void renderGame() {
	drawGrid();
	drawFood();
	drawSnake();
}

//render welcome screen
void renderWelcome() {
	drawStrings((char*)"CLASSICAL SNAKES", 0.03, 0.03, 30, 1200,1.5);
	drawStrings((char*)"GRAPHICS PROJECT", 0.02, 0.02, 40, 1600,1.5);
	drawStrings((char*)"PRESS S TO START GAME", 0.01, 0.01, 100, 2600,1.2);
	drawStrings((char*)"PRESS P TO PAUSE GAME", 0.01, 0.01, 100, 2400,1.2);
	drawStrings((char*)"PRESS Q TO QUIT GAME", 0.01, 0.01, 100, 2200,1.2);
	drawStrings((char*)"USE ARROW KEYS OR W,S,A,D AS GAME CONTROLS", 0.01, 0.01, 100, 2000,1.2);
	drawStrings((char*)"AUTHOR : MAYANK METHA D", 0.015, 0.015, 60, 800,1.5);
	drawStrings((char*)"USN : 1MV14CS054", 0.015, 0.015, 60, 600,1.5);
}

//render pause screen
void renderPause() {
	drawGrid();
	drawFood();
	drawSnake();
	drawStrings((char*)"GAME PAUSED", 0.03, 0.03, 190, 1100,1.5);
	drawStrings((char*)"PRESS P TO UNPAUSE", 0.015, 0.015, 300, 1600, 1.5);
	getScoreString();
}

//render exit screen
void renderExit() {
	drawGrid();
	drawFood();
	drawSnake();
	drawStrings((char*)"GAME OVER", 0.03, 0.03, 220, 1100,1.5);
	drawStrings((char*)"PRESS Q TO QUIT", 0.015, 0.015, 300, 1600,1.5);
	drawStrings((char*)"PRESS N TO RESTART", 0.015, 0.015, 300, 1400,1.5);
	getScoreString();
}

//turn up
void turnUp() {
	if (sDir != DOWN && sDirFlag == true) {
		sDir = UP;
		sDirFlag = false;
	}
}

//turn down
void turnDown() {
	if (sDir != UP && sDirFlag == true) {
		sDir = DOWN;
		sDirFlag = false;
	}
}

//turn right
void turnRight() {
	if (sDir != LEFT && sDirFlag == true) {
		sDir = RIGHT;
		sDirFlag = false;
	}
}

//turn left
void turnLeft() {
	if (sDir != RIGHT && sDirFlag == true) {
		sDir = LEFT;
		sDirFlag = false;
	}
}
