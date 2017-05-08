//
//  Canvas.h
//  Art
//
//  Created by Luke Doucet on 4/5/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#ifndef CANVAS_H
#define CANVAS_H

#include "Size.h"
#include "Point.h"

struct Canvas {
    Canvas();
    Canvas(Size size);
    ~Canvas();
    
    Point midPoint();
    
    Size size;
};

#endif
