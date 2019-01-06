//
//  SVGRectangle.h
//  Art
//
//  Created by Luke Doucet on 4/4/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#ifndef SVGRectangle_h
#define SVGRectangle_h

#include <math.h>
#include "SVGObject.h"
#include "Point.h"
#include "Size.h"

class SVGRectangle : public SVGObject {
public:
    SVGRectangle(Point point, Size size);
    
    string getSvg();
protected:
    Point point;
    Size size;
};

#endif
