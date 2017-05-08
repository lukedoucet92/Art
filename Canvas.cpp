//
//  Canvas.cpp
//  Art
//
//  Created by Luke Doucet on 4/5/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#include "Canvas.h"

Canvas::Canvas() {
    this->size = Size();
}

Canvas::Canvas(Size size) {
    this->size = size;
}

Canvas::~Canvas() {
    
}

Point Canvas::midPoint() {
    return Point(size.width/2, size.height/2);
}
