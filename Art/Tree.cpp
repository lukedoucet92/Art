
#include "Tree.h"

using namespace std;


//MARK: Constructor

Tree::Tree() {
    this->canvas = Canvas(Size(100, 100));
    this->svg = "";
    
    Line left = Line();
    Line right = Line();
    left.x1 = 0;
    left.y1 = 0;
    left.x2 = canvas.size.width/2.0;
    left.y2 = 0;
    left.color = Color(0, 0.5, 1.0);
    left.stroke = 5.0;
    
    right.x1 = left.x2;
    right.y1 = left.y2;
    right.x2 = left.x2;
    right.y2 = canvas.size.height;
    right.color = Color(1.0, 0.5, 0.0);
    right.stroke = 2.0;
    
    
    TreeNode * t = new TreeNode(NULL, NULL, left, right);
    root = t;
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
        file << "<svg width=\"" << roundf(this->canvas.size.width) << "\" height=\"" << roundf(this->canvas.size.height) << "\">\n";
        file << svg;
        file << "</svg>";
        file.close();
    } else {
        exit(1);
    }
}
