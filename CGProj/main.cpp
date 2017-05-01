//headers
#include"game.h"

// display axis
// y
// ^
// |
// |
//  ------->x

//constants
#define ROWS 40 //yaxis
#define COLUMNS 40 //xaxis
#define FPS 12 //frame per seconds
#define MIN_FPS 5 //minimum FPS

//variables
extern short sDir;
bool gameOver = false;
bool gamePause = false;
bool gameWelcome = false;
int score;
int fps;

// initalze the program
void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initGrid(ROWS,COLUMNS);
    initGame();
    gameWelcome = true;
}

//timer function for animation fps
void myTimer(int) {
    glutPostRedisplay();
    //increase fps by one unit after score increaases by 5
    if (score/5!=0 && score!=0) {
        fps = MIN_FPS + (score / 5);
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
            if (sDir != DOWN)
                sDir = UP;
            break;
        case GLUT_KEY_DOWN:
            if (sDir != UP)
                sDir = DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if (sDir != LEFT)
                sDir = RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if (sDir != RIGHT)
                sDir = LEFT;
            break;
    }
}

//keyboard alphanumeric
void myKeyboard(unsigned char key, int, int) {
    switch (key) {
            //start
        case 's':
        case 'S':
            gameWelcome = false;
            break;
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
    }
}

//main()
int main(int argc, char **argv) {
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
