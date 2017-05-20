//
//  SVGCircle.hpp
//  Art
//
//  Created by Luke Doucet on 5/19/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#ifndef SVGCircle_h
#define SVGCircle_h

#include "SVGObject.h"
#include "Graphics.h"

class SVGCircle : public SVGObject {
public:
    SVGCircle();
    
    SVGCircle(Point center, float radius);
    
    /// SVG representation of the object.
    string getSvg();
    
    /// The radius of the circle.
    float radius;
    
    /// The center point of the circle.
    Point center;
    
    /// The stroke color.
    Color strokeColor;
    
    /// The stroke width.
    float strokeWidth;
};

#endif
