//headers
#include"game.h"

// display axis
// y
// ^
// |
// |
//  ------->x

//variables
short sDir; // snake direction
bool gameOver = false; //game over flag
bool gamePause = false; //game pause flag
bool gameWelcome = false; //game before start flag
int score; // score of game
int fps; // frame rate of game
bool sDirFlag = true; // snake direction change input flag
bool hiddenFlag = false; //easter egg
int easterEgg; // easterFlag enables only when H key is hit 5 times

// initalze the program
void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initGrid(ROWS,COLUMNS);
    initGame();
    gameWelcome = true;
	easterEgg = 5;
}

//timer function for animation fps
void myTimer(int) {
    glutPostRedisplay();
    //increase fps by one unit after score increaases by 5
    if (score%5==0 && score!=0) {
        fps = MIN_FPS + floor(score / 5);
        if (fps > FPS) fps = FPS;
    }
    glutTimerFunc(1000 / fps, myTimer, 0);
}

//display function
void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    //Welcome screen
    if (gameWelcome && !gamePause && !gameOver) {
        renderWelcome();
    }
    //Game screen
    else if (!gameWelcome && !gamePause && !gameOver) {
        renderGame();
    }
    //Pause Screen
    else if (!gameWelcome && gamePause && !gameOver) {
        renderPause();
    }
    //Exit Screen
    else if (gameOver && !gameWelcome) {
        renderExit();
    }
    glFlush();
    glutSwapBuffers();
}

//scaling & transform screen function
void myReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//keyboard special key
void mySpecialKeyboard(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
			if (!gameOver && !gamePause && !gameWelcome)
				turnUp();
            break;
        case GLUT_KEY_DOWN:
			if (!gameOver && !gamePause && !gameWelcome)
				turnDown();
            break;
        case GLUT_KEY_RIGHT:
			if (!gameOver && !gamePause && !gameWelcome)
				turnRight();
            break;
        case GLUT_KEY_LEFT:
			if (!gameOver && !gamePause && !gameWelcome)
				turnLeft();
            break;
    }
}

//keyboard alphanumeric
void myKeyboard(unsigned char key, int, int) {
    switch (key) {
        //restart after game over
        case 'n':
        case 'N':
            if (gameOver) {
                initGame();
                gameOver = !gameOver;
                gamePause = !gamePause;
                gameWelcome = true;
            }
            break;
        //pause
        case 'p':
        case 'P':
            if(!gameOver && !gameWelcome)
                gamePause = !gamePause;
            break;
        //exit
        case 'q':
        case 'Q':
            if (!gameOver && !gameWelcome)
                makeGameOver();
            else 
                exit(0);
            break;
		//turn up
		case 'w':
		case 'W':
			if (!gameOver && !gamePause && !gameWelcome)
				turnUp();
			break;
		//start and turn down
		case 's':
		case 'S':
			if(gameWelcome)
				gameWelcome = false;
			else if (!gameOver && !gamePause && !gameWelcome)
				turnDown();
			break;
		//turn left
		case 'a':
		case 'A':
			if (!gameOver && !gamePause && !gameWelcome)
				turnLeft();
			break;
		//turn right
		case 'd':
		case 'D':
			if (!gameOver && !gamePause && !gameWelcome)
				turnRight();
			break;
		//easterEgg flag enable if count 0 or easterEgg--;
		case 'h':
		case 'H':
			if (easterEgg > 1)
				easterEgg--;
			else if (easterEgg == 1) {
				easterEgg--;
				hiddenFlag = true;
			}
			else hiddenFlag = !hiddenFlag;
			break;
    }
}

//main()
int main(int argc, char **argv) {
	srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Classical Snakes");
    glutPositionWindow(500, 100);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutTimerFunc(0,myTimer,0);
    glutSpecialFunc(mySpecialKeyboard);
    glutKeyboardFunc(myKeyboard);
    myInit();
    glutMainLoop();
    return 0;
}
