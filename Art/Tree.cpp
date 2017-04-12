
#include "Tree.h"

using namespace std;


//MARK: Constructor

Tree::Tree() {
    canvas = Canvas(Size(800, 450));
    svg = "<svg width=\"" + to_string(roundf(canvas.size.width)) + "\" height=\"" + to_string(roundf(canvas.size.height)) + "\">\n";
    svg += "<rect x=\"0\" y=\"0\" width=\"" + to_string(roundf(canvas.size.width)) + "\" height=\"" + to_string(roundf(canvas.size.height)) + "\" ";
    svg += "style=\"fill:#007aff;\" />\n";
    maxLevels = MAX_LEVELS;
    initialStroke = 20;
    strokeShrinkFactor = 0.5;
    lineShrinkFactor = 0.75;
    angleRotationFactor = 15.0;
    
    float halfCanvas = canvas.size.width/2;
    float rootLineHeight = canvas.size.height/3;
    Point rootStart = Point(halfCanvas, 0);
    Point rootEnd = Point(halfCanvas, rootLineHeight);
    rootLine = Line(rootStart, rootEnd, initialStroke, Color().blackColor());
    svg += rootLine.getSvg();
    
    Line left = Line(rootLine.end, 90.0-angleRotationFactor, rootLine.getLength()*lineShrinkFactor);
    left.color = Color().blackColor();
    left.stroke = rootLine.stroke * strokeShrinkFactor;
    
    Line right = Line(rootLine.end, 90.0+angleRotationFactor, rootLine.getLength()*lineShrinkFactor);
    right.color = Color().blackColor();
    right.stroke = rootLine.stroke * strokeShrinkFactor;
    
    TreeNode * t = new TreeNode(NULL, NULL, left, right);
    root = t;
    
    
    Line left2 = Line(left.end, left.getAngle()+angleRotationFactor, left.getLength()*lineShrinkFactor);
    left2.color = Color().blackColor();
    left2.stroke = left.stroke * strokeShrinkFactor;
    
    Line right2 = Line(left.end, left.getAngle()-angleRotationFactor, left.getLength()*lineShrinkFactor);
    right2.color = Color().blackColor();
    right2.stroke = right.stroke * strokeShrinkFactor;
    
    cout << left.getAngle() << " is the angle." << endl;
    
    root->leftChild = new TreeNode(NULL, NULL, left2, right2);
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
