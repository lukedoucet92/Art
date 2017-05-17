
#ifndef LINE_H
#define LINE_H

#include <string>
#include <iostream>
#include <math.h>
#include "Color.h"
#include "Point.h"

using namespace std;

class Line {
public:
    Line();
    Line(Point start, float angle, float length);
    
    string getSvg();
    Point getStart();
    Point getEnd();
    float getAngle();
    float getLength();
    
    Color color;
    
    float stroke;
    
private:
    float angle;
    Point start;
    Point end;
};

#endif
