#ifndef _PLATFORMS_H
#define _PLATFORMS_H


#ifdef __APPLE__
//APPLE macOS 10.7 upwards
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#elif defined _WIN32
//WIN 32bit and 64bit
#include<GL/glut.h>
#elif defined __linux__
//freeGlut on linux
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#endif

#endif