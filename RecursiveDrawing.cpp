//
//  RecursiveDrawing.cpp
//  Art
//
//  Created by Luke Doucet on 5/19/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#include "RecursiveDrawing.h"

RecursiveDrawing::RecursiveDrawing(Size size) {
    canvas = new SVGCanvas(size);
}

/// Outputs the art to file.
void RecursiveDrawing::writeToFile(string filename) {
    int previous = 0;
    int current = 1;
    float radius = 0;
    const int k = 1;
    int i = 1;
    SVGCircle * circle;
    
    while(radius < 1000) {
        radius += k;//previous + current;
        previous = current;
        current = radius;
        float theta = i * k;
        float x = radius * cos(theta * M_PI / 180);
        float y = radius * sin(theta * M_PI / 180);
        circle = new SVGCircle(Point(x, y), radius);
        circle->color.alpha = 0;
        circle->strokeColor = Color().blackColor();
        circle->strokeWidth = 1;
        canvas->objects.push_back(circle);
        circle = NULL;
        i++;
    }

    // Uncomment the following to generate a circular shape
    // thingy. But make sure you remove the previous code
    // in this function.
    
//    int previous = 0;
//    int current = 1;
//    float radius = 0;
//    const int k = 5;
//    int i = 1;
//    SVGCircle * circle;
//    while(i * k <= 360) {
//        radius = 100;//previous + current;
//        previous = current;
//        current = radius;
//        float theta = i * k;
//        float x = radius * cos(theta * M_PI / 180);
//        float y = radius * sin(theta * M_PI / 180);
//        circle = new SVGCircle(Point(x, y), radius);
//        circle->color.alpha = 0;
//        circle->strokeColor = Color().blackColor();
//        circle->strokeWidth = .5;
//        canvas->objects.push_back(circle);
//        circle = NULL;
//        i++;
//    }
    
    ofstream file (filename);
    if (file.is_open()) {
        file << canvas->getSvg();
        file.close();
    } else {
        exit(1);
    }
}

RecursiveDrawing::~RecursiveDrawing() {
    delete canvas;
    canvas = NULL;
}
