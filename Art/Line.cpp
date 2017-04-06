
#include "Line.h"

using namespace std;

Line::Line() {
    this->x1 = 0;
    this->x2 = 0;
    this->y1 = 0;
    this->y2 = 0;
    
    this->stroke = 1.0;
    this->color = Color();
}

Line::Line(float x1, float x2, float y1, float y2) {
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    
    this->stroke = 1.0;
    this->color = Color();
}

Line::Line(float x1, float x2, float y1, float y2, float stroke, Color color) {
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    
    this->stroke = stroke;
    this->color = color;
}

string Line::getSvg() {
    string svg = "<line ";
    svg += "x1=\"" + to_string(this->x1) + "\" ";
    svg += "y1=\"" + to_string(this->y1) + "\" ";
    svg += "x2=\"" + to_string(this->x2) + "\" ";
    svg += "y2=\"" + to_string(this->y2) + "\" ";
    svg += "style=\"stroke:" + this->color.toSvg() + ";stroke-width:";
    svg += to_string(this->stroke) + "\" />\n";
    return svg;
}
