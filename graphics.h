//
// Created by Wyatt Chrisman on 4/7/23.
//

#ifndef M4OEP_WCHRISMA_GRAPHICS_H
#define M4OEP_WCHRISMA_GRAPHICS_H

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Button.h"

enum difficulty {
    easy,
    medium,
    hard
};

// Fill all vectors
void setNumberVectors(vector<Button> &numbers, vector<Button> &background, enum difficulty difficulty);

// Swap two elements in vector
void swap(vector<Button> &vec, int firstNum, int secondNum);

// Check if all pieces are in correct spot
void checkEnd(vector<Button> background);

// Adds all number buttons to the vectors
void initNumbers();

// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
void init();

// Initialize OpenGL Graphics
void InitGL();

// Check if square is in the correct position, if yes, set background green, otherwise keep red
void checkCorrect(vector<Button> &numbers, vector<Button> &background);

// Draw the window - this is where all the GL actions are
void display();

// Trap and process alphanumeric keyboard events
void kbd(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

// Handle "mouse cursor moved" events
void cursor(int x, int y);

// Calls itself after a specified time
void timer(int dummy);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);

#endif //M4OEP_WCHRISMA_GRAPHICS_H
