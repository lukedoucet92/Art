
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include <math.h>
#include "Line.h"
#include "Canvas.h"


enum PrintOrder {
    preOrder,
    inOrder,
    postOrder
};

struct TreeNode {
    TreeNode* leftChild;
    TreeNode* rightChild;
    Line leftLine;
    Line rightLine;
    
    TreeNode(Line leftLine, Line rightLine) {
        this->leftChild = NULL;
        this->rightChild = NULL;
        this->leftLine = leftLine;
        this->rightLine = rightLine;
    }
    
    TreeNode(TreeNode* leftChild, TreeNode* rightChild, Line leftLine, Line rightLine) {
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->leftLine = leftLine;
        this->rightLine = rightLine;
    }
};

#define MAX_LEVELS 5

class Tree {
public:
    
    Tree();
    
    // Outputs the art to file.
    void output();
    
    ~Tree();
    
private:
    
    // Pointer to the root of the parse tree.
    TreeNode* root;
    
    // SVG output.
    string svg;
    
    // Number of levels on the tree.
    int maxLevels;
    
    // The canvas.
    Canvas canvas;
    
    // The initial stroke of the `rootLine`.
    float initialStroke;
    
    // The root line of the tree.
    Line rootLine;
    
    // The stroke shrink factor.
    float strokeShrinkFactor;
    
    // The line shink factor.
    float lineShrinkFactor;
    
    // The angle rotation factor.
    float angleRotationFactor;
    
    // Internal Print
    void _output(TreeNode ** node);
    
    // External Traversal Methods
    void post_order_map(void (Tree::*handler)(TreeNode**));
    void in_order_map(void (Tree::*handler)(TreeNode**));
    void pre_order_map(void (Tree::*handler)(TreeNode**));
    
    
    // Internal Traversal Methods
    void _post_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**));
    void _in_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**));
    void _pre_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**));
    
    // Destructor Helpers
    void dealloc();
    void deleteNode(TreeNode ** node);
};

#endif
