//
//  SVGRectangle.cpp
//  Art
//
//  Created by Luke Doucet on 4/4/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#include "SVGRectangle.h"

SVGRectangle::SVGRectangle(Point point, Size size) {
    this->point = point;
    this->size = size;
    this->color = Color().blackColor();
}

string SVGRectangle::getSvg() {
    string svg = "<rect x=\"" + to_string(roundf(point.x)) + "\" y=\"" + to_string(roundf(point.y)) + "\" ";
    svg+= "width=\"" + to_string(roundf(size.width)) + "\" height=\"" + to_string(roundf(size.height)) + "\" ";
    svg += "style=\"fill:" + color.rgba() + ";\" />\n";
    return svg;
}
