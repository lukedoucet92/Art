//
//  SVGCanvas.h
//  Art
//
//  Created by Luke Doucet on 4/4/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#ifndef CANVAS_H
#define CANVAS_H

#include <math.h>
#include <vector>
#include "Size.h"
#include "Point.h"
#include "SVGObject.h"
#include "SVGConstants.h"

using namespace std;

class SVGCanvas : public SVGObject {
public:
    SVGCanvas();
    
    SVGCanvas(Size size);
    
    ~SVGCanvas();
    
    string getSvg();
    
    Point getMidPoint();
    
    Point getMinPoint();
    
    Point getMaxPoint();
    
    Point maxX();
    
    Point maxY();

    Size getSize();
    
    vector<SVGObject*> objects;
    
protected:
    
    Size size;
};

#endif
