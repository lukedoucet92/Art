//
//  SVGCircle.cpp
//  Art
//
//  Created by Luke Doucet on 5/19/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#include "SVGCircle.h"

SVGCircle::SVGCircle() {
    this->center = Point();
    this->radius = 1;
    strokeColor = Color().clearColor();
    strokeWidth = 0;
}

SVGCircle::SVGCircle(Point center, float radius) {
    this->center = center;
    this->radius = radius;
    strokeColor = Color().clearColor();
    strokeWidth = 0;
}

string SVGCircle::getSvg() {
    string svg = "<circle cx=\"" + to_string(center.x) + "\" cy=\"" + to_string(center.y);
    svg += "\" r=\"" + to_string(radius) + "\" ";
    svg += "style=\"fill:" + color.rgba() + ";\" ";
    svg += "stroke=\"" + strokeColor.rgba() + "\" stroke-width=\"" + to_string(strokeWidth) + "\" />\n";
    
    return svg;
}
