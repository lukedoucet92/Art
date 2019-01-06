//
//  SVGLine.h
//  Art
//
//  Created by Luke Doucet on 4/4/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#ifndef SVGLINE_H
#define SVGLINE_H

#include <string>
#include <iostream>
#include <math.h>
#include "Color.h"
#include "Point.h"
#include "SVGObject.h"

using namespace std;

class SVGLine : public SVGObject {
public:
    SVGLine();
    
    SVGLine(Point start, float angle, float length);
    
    string getSvg();
    
    Point getStart();
    
    Point getEnd();
    
    float getAngle();
    
    float getLength();
    
    float stroke;
    
private:
    float angle;
    
    Point start;
    
    Point end;
};

#endif
