//
// Created by Wyatt Chrisman on 4/12/23.
//

#include "Quad.h"
#include "graphics.h"
#include <iostream>
using namespace std;

/********************* Color Struct ********************/

color::color() : red(0.0), green(0.0), blue(0.0), alpha(1.0) {
}

color::color(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {
}

color::color(double r, double g, double b) : red(r), green(g), blue(b), alpha(1.0) {
}

std::ostream& operator << (std::ostream& outs, const color &c) {
    outs << "(" << c.red << ", " << c.green << ", " << c.blue << ")";
    return outs;
}

/********************* Point Struct ********************/

point2D::point2D() : x(0), y(0) {}

point2D::point2D(double x, double y) : x(x), y(y) {}

ostream& operator << (ostream& outs, const point2D &p) {
    outs << "(" << p.x << ", " << p.y << ")";
    return outs;
}

Quad::Quad() {
    fill = {0, 0, 0};
    center = {0, 0};
    width = 50;
    height = 50;
}

Quad::Quad(color fill, point2D center, unsigned int width, unsigned int height) {
    this->fill = fill;
    this->center = center;
    this->width = width;
    this->height = height;
}

int Quad::getCenterX() const {
    return center.x;
}

int Quad::getLeftX() const {
    return center.x - (width / 2);
}

int Quad::getRightX() const {
    return center.x + (width / 2);
}

int Quad::getCenterY() const {
    return center.y;
}

int Quad::getTopY() const {
    return center.y - (height / 2);
}

int Quad::getBottomY() const {
    return center.y + (height / 2);
}

point2D Quad::getCenter() const {
    return center;
}

double Quad::getRed() const {
    return fill.red;
}

double Quad::getGreen() const {
    return fill.green;
}

double Quad::getBlue() const {
    return fill.blue;
}

color Quad::getFill() const {
    return fill;
}

unsigned int Quad::getWidth() const {
    return width;
}

unsigned int Quad::getHeight() const {
    return height;
}

void Quad::setColor(double red, double green, double blue) {
    fill = {red, green, blue};
}

void Quad::setColor(color fill) {
    this->fill = fill;
}

void Quad::setCenter(point2D center) {
    this->center = center;
}

void Quad::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Quad::resize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

bool Quad::isOverlapping(int x, int y) const {
    if (x < getLeftX() || x > getRightX() || y > getBottomY() || y < getTopY()) {
        return false;
    }
    return true;
}

void Quad::hover() {
    // TODO: Fix to match project
//    color red(1,0,0);
//    setColor(red);
}

void Quad::pressDown() {
    // TODO: Fix to match project
//    color grey(0.4, 0.4, 0.4);
//    color yellow(1, 1, 0);
//    //the conditional is always true so this doesn't work
//    if (getGreen() == 1 ) {
//        setColor(grey);
//    }
//    else {
//        setColor(yellow);
//    }
}

void Quad::release(vector<Quad> &vec1, vector<Quad> &vec2) {
    // TODO: Fix to match project
//    color yellow(1, 1, 0);
//    color grey(0.4, 0.4, 0.4);
//
//    for (int i = 0; i < vec1.size(); i++) {
//        if (vec1[i].getGreen() == 1) {
//            vec2[i].setColor(yellow);
//        }
//        else if (vec1[i].getGreen() == 0 && vec1[i].getRed() == 1) {
//            vec2[i].setColor(yellow);
//        }
//        else {
//            setColor(grey);
//        }
//    }
}

void Quad::draw() const {
    // TODO: Implement
    // Create quad and set color
    glBegin(GL_QUADS);
    glColor3f(fill.red, fill.green, fill.blue);

    // Create all Vertexes
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getRightX(), getBottomY());
    glVertex2i(getRightX(), getTopY());


    glEnd();

    // Don't forget to set the color to the fill field
}