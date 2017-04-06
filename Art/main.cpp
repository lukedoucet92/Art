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
        Tree *tree = new Tree();
        tree->output();
        delete tree;
    } catch (string exception) {
        cout << exception << endl;
    }
}
