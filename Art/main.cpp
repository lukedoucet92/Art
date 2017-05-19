//
//  main.cpp
//  Calculator
//
//  Created by Luke Doucet on 10/28/16.
//  Copyright © 2016 Luke Doucet. All rights reserved.
//

#include <iostream>
#include "Tree.h"

using namespace std;

int main(int argc, const char * argv[]) {
    try {
        Tree *tree = new Tree(Size(250, 250));
        tree->writeToFile("art.svg");
        tree->numberOfLevels = 0;
        tree->alphaFadeFactor = 1.0;
        tree->writeToFile("tree.svg");
        delete tree;
        tree = NULL;
        
    } catch (string exception) {
        cout << exception << endl;
    }
    
    return 0;
}
