//
// Created by Wyatt Chrisman on 4/12/23.
//

#ifndef M4OEP_WCHRISMA_QUAD_H
#define M4OEP_WCHRISMA_QUAD_H

#include <string>
#include <vector>
using std::vector;

struct color {
    double red;
    double green;
    double blue;
    double alpha; // Opacity (0 is transparent, 1 is solid)

    /* Constructors */
    color();
    color(double r, double g, double b);
    color(double r, double g, double b, double a);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const color &c);
};

struct point2D {
    double x;
    double y;

    /* Constructors */
    point2D();
    point2D(double x, double y);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const point2D &p);
};

class Quad {
protected:
    color fill;
    point2D center;
    unsigned int width;
    unsigned int height;

public:
    Quad();
    Quad(color fill, point2D center, unsigned int width, unsigned int height);

    int getCenterX() const;
    int getLeftX() const;
    int getRightX() const;
    int getCenterY() const;
    int getTopY() const;
    int getBottomY() const;
    point2D getCenter() const;

    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    color getFill() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setColor(double red, double green, double blue);
    void setColor(color fill);
    void setCenter(point2D center);
    void move(int deltaX, int deltaY);
    void resize(unsigned int width, unsigned int height);
    bool isOverlapping(int x, int y) const;
    void hover();
    void pressDown();
    void release(vector<Quad> &vec1, vector<Quad> &vec2);

    virtual void draw() const;
};

#endif //M4OEP_WCHRISMA_QUAD_H
