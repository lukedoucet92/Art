
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
    Line(Point start, Point end);
    Line(Point start, Point end, float stroke, Color color);
    Line(Point start, float angle, float length);
    
    Point start;
    Point end;
    
    string getSvg();
    
    float getLength();
    
    float getAngle();
    
    Color color;
    
    float stroke;
};

#endif
