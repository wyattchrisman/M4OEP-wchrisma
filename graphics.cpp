#include "graphics.h"
#include "Button.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;

enum screen {startScreen,
    easyScreen,
    mediumScreen,
    hardScreen,
    endScreen};
screen activeScreen = startScreen;

const color red (1,0,0);
const color blue(0, 0, 1);
const color green(0, 1, 0);

int clickCounter = 0;

vector<Button> numberBoxesEasy;
vector<Button> backgroundBoxEasy;
vector<Button> numberBoxesMedium;
vector<Button> backgroundBoxMedium;
vector<Button> numberBoxesHard;
vector<Button> backgroundBoxHard;




void setNumberVectors(vector<Button> &numbers, vector<Button> &background, enum difficulty difficulty) {
    int totalBoxes;
    double backgroundBoxHeight;

    if(difficulty == easy) {
        totalBoxes = 9;
        backgroundBoxHeight = 95;
    }
    if(difficulty == medium) {
        totalBoxes = 16;
        backgroundBoxHeight = 85;
    }
    if(difficulty == hard) {
        totalBoxes = 25;
        backgroundBoxHeight = 75;
    }

    int squareRootBoxes = sqrt(totalBoxes);
    double backgroundBoxWidth = backgroundBoxHeight;
    double boxWidth = backgroundBoxHeight - 10;
    double boxHeight = boxWidth;
    double x,y;

    double startBox = ((width - (backgroundBoxHeight * squareRootBoxes)) / (squareRootBoxes + 1)) + (backgroundBoxHeight/2);
    double gapCenters = startBox + backgroundBoxHeight/2;


    // Get all x-coordinates and y-coordinates
    for(int i = 1; i < totalBoxes + 1; ++i) {

        // Loop to get all x-axis
        for(int k = 1; k < sqrt(totalBoxes)+1; ++k) {
            if((i - k) % squareRootBoxes == 0) {
                x = startBox + (gapCenters * (k-1));
            }
        }

        // Set the y-axis
        y = startBox + ((i - 1) / squareRootBoxes) * gapCenters;

        // Create point with x and y and add light to vector
        point2D center(x,y);
        if(i < totalBoxes) {
            numbers.push_back(Button(blue, center, boxWidth, boxHeight, to_string(i)));
            background.push_back(Button(red, center, backgroundBoxWidth, backgroundBoxHeight, to_string(i)));
        } else {
            numbers.push_back(Button(blue, center, boxWidth, boxHeight, " "));
            background.push_back(Button(red, center, backgroundBoxWidth, backgroundBoxHeight, " "));
        }
    }
}


// Creates all numbers and puts them into the corresponding 'numbers' vector
void initNumbers() {
    setNumberVectors(numberBoxesEasy, backgroundBoxEasy, easy);
    setNumberVectors(numberBoxesMedium, backgroundBoxMedium, medium);
    setNumberVectors(numberBoxesHard, backgroundBoxHard, hard);

    glutPostRedisplay();
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

void checkCorrect(vector<Button> &numbers, vector<Button> &background){
    for(int i = 0; i < numbers.size(); ++i) {
        if(numbers[i].label == background[i].label) {
            background[i].setColor(green);
        } else {
            background[i].setColor(red);
        }
    }
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
        string label = "Welcome to slide puzzle!";// This is a game where you will get a set of numbers in a grid pattern based on your chosen difficulty.  You will need to arrange the numbers in descending order from left to right and top down.";
        glColor3f(1,1,1);
        glRasterPos2i(250 - (4 * label.length()), 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if(activeScreen == easyScreen) {
        // Print all the boxes onto the screen
        for (Button &easyBox: backgroundBoxEasy) {
            easyBox.draw();
        }

        for (Button &easyBox: numberBoxesEasy) {
            easyBox.draw();
        }
        checkCorrect(numberBoxesEasy, backgroundBoxEasy);
    }

    if(activeScreen == mediumScreen) {
        // Print all the boxes onto the screen
        for (Button &mediumBox: backgroundBoxMedium) {
            mediumBox.draw();
        }

        for (Button &mediumBox: numberBoxesMedium) {
            mediumBox.draw();
        }
        checkCorrect(numberBoxesMedium, backgroundBoxMedium);
    }

    if(activeScreen == hardScreen) {
        // Print all the boxes onto the screen
        for (Button &hardBox: backgroundBoxHard) {
            hardBox.draw();
        }

        for (Button &hardBox: numberBoxesHard) {
            hardBox.draw();
        }
        checkCorrect(numberBoxesHard, backgroundBoxHard);
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

    // Go to screen corresponding with the difficulty
    if(activeScreen == startScreen) {
        if (key == 69 || key == 101) {
            activeScreen = easyScreen;
        }

        if (key == 77 || key == 109) {
            activeScreen = mediumScreen;
        }

        if (key == 72 || key == 104) {
            activeScreen = hardScreen;
        }
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
    for (int i = 0; i < numberBoxesEasy.size(); i++){
        if (numberBoxesEasy[i].isOverlapping(x,y)) {
            numberBoxesEasy[i].hover();
        }
        else {
            numberBoxesEasy[i].release();
        }
    }

    for (int i = 0; i < numberBoxesMedium.size(); i++){
        if (numberBoxesMedium[i].isOverlapping(x,y)) {
            numberBoxesMedium[i].hover();
        }
        else {
            numberBoxesMedium[i].release();
        }
    }

    for (int i = 0; i < numberBoxesHard.size(); i++){
        if (numberBoxesHard[i].isOverlapping(x,y)) {
            numberBoxesHard[i].hover();
        }
        else {
            numberBoxesHard[i].release();
        }
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    // TODO: Change to select box
    for (int i = 0; i < numberBoxesHard.size(); i++) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && numberBoxesEasy[i].isOverlapping(x,y)) {
            numberBoxesEasy[i].pressDown();
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && numberBoxesMedium[i].isOverlapping(x,y)) {
            numberBoxesMedium[i].pressDown();
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && numberBoxesHard[i].isOverlapping(x,y)) {
            numberBoxesHard[i].pressDown();
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
    wd = glutCreateWindow("Slide Puzzle!" /* title */ );

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
