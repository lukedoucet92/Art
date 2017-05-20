//
//  RecursiveDrawing.hpp
//  Art
//
//  Created by Luke Doucet on 5/19/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#ifndef RecursiveDrawing_h
#define RecursiveDrawing_h

#include <iostream>
#include <fstream>
#include <math.h>

#include "SVGCircle.h"
#include "SVGRectangle.h"
#include "SVGCanvas.h"
#include "Graphics.h"

class RecursiveDrawing {
public:
    RecursiveDrawing(Size size);
    
    // Outputs the art to file.
    void writeToFile(string filename);
    
    ~RecursiveDrawing();
protected:
    SVGCanvas * canvas;
};

#endif
