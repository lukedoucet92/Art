
#ifndef COLOR_H
#define COLOR_H

#include <string>

using namespace std;

class Color {
public:
    Color();
    Color(float red, float green, float blue, float alpha);
    
    string toSvg();
    
    // Black color.
    Color blackColor();
    
    // Green color.
    Color greenColor();
    
    float red;
    float green;
    float blue;
    float alpha;
};

#endif
