#include "graphics.h"
#include "Button.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
const int totalLights = 25;
const color yellow(1,1,0);
const color red(1,0,0);
const color black(0,0,0);
int clickCounter = 0;

vector<Button> lights;


enum screen {startScreen, playScreen, endScreen};
screen activeScreen = startScreen;

point2D startPosition(800,800);

// Creates all lights and puts them into the 'lights' vector
void initNumbers() {

    double lightWidth = 65;
    double lightHeight = 65;
    double borderWidth = 75;
    double borderHeight = 75;

    double startPosition = 58.3;
    double x,y;
    double gapCenters = 95.8;

    // Get all x-coordinates and y-coordinates
    for(int i = 1; i < totalLights + 1; ++i) {

        // Loop to get all x-axis
        for(int k = 1; k < 6; ++k) {
            if((i - k) % 5 == 0) {
                x = startPosition + (gapCenters * (k-1));
            }
        }

        // Set the y-axis
        y = startPosition + ((i - 1) / 5) * gapCenters;

        // Create point with x and y and add light to vector
        point2D center(x,y);
        lights.push_back(Quad(yellow, center, lightWidth, lightHeight));
        backgroundBorder.push_back(Quad(yellow, center, borderWidth, borderHeight));
    }
}


void init() {
    width = 500;
    height = 500;
    srand(time(0));
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */

    // start screen that shows message to proceed
    if (activeScreen == startScreen) {
        string label = "Press 's' to start!";
        glColor3f(1,1,1);
        glRasterPos2i(250 - (4 * label.length()), 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if (activeScreen == playScreen) {
        for (Quad &border: backgroundBorder) {
            border.draw();
        }

        // Print all the lights onto the screen
        for (Quad &light: lights) {
            light.draw();
        }
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 115) {
        activeScreen = playScreen;
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {
    // Makes the background box red while overlapping with the background box
    for (int i = 0; i < backgroundBorder.size(); i++){
        if (backgroundBorder[i].isOverlapping(x,y)) {
            backgroundBorder[i].hover();
        }
        else {
            backgroundBorder[i].release(lights, backgroundBorder);
        }
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    //Change to clicking of the lights and changing on/off
    for (int i = 0; i < backgroundBorder.size(); i++) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && backgroundBorder[i].isOverlapping(x,y)) {
            lights[i].pressDown();
            backgroundBorder[i].pressDown();

            if (i == 0) {
                lights[i + 1].pressDown();
                lights[i + 5].pressDown();
                backgroundBorder[i + 1].pressDown();
                backgroundBorder[i + 5].pressDown();
            }
            else if (i == 1 || i == 2 || i == 3) {
                lights[i + 1].pressDown();
                lights[i - 1].pressDown();
                lights[i + 5].pressDown();
                backgroundBorder[i + 1].pressDown();
                backgroundBorder[i - 1].pressDown();
                backgroundBorder[i + 5].pressDown();
            }
            else if (i == 4) {
                lights[i - 1].pressDown();
                lights[i + 5].pressDown();
                backgroundBorder[i - 1].pressDown();
                backgroundBorder[i + 5].pressDown();
            }
            else if (i == 5 || i == 10 || i == 15) {
                lights[i + 1].pressDown();
                lights[i - 5].pressDown();
                lights[i + 5].pressDown();
                backgroundBorder[i + 1].pressDown();
                backgroundBorder[i - 5].pressDown();
                backgroundBorder[i + 5].pressDown();
            }
            else if (i == 9 || i == 14 || i == 19) {
                lights[i - 1].pressDown();
                lights[i + 5].pressDown();
                lights[i + 5].pressDown();
                backgroundBorder[i - 1].pressDown();
                backgroundBorder[i + 5].pressDown();
                backgroundBorder[i + 5].pressDown();
            }
            else if (i == 20) {
                lights[i + 1].pressDown();
                lights[i - 5].pressDown();
                backgroundBorder[i + 1].pressDown();
                backgroundBorder[i - 5].pressDown();
            }
            else if (i == 21 || i == 22 || i == 23) {
                lights[i - 1].pressDown();
                lights[i + 1].pressDown();
                lights[i - 5].pressDown();
                backgroundBorder[i - 1].pressDown();
                backgroundBorder[i + 1].pressDown();
                backgroundBorder[i - 5].pressDown();
            }
            else if (i == 24) {
                lights[i - 1].pressDown();
                lights[i - 5].pressDown();
                backgroundBorder[i - 1].pressDown();
                backgroundBorder[i - 5].pressDown();
            }
            else {
                lights[i - 1].pressDown();
                lights[i + 1].pressDown();
                lights[i - 5].pressDown();
                lights[i + 5].pressDown();
                backgroundBorder[i - 1].pressDown();
                backgroundBorder[i + 1].pressDown();
                backgroundBorder[i - 5].pressDown();
                backgroundBorder[i + 5].pressDown();
            }
            clickCounter++;
        }
    }

    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Lights Out!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // Initialize Lights
    initNumbers();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);


    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
