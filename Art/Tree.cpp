//
//  Tree.cpp
//  Art
//
//  Created by Luke Doucet on 4/4/17.
//  Copyright © 2017 Luke Doucet. All rights reserved.
//

#include "Tree.h"

using namespace std;

//MARK: Constructor

Tree::Tree(Size canvasSize) {
    canvas = SVGCanvas(canvasSize);
    initialStroke = 10;
    strokeShrinkFactor = 0.65;
    lineShrinkFactor = 0.90;
    angleRotationFactor = 5;
    alphaFadeFactor = 0.75;
    numberOfLevels = 8;
}

/// Creates a left skewed tree.
void Tree::_skew() {
    int currentLevel = numberOfLevels;
    
    TreeNode* ptr = NULL;
    
    while (currentLevel > 0) {
        TreeNode* newNode = new TreeNode();
        (*newNode).currentLevel = currentLevel;
        if(ptr == NULL) {
            ptr = newNode;
        } else {
            newNode->leftChild = ptr;
            ptr->parent = newNode;
            ptr = newNode;
        }
        newNode = NULL;
        currentLevel--;
    }
    
    root = ptr;
    ptr = NULL;
    
    root->leftLine.color = Color().blackColor();
    root->leftLine.color.alpha = rootLine.color.alpha * alphaFadeFactor;
    root->leftLine = SVGLine(rootLine.getEnd(), rootLine.getAngle()-angleRotationFactor, rootLine.getLength()*lineShrinkFactor);
    root->leftLine.stroke = rootLine.stroke * strokeShrinkFactor;
    
    root->rightLine.color = Color().blackColor();
    root->rightLine.color.alpha = rootLine.color.alpha * alphaFadeFactor;
    root->rightLine = SVGLine(rootLine.getEnd(), rootLine.getAngle()+angleRotationFactor, rootLine.getLength()*lineShrinkFactor);
    root->rightLine.stroke = rootLine.stroke * strokeShrinkFactor;
}

/// Creates a complete binary tree from the skewed tree.
void Tree::_complete() {
    _pre_order_map(&root, &Tree::_completeNode);
}

/// Configures an individial node in the tree.
void Tree::_completeNode(TreeNode ** node) {
    if((*node)->currentLevel != numberOfLevels) {
        if ((*node)->leftChild == NULL) {
            TreeNode* newNode = new TreeNode();
            newNode->parent = *node;
            newNode->currentLevel = (*node)->currentLevel+1;
            (*node)->leftChild = newNode;
        }
        if ((*node)->rightChild == NULL) {
            TreeNode* newNode = new TreeNode();
            newNode->parent = *node;
            newNode->currentLevel = (*node)->currentLevel+1;
            (*node)->rightChild = newNode;
        }
    }
    
    if((*node)->parent != NULL) {
        bool isRightSide = (*node)->parent->leftChild == (*node);
        
        if(isRightSide) {
            (*node)->leftLine.color = Color().blackColor();
            (*node)->leftLine.color.alpha = (*node)->parent->rightLine.color.alpha * alphaFadeFactor;
            (*node)->leftLine = SVGLine((*node)->parent->rightLine.getEnd(), (*node)->parent->rightLine.getAngle()-(angleRotationFactor*(*node)->currentLevel), (*node)->parent->rightLine.getLength()*lineShrinkFactor);
            (*node)->leftLine.stroke = (*node)->parent->rightLine.stroke * strokeShrinkFactor;
            
            (*node)->rightLine.color = Color().blackColor();
            (*node)->rightLine.color.alpha = (*node)->parent->rightLine.color.alpha * alphaFadeFactor;
            (*node)->rightLine = SVGLine((*node)->parent->rightLine.getEnd(), (*node)->parent->rightLine.getAngle()+(angleRotationFactor*(*node)->currentLevel), (*node)->parent->rightLine.getLength()*lineShrinkFactor);
            
            (*node)->rightLine.stroke = (*node)->parent->rightLine.stroke * strokeShrinkFactor;
            
        } else {
            (*node)->leftLine.color = Color().blackColor();
            (*node)->leftLine.color.alpha = (*node)->parent->leftLine.color.alpha * alphaFadeFactor;
            (*node)->leftLine = SVGLine((*node)->parent->leftLine.getEnd(), (*node)->parent->leftLine.getAngle()-(angleRotationFactor*(*node)->currentLevel), (*node)->parent->leftLine.getLength()*lineShrinkFactor);
            
            (*node)->leftLine.stroke = (*node)->parent->leftLine.stroke * strokeShrinkFactor;
            
            (*node)->rightLine.color = Color().blackColor();
            (*node)->rightLine.color.alpha = (*node)->parent->leftLine.color.alpha * alphaFadeFactor;
            (*node)->rightLine = SVGLine((*node)->parent->leftLine.getEnd(), (*node)->parent->leftLine.getAngle()+(angleRotationFactor*(*node)->currentLevel), (*node)->parent->leftLine.getLength()*lineShrinkFactor);
            
            (*node)->rightLine.stroke = (*node)->parent->leftLine.stroke * strokeShrinkFactor;
        }
    }
}

//MARK: Destructor

Tree::~Tree() {
    dealloc();
}

void Tree::dealloc() {
    canvas.objects.clear();
    
    if(this->root != NULL) {
        _post_order_map(&root, &Tree::deleteNode);
    } else {
        return;
    }
}

void Tree::deleteNode(TreeNode ** node) {
    if (*node) {
        delete *node;
        *node = NULL;
    }
}

//MARK: External Traversal Methods

void Tree::post_order_map(void (Tree::*handler)(TreeNode**)) {
    _post_order_map(&root, handler);
}

void Tree::in_order_map(void (Tree::*handler)(TreeNode**)) {
    _in_order_map(&root, handler);
}

void Tree::pre_order_map(void (Tree::*handler)(TreeNode**)) {
    _pre_order_map(&root, handler);
}

//MARK: Internal Traversal Methods

void Tree::_post_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**)) {
    if(*node == NULL) {
        printf("Warning: Unable to map node. Already NULL at %p\n", (void*)node);
        return;
    }
    if((*node)->leftChild != NULL) {
        _post_order_map(&(*node)->leftChild, handler);
    }
    if((*node)->rightChild != NULL) {
        _post_order_map(&(*node)->rightChild, handler);
    }
    (*this.*handler)(node);
}

void Tree::_in_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**)) {
    if(*node == NULL) {
        printf("Warning: Unable to map node. Already NULL at %p\n", (void*)node);
        return;
    }
    if((*node)->leftChild != NULL) {
        _in_order_map(&(*node)->leftChild, handler);
    }
    (*this.*handler)(node);
    if((*node)->rightChild != NULL) {
        _in_order_map(&(*node)->rightChild, handler);
    }
}

void Tree::_pre_order_map(TreeNode** node, void (Tree::*handler)(TreeNode**)) {
    if(*node == NULL) {
        printf("Warning: Unable to map node. Already NULL at %p\n", (void*)node);
        return;
    }
    (*this.*handler)(node);
    if((*node)->leftChild != NULL) {
        _pre_order_map(&(*node)->leftChild, handler);
    }
    if((*node)->rightChild != NULL) {
        _pre_order_map(&(*node)->rightChild, handler);
    }
}

void Tree::_output(TreeNode ** node) {
    canvas.objects.push_back( &(*node)->leftLine  );
    canvas.objects.push_back( &(*node)->rightLine );
}

void Tree::writeToFile(string filename) {
    
    //TODO: remove
    SVGRectangle * rect = new SVGRectangle(Point(), canvas.getSize());
    rect->color = Color().blueColor();
    canvas.objects.push_back(rect);
    
    if(numberOfLevels < 1) { return; }
    
    //TODO: fix
    float x = canvas.getSize().width/4;
    rootLine = SVGLine(Point(x, canvas.getSize().height), 270, canvas.getSize().height/2);
    
//    float x = canvas.getSize().width/4;
//    rootLine = SVGLine(Point(50, 100), 270, 50);
    
    rootLine.stroke = initialStroke;
    canvas.objects.push_back(&rootLine);
    
    _skew();
    _complete();
    _pre_order_map(&root, &Tree::_output);
    
    ofstream file (filename);
    if (file.is_open()) {
        file << canvas.getSvg();
        file.close();
    } else {
        exit(1);
    }
    
    dealloc();
}
