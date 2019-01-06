//
//  SVGObject.h
//  Art
//
//  Created by Luke Doucet on 5/18/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#ifndef SVGObject_h
#define SVGObject_h

#include <string>
#include "Color.h"

class SVGObject {
public:
    SVGObject();
    
    /// SVG representation of the object.
    virtual string getSvg() = 0;
    
    /// The color of the object.
    Color color;
};

#endif
