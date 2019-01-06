//
//  SVGCanvas.cpp
//  Art
//
//  Created by Luke Doucet on 4/4/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#include "SVGCanvas.h"

SVGCanvas::SVGCanvas() {
    this->objects = vector<SVGObject*>();
    this->size = Size();
}

SVGCanvas::SVGCanvas(Size size) {
    this->objects = vector<SVGObject*>();
    this->size = size;
}

SVGCanvas::~SVGCanvas() {
    objects.clear();
}

string SVGCanvas::getSvg() {
    string svg = "<svg width=\"" + to_string(roundf(size.width)) + "\" height=\"" + to_string(roundf(size.height)) + "\">\n";
    for (vector<SVGObject*>::iterator it = objects.begin() ; it != objects.end(); ++it) {
        svg += (*it)->getSvg();
    }
    svg += SVG_CLOSE_TAG;
    return svg;
}

Size SVGCanvas::getSize() {
    return this->size;
}

Point SVGCanvas::getMidPoint() {
    return Point(size.width/2, size.height/2);
}

Point SVGCanvas::getMinPoint() {
    return Point(0, 0);
}

Point SVGCanvas::getMaxPoint() {
    return Point(size.width, size.height);
}
