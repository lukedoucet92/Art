//
//  Tree.h
//  Art
//
//  Created by Luke Doucet on 4/4/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include <math.h>
#include "SVGLine.h"
#include "SVGRectangle.h"
#include "SVGCanvas.h"

enum PrintOrder {
    preOrder,
    inOrder,
    postOrder
};

struct TreeNode {
    TreeNode* leftChild;
    TreeNode* rightChild;
    SVGLine leftLine;
    SVGLine rightLine;
    TreeNode* parent;
    int currentLevel;
    
    TreeNode() {
        this->leftChild = NULL;
        this->rightChild = NULL;
        this->leftLine = SVGLine();
        this->rightLine = SVGLine();
        this->parent = NULL;
        currentLevel = 0;
    }
    
    TreeNode(TreeNode* leftChild, TreeNode* rightChild) {
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->leftLine = SVGLine();
        this->rightLine = SVGLine();
        this->parent = NULL;
        currentLevel = 0;
    }
    
    TreeNode(SVGLine leftLine, SVGLine rightLine) {
        this->leftChild = NULL;
        this->rightChild = NULL;
        this->leftLine = leftLine;
        this->rightLine = rightLine;
        this->parent = NULL;
        currentLevel = 0;
    }
    
    TreeNode(TreeNode* leftChild, TreeNode* rightChild, SVGLine leftLine, SVGLine rightLine, TreeNode* parent) {
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->leftLine = leftLine;
        this->rightLine = rightLine;
        this->parent = parent;
        currentLevel = 0;
    }
};

class Tree {
public:
    
    Tree(Size canvasSize);
    
    // Outputs the art to file.
    void writeToFile(string filename);
    
    ~Tree();
    
    // The initial stroke of the `rootLine`.
    float initialStroke;
    
    // The stroke shrink factor.
    float strokeShrinkFactor;
    
    // The line shink factor.
    float lineShrinkFactor;
    
    // The angle rotation factor.
    float angleRotationFactor;
    
    // The alpha fade factor.
    float alphaFadeFactor;
    
    // The number of levels in the tree.
    int numberOfLevels;
    
private:
    
    // Pointer to the root of the parse tree.
    TreeNode* root;
    
    // The root line of the tree.
    SVGLine rootLine;
    
    // The canvas.
    SVGCanvas canvas;
    
    // Skews a tree to NUM_LEVELS.
    void _skew();
    
    // Completes the skewed tree.
    void _complete();
    
    // Completes tree at `node`.
    void _completeNode(TreeNode ** node);
    
    // Internal Print.
    void _output(TreeNode ** node);
    
    // External Traversal Methods.
    void post_order_map(void (Tree::*handler)(TreeNode**));
    void in_order_map(void (Tree::*handler)(TreeNode**));
    void pre_order_map(void (Tree::*handler)(TreeNode**));
    
    
    // Internal Traversal Methods.
    void _post_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**));
    void _in_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**));
    void _pre_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**));
    
    // Destructor Helpers.
    void dealloc();
    void deleteNode(TreeNode ** node);
};

#endif
