
#include "SVGLine.h"

using namespace std;

SVGLine::SVGLine() {
    this->start = Point();
    this->end = Point();
    this->stroke = 1.0;
    this->color = Color();
    this->angle = 0;
}

SVGLine::SVGLine(Point start, float degrees, float length) {    
    this->start = start;
    this->stroke = 1.0;
    this->color = Color();
    this->angle = degrees;
    
    float x = length * cos(degrees * M_PI / 180.0) + start.x;
    float y = length * sin(degrees * M_PI / 180.0) + start.y;
    this->end = Point(x, y);
}

float SVGLine::getLength() {
    float a = fabs(start.x - end.x + 0.0);
    float b = fabs(start.y - end.y + 0.0);
    float c = sqrtf( powf(a, 2.0) + powf(b, 2.0) );
    return c;
}

string SVGLine::getSvg() {
    string svg = "<line ";
    svg += "x1=\"" + to_string(this->start.x) + "\" ";
    svg += "y1=\"" + to_string(this->start.y) + "\" ";
    svg += "x2=\"" + to_string(this->end.x) + "\" ";
    svg += "y2=\"" + to_string(this->end.y) + "\" ";
    svg += "style=\"stroke:" + this->color.rgba() + ";stroke-width:";
    svg += to_string(this->stroke) + ";stroke-opacity:" + to_string(this->color.alpha) + "\" />\n";
    return svg;
}

Point SVGLine::getStart() {
    return start;
}

Point SVGLine::getEnd() {
    return end;
}

float SVGLine::getAngle() {
    return angle;
}
