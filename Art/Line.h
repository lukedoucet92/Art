
#ifndef LINE_H
#define LINE_H

#include <string>
#include "Color.h"

using namespace std;

class Line {
public:
    Line();
    Line(float x1, float x2, float y1, float y2);
    Line(float x1, float x2, float y1, float y2, float stroke, Color color);
    
    float x1;
    float x2;
    float y1;
    float y2;
    
    string getSvg();
    
    Color color;
    
    float stroke;
};

#endif
