#include "graphics.h"
#include "Button.h"
#include <time.h>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;

// Create enum for all screens
enum screen {startScreen,
    easyScreen,
    mediumScreen,
    hardScreen,
    endScreen};
screen activeScreen = startScreen;

// Create all colors used
const color red (1,0,0);
const color blue(0, 0, 1);
const color green(0, 1, 0);

// Create move count
int moveCount = 0;

// Variables for time
time_t startTime;
time_t endTime;

// Create vectors for all game modes
vector<Button> numberBoxesEasy;
vector<Button> backgroundBoxEasy;
vector<Button> numberBoxesMedium;
vector<Button> backgroundBoxMedium;
vector<Button> numberBoxesHard;
vector<Button> backgroundBoxHard;

// Fill given vectors with all their numbers and respective background based on difficulty
void setNumberVectors(vector<Button> &numbers, vector<Button> &background, enum difficulty difficulty) {
    // Vector for numbers to be chosen from
    vector<int> nums;

    // Create needed variables
    int totalBoxes;
    double backgroundBoxHeight;

    // Add nums needed for respective game difficulties
    if(difficulty == easy) {
        totalBoxes = 9;
        backgroundBoxHeight = 95;
        for(int i = 1; i < totalBoxes; ++i) {
            nums.push_back(i);
        }
    }
    if(difficulty == medium) {
        totalBoxes = 16;
        backgroundBoxHeight = 85;
        for(int i = 1; i < totalBoxes; ++i) {
            nums.push_back(i);
        }
    }
    if(difficulty == hard) {
        totalBoxes = 25;
        backgroundBoxHeight = 75;
        for(int i = 1; i < totalBoxes; ++i) {
            nums.push_back(i);
        }
    }

    // Create all variables needed to create each box
    int squareRootBoxes = sqrt(totalBoxes);
    double backgroundBoxWidth = backgroundBoxHeight;
    double boxWidth = backgroundBoxHeight - 10;
    double boxHeight = boxWidth;
    double x,y;

    // Set start coordinate for first box
    double startBox = ((width - (backgroundBoxHeight * squareRootBoxes)) / (squareRootBoxes + 1)) + (backgroundBoxHeight/2);
    // Get gap between the centers of boxes
    double gapCenters = startBox + backgroundBoxHeight/2;

    // Get all x-coordinates and y-coordinates and add button to vector
    for(int i = 1; i < totalBoxes + 1; ++i) {

        // Loop to get all x-axis
        for(int k = 1; k < sqrt(totalBoxes)+1; ++k) {
            if((i - k) % squareRootBoxes == 0) {
                x = startBox + (gapCenters * (k-1));
                break;
            }
        }

        // Set the y-axis
        y = startBox + ((i - 1) / squareRootBoxes) * gapCenters;


        // Create point with x and y and add light to vector
        point2D center(x,y);
        if(i < totalBoxes) {
            // Get rand number for each number
            int randNum = rand() % nums.size();
            int numToAdd = nums[randNum];
            remove(nums.begin(),nums.end(), numToAdd);
            nums.resize(nums.size()-1);

            // Add to vector
            numbers.push_back(Button(blue, center, boxWidth, boxHeight, to_string(numToAdd)));
            background.push_back(Button(red, center, backgroundBoxWidth, backgroundBoxHeight, to_string(i)));
        } else {
            // Add last box as blank
            numbers.push_back(Button(blue, center, boxWidth, boxHeight, ""));
            background.push_back(Button(red, center, backgroundBoxWidth, backgroundBoxHeight, ""));
        }
    }
}

void swap(vector<Button> &vec, int firstNum, int secondNum){
    // Create temp and set all values to first num
    Button temp;

    // Swap labels for buttons
    temp.label = vec[firstNum].label;
    vec[firstNum].label = vec[secondNum].label;
    vec[secondNum].label = temp.label;
    ++moveCount;
}

// Check if the game is over by checking if there are 0 incorrect boxes
void checkEnd(vector<Button> background) {
    int incorrectCount = 0;
    for(int i = 0; i < background.size(); ++i) {
        if(background[i].getRed() == 1) {
            ++incorrectCount;
        }
    }
    if(incorrectCount == 0) {
        activeScreen = endScreen;
        time(&endTime);
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
    int numCorrect;
    for(int i = 0; i < numbers.size(); ++i) {
        if(numbers[i].label == background[i].label) {
            background[i].setColor(green);
            ++numCorrect;
            if(numCorrect == numbers.size()){
                activeScreen = endScreen;
            }
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
        // Add instructions and print to screen
        string label = "Welcome to slide puzzle!";
        string label2 = "This is a game where you will get a set of numbers in";
        string label3 = "a grid pattern based on your chosen difficulty.";
        string label4 = "You will need to arrange the numbers in descending order";
        string label5 = "from left to right and top down. ";
        string label6 = "You will use your left, right, up and down arrows";
        string label7 = "To move the blank box around your screen.";
        string label8 = "You will choose from easy: (3x3), medium: (4x4) or hard: (5x5)";
        string label9 = "Enter 'e' for easy, 'm' for medium, or 'h' for hard.";
        glColor3f(1,1,1);
        glRasterPos2i(250 - (4 * label.length()), 50);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(130 - (4 * label.length()), 100);
        for (const char &letter : label2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(150 - (4 * label.length()), 150);
        for (const char &letter : label3) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(120 - (4 * label.length()), 200);
        for (const char &letter : label4) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(220 - (4 * label.length()), 250);
        for (const char &letter : label5) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(150 - (4 * label.length()), 300);
        for (const char &letter : label6) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(180 - (4 * label.length()), 350);
        for (const char &letter : label7) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(100 - (4 * label.length()), 400);
        for (const char &letter : label8) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(140 - (4 * label.length()), 450);
        for (const char &letter : label9) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if(activeScreen == easyScreen) {
        // Print out active number of moves
        string movesLabel = "Number of moves: " + to_string(moveCount);
        glColor3f(1,1,1);
        glRasterPos2i(10,15);
        for (const char &letter : movesLabel) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // Print all the boxes onto the screen
        for (Button &easyBox: backgroundBoxEasy) {
            easyBox.draw();
        }

        for (Button &easyBox: numberBoxesEasy) {
            easyBox.draw();
        }
        // Check if game is over
        checkCorrect(numberBoxesEasy, backgroundBoxEasy);
    }

    if(activeScreen == mediumScreen) {
        // Print out active number of moves
        string movesLabel = "Number of moves: " + to_string(moveCount);
        glColor3f(1,1,1);
        glRasterPos2i(10,15);
        for (const char &letter : movesLabel) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // Print all the boxes onto the screen
        for (Button &mediumBox: backgroundBoxMedium) {
            mediumBox.draw();
        }

        for (Button &mediumBox: numberBoxesMedium) {
            mediumBox.draw();
        }
        // Check if game is over
        checkCorrect(numberBoxesMedium, backgroundBoxMedium);
    }

    if(activeScreen == hardScreen) {
        // Print out active number of moves
        string movesLabel = "Number of moves: " + to_string(moveCount);
        glColor3f(1,1,1);
        glRasterPos2i(10,15);
        for (const char &letter : movesLabel) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // Print all the boxes onto the screen
        for (Button &hardBox: backgroundBoxHard) {
            hardBox.draw();
        }

        for (Button &hardBox: numberBoxesHard) {
            hardBox.draw();
        }
        // Check if game is over
        checkCorrect(numberBoxesHard, backgroundBoxHard);
    }

    if(activeScreen == endScreen) {
        // Calculate time taken and print winning statements
        long totalTime = (endTime - startTime);
        string label = "YOU WIN! It took you " + to_string(moveCount) + " moves to complete!";
        string label2 = "It took " + to_string(totalTime) + " seconds to finish!";
        glColor3f(1,1,1);
        glRasterPos2i(250 - (4 * label.length()), 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        glRasterPos2i(250 - (4 * label.length()), 200);
        for (const char &letter : label2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
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

    // Go to screen corresponding with the difficulty
    if(activeScreen == startScreen) {
        if (key == 69 || key == 101) {
            activeScreen = easyScreen;
            time(&startTime);
        }

        if (key == 77 || key == 109) {
            activeScreen = mediumScreen;
            time(&startTime);
        }

        if (key == 72 || key == 104) {
            activeScreen = hardScreen;
            time(&startTime);
        }
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    int swapNum;

    bool swapped = false;
    if(activeScreen == easyScreen) {
       swapNum = 3;
       swapped = false;
       for(int i = 0; i < numberBoxesEasy.size(); ++i) {
           switch(key) {
               case GLUT_KEY_DOWN:
                   if(numberBoxesEasy[i].label == "" && !swapped && i != 6 && i != 7 && i != 8){
                       swap(numberBoxesEasy, i, i+swapNum);
                       swapped = true;
                       break;
                   }
                   else {break;}
               case GLUT_KEY_LEFT:
                   if(numberBoxesEasy[i].label == "" && i != 0 && i != 3 && i != 6){
                       swap(numberBoxesEasy, i, i-1);
                       break;
                   }
                   else {break;}
               case GLUT_KEY_RIGHT:
                   if(numberBoxesEasy[i].label == "" && !swapped && i != 2 && i != 5 && i != 8){
                       swap(numberBoxesEasy, i, i+1);
                       swapped = true;
                       break;
                   }
                   else {break;}
               case GLUT_KEY_UP:
                   if(numberBoxesEasy[i].label == "" && i != 0 && i != 1 && i != 2){
                       swap(numberBoxesEasy, i, i-swapNum);
                       break;
                   }
                   else {break;}
           }
       }
       checkEnd(backgroundBoxEasy);
    } else if(activeScreen == mediumScreen) {
        swapNum = 4;
        swapped = false;
        for(int i = 0; i < numberBoxesMedium.size(); ++i) {
            switch(key) {
                case GLUT_KEY_DOWN:
                    if(numberBoxesMedium[i].label == "" && !swapped && i != 12 && i != 13 && i != 14 && i != 15){
                        swap(numberBoxesMedium, i, i+swapNum);
                        swapped = true;
                        break;
                    }
                    else {break;}
                case GLUT_KEY_LEFT:
                    if(numberBoxesMedium[i].label == "" && i != 0 && i != 4 && i != 8 && i != 12){
                        swap(numberBoxesMedium, i, i-1);
                        break;
                    }
                    else {break;}
                case GLUT_KEY_RIGHT:
                    if(numberBoxesMedium[i].label == "" && !swapped && i != 3 && i != 7 && i != 11 && i != 15){
                        swap(numberBoxesMedium, i, i+1);
                        swapped = true;
                        break;
                    }
                    else {break;}
                case GLUT_KEY_UP:
                    if(numberBoxesMedium[i].label == "" && i != 0 && i != 1 && i != 2 && i != 3){
                        swap(numberBoxesMedium, i, i-swapNum);
                        break;
                    }
                    else {break;}
            }
        }
        checkEnd(backgroundBoxMedium);
    } else {
        swapNum = 5;
        swapped = false;
        for(int i = 0; i < numberBoxesHard.size(); ++i) {
            switch(key) {
                case GLUT_KEY_DOWN:
                    if(numberBoxesHard[i].label == "" && !swapped && i != 20 && i != 21 && i != 22 && i != 23 && i != 24){
                        swap(numberBoxesHard, i, i+swapNum);
                        swapped = true;
                        break;
                    }
                    else {break;}
                case GLUT_KEY_LEFT:
                    if(numberBoxesHard[i].label == "" && i != 0 && i != 5 && i != 10 && i != 15 && i != 20){
                        swap(numberBoxesHard, i, i-1);
                        break;
                    }
                    else {break;}
                case GLUT_KEY_RIGHT:
                    if(numberBoxesHard[i].label == "" && !swapped && i != 4 && i != 9 && i != 14 && i != 19 && i != 24){
                        swap(numberBoxesHard, i, i+1);
                        swapped = true;
                        break;
                    }
                    else {break;}
                case GLUT_KEY_UP:
                    if(numberBoxesHard[i].label == "" && i != 0 && i != 1 && i != 2 && i != 3 && i != 4){
                        swap(numberBoxesHard, i, i-swapNum);
                        break;
                    }
                    else {break;}
            }
        }
        checkEnd(backgroundBoxHard);
    }


    glutPostRedisplay();
}

void cursor(int x, int y) {


    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {


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
