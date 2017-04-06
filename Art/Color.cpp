//
//  Color.cpp
//  Art
//
//  Created by Luke Doucet on 4/4/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#include "Color.h"

Color::Color() {
    this->red = 0.0;
    this->green = 0.0;
    this->blue = 0.0;
}

Color::Color(float red, float green, float blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

string Color::toSvg() {
    float r = red * 255.0;
    float g = green * 255.0;
    float b = blue * 255.0;
    string svg = "rgb(" + to_string(r) + "," + to_string(g) + "," + to_string(b) + ")";
    return svg;
}
