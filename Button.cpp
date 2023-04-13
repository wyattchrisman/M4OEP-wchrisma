#include "Button.h"
#include "graphics.h"
using namespace std;

Button::Button(color fill, point2D center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {fill.red + 0.5, fill.green + 0.5, fill.blue + 0.5};
    pressFill = {fill.red - 0.5, fill.green - 0.5, fill.blue - 0.5};
}

void Button::draw() const {
    Quad::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
    // TODO: Implement

    bool overlap = false;

    // Create all rectangle left and right variables
    double width = getWidth();
    double left = getLeftX();
    double right = left + width;

    bool leftRight = false;
    if(left <= x && x <= right) {
        leftRight = true;
    }

    // Create all rectangle top and bottom variables
    double height = getHeight();
    double top = getTopY();
    double bottom = top + height;

    if(top <= y && y <= bottom && leftRight) {
        overlap = true;
    }

    return overlap; // Placeholder for compilation
}

/* Change color of the box when the user is hovering over it */
void Button::hover() {
    setColor(hoverFill);
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
    setColor(originalFill);
}