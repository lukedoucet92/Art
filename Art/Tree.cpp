
#include "Tree.h"

using namespace std;


//MARK: Constructor

Tree::Tree() {
    canvas = Canvas(Size(800, 450));
    svg = "<svg width=\"" + to_string(roundf(canvas.size.width)) + "\" height=\"" + to_string(roundf(canvas.size.height)) + "\">\n";
    svg += "<rect x=\"0\" y=\"0\" width=\"" + to_string(roundf(canvas.size.width)) + "\" height=\"" + to_string(roundf(canvas.size.height)) + "\" ";
    svg += "style=\"fill:#ffffff;\" />\n";
    initialStroke = 20;
    strokeShrinkFactor = 0.5;
    lineShrinkFactor = 0.75;
    angleRotationFactor = 15.0;
    alphaFadeFactor = 0.75;
    
    float halfCanvas = canvas.size.width/2;
    float rootLineHeight = canvas.size.height/3;
    Point rootStart = Point(halfCanvas, 0);
    Point rootEnd = Point(halfCanvas, rootLineHeight);
    rootLine = Line(rootStart, rootEnd, initialStroke, Color().blackColor());
    svg += rootLine.getSvg();
    
    _skew();
    _complete();
    _pre_order_map(&root, &Tree::_output);
}

/// Creates a left skewed tree.
void Tree::_skew() {
    int currentLevel = NUM_LEVELS;
    
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
    root->leftLine.start = rootLine.end;
    root->leftLine.end = Line(rootLine.end, angleRotationFactor, rootLine.getLength()*lineShrinkFactor).end;
    root->leftLine.stroke = rootLine.stroke * strokeShrinkFactor;
    
    root->rightLine.color = Color().blackColor();
    root->rightLine.color.alpha = rootLine.color.alpha * alphaFadeFactor;
    root->rightLine.start = rootLine.end;
    root->rightLine.end = Line(rootLine.end, -angleRotationFactor, rootLine.getLength()*lineShrinkFactor).end;
    root->rightLine.stroke = rootLine.stroke * strokeShrinkFactor;
}

/// Creates a complete binary tree from the skewed tree.
void Tree::_complete() {
    _pre_order_map(&root, &Tree::_completeNode);
}

void Tree::_completeNode(TreeNode ** node) {
    if((*node)->currentLevel != NUM_LEVELS) {
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
        bool isRightSide = true;
        
        if((*node)->parent->leftChild == (*node)) {
            isRightSide = false;
        }
        
        if(isRightSide) {
            (*node)->leftLine.color = Color().blackColor();
            (*node)->leftLine.color.alpha = (*node)->parent->rightLine.color.alpha * alphaFadeFactor;
            (*node)->leftLine.start = (*node)->parent->rightLine.end;
            (*node)->leftLine.end = Line((*node)->parent->rightLine.end, (*node)->parent->rightLine.getAngle()+angleRotationFactor, (*node)->parent->rightLine.getLength()*lineShrinkFactor).end;
            (*node)->leftLine.stroke = (*node)->parent->rightLine.stroke * strokeShrinkFactor;
            
            (*node)->rightLine.color = Color().blackColor();
            (*node)->rightLine.color.alpha = (*node)->parent->rightLine.color.alpha * alphaFadeFactor;
            (*node)->rightLine.start = (*node)->parent->rightLine.end;
            (*node)->rightLine.end = Line((*node)->parent->rightLine.end, (*node)->parent->rightLine.getAngle()-(angleRotationFactor*2), (*node)->parent->rightLine.getLength()*lineShrinkFactor).end;
            (*node)->rightLine.stroke = (*node)->parent->rightLine.stroke * strokeShrinkFactor;
        } else {
            (*node)->leftLine.color = Color().blackColor();
            (*node)->leftLine.color.alpha = (*node)->parent->leftLine.color.alpha * alphaFadeFactor;
            (*node)->leftLine.start = (*node)->parent->leftLine.end;
            (*node)->leftLine.end = Line((*node)->parent->leftLine.end, (*node)->parent->leftLine.getAngle()+angleRotationFactor, (*node)->parent->leftLine.getLength()*lineShrinkFactor).end;
            (*node)->leftLine.stroke = (*node)->parent->leftLine.stroke * strokeShrinkFactor;
            
            (*node)->rightLine.color = Color().blackColor();
            (*node)->rightLine.color.alpha = (*node)->parent->leftLine.color.alpha * alphaFadeFactor;
            (*node)->rightLine.start = (*node)->parent->leftLine.end;
            (*node)->rightLine.end = Line((*node)->parent->leftLine.end, (*node)->parent->leftLine.getAngle()-(angleRotationFactor*2), (*node)->parent->leftLine.getLength()*lineShrinkFactor).end;
            (*node)->rightLine.stroke = (*node)->parent->leftLine.stroke * strokeShrinkFactor;
        }
    }
}

//MARK: Destructor

Tree::~Tree() {
    dealloc();
}

void Tree::dealloc() {
    if(this->root != NULL) {
        _post_order_map(&root, &Tree::deleteNode);
    } else {
        printf("Fatal: Unable to delete tree. Already NULL at %p\n", (void*)&root);
        exit(EXIT_FAILURE);
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
    svg += (*node)->leftLine.getSvg();
    svg += (*node)->rightLine.getSvg();
}

void Tree::output() {
    _post_order_map(&root, &Tree::_output);
    
    ofstream file ("art.svg");
    if (file.is_open()) {
        file << svg;
        file << "</svg>";
        file.close();
    } else {
        exit(1);
    }
}
