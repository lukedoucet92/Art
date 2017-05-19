
#ifndef COLOR_H
#define COLOR_H

#include <string>

using namespace std;

class Color {
public:
    Color();
    
    Color(float red, float green, float blue, float alpha);
    
    string rgba();
    
    // Black color.
    Color blackColor();
    
    // Red color.
    Color redColor();
    
    // Green color.
    Color greenColor();
    
    // Blue color.
    Color blueColor();
    
    // Clear color.
    Color clearColor();
    
    // White color.
    Color whiteColor();

    float red;
    float green;
    float blue;
    float alpha;
};

#endif
