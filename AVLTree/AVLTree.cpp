#include "AVLTree.h"
#include <algorithm>
#include <string>
using namespace std;

AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::deleteTree(Node* node) {
    // Recursively remove all nodes in the BST (used by the destructor). 
    // By doing this recursively, we start removing nodes from the bottom
    // of the tree (leaf nodes), which is most efficiently because it does
    // not require replacing any nodes.

    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

//update a nodes height value by taking max of child subtrees heights and adding 1
void Node::AVLTreeUpdateHeight() {
    int leftHeight = -1;
    if (left != nullptr)
        leftHeight = left->height;
    int rightHeight = -1;
    if (right != nullptr)
        rightHeight = right->height;
    height = max(leftHeight, rightHeight) + 1;
}

//subtract right subtree height from left subtree height to get balance factor
int Node::AVLTreeGetBalance(Node* node) {
    int leftHeight = -1;
    if (node->left != nullptr)
        leftHeight = node->left->height;
    int rightHeight = -1;
    if (node->right != nullptr)
        rightHeight = node->right->height;
    return leftHeight - rightHeight;
}

//Defined on a subtree root (node D) which must have a left child (node B).
//The algorithm reassigns child pointers, assigning B's right child with D,
//and assigning D's left child with C (B's original right child, which may be
//null). If D's parent is non-null, then the parent's child is replaced with B
Node* AVLTree::AVLTreeRotateRight(Node* node) {
    Node* leftRightChild = node->left->right;
    if (node->parent != nullptr)
        node->parent->AVLTreeReplaceChild(node->parent, node, node->left);
    else {  //node is root
        root = node->left;
        root->parent = nullptr;
    }
    node->left->AVLTreeSetChild(node->left, false, node);
    node->AVLTreeSetChild(node, true, leftRightChild);
    return node->parent;    //added return value for replaceChild function
}

//Functionally same as RotateRight, just inversed for a left rotate
Node* AVLTree::AVLTreeRotateLeft(Node* node) {
    Node* rightLeftChild = node->right->left;
    if (node->parent != nullptr)
        node->parent->AVLTreeReplaceChild(node->parent, node, node->right);
    else {  //node is root
        root = node->right;
        root->parent = nullptr;
    }
    node->right->AVLTreeSetChild(node->right, true, node);
    node->AVLTreeSetChild(node, false, rightLeftChild);
    return node->parent;
}

//Replace one of a node's existing child pointer with a new value,
//utilizing AVLTreeSetChild to perform replacement
bool Node::AVLTreeReplaceChild(Node* parent, Node* currentChild, Node* newChild) {
    if (parent->left == currentChild)
        return AVLTreeSetChild(parent, true, newChild);
    else if (parent->right == currentChild)
        return AVLTreeSetChild(parent, false, newChild);
    return false;
}

//Sets a node as the parent's left or right child, updates the child's pointer,
//and updates the child's parent pointer, and update the parent node's height
bool Node::AVLTreeSetChild(Node* parent, bool whichChild, Node* child) {
    if (whichChild)
        parent->left = child;
    else
        parent->right = child;
    if (child != nullptr)
        child->parent = parent;
    AVLTreeUpdateHeight();
    return true;
}

//Updates the height value at a node, computes the balance factor,
//and rotates if the balance factor is 2 or -2
Node* AVLTree::AVLTreeRebalance(Node* node) {
    node->AVLTreeUpdateHeight();
    if (node->AVLTreeGetBalance(node) == -2) {
        if (node->right->AVLTreeGetBalance(node->right) == 1) {
            //Double rotation case
            AVLTreeRotateRight(node->right);
        }
        return AVLTreeRotateLeft(node);
    }
    else if (node->AVLTreeGetBalance(node) == 2) {
        if (node->left->AVLTreeGetBalance(node->left) == -1) {
            //Double rotation case
            AVLTreeRotateLeft(node->left);
        }
        return AVLTreeRotateRight(node);
    }
    return node;
}

//All ancestors of the inserted node, from the parent up to the root,
//are rebalanced. A node is rebalanced by first computing the node's
//balance factor, then performing rotations if the balance factor is 
//outside of the range [-1, 1].
void AVLTree::AVLTreeInsert(Node* node, bool AVL) {
    if (root == nullptr) {
        root = node;
        node->parent = nullptr;
        return;
    }

    Node* cur = root;
    while (cur != nullptr) {
        if (node->key < cur->key) {
            if (cur->left == nullptr) {
                cur->left = node;
                node->parent = cur;
                cur = nullptr;
            }
            else {
                cur = cur->left;
            }
        }
        else {
            if (cur->right == nullptr) {
                cur->right = node;
                node->parent = cur;
                cur = nullptr;
            }
            else
                cur = cur->right;
        }
    }
    if (AVL) {  //if its an AVL tree, rebalance
        node = node->parent;
        while (node != nullptr) {
            AVLTreeRebalance(node);
            node = node->parent;
        }
    }
}

//uses AVLInsert but doesnt rebalance
void AVLTree::insertWithoutRebalance(Node* node) {
    this->AVLTreeInsert(node, false);   //insert into BST
    node = node->parent;
    while (node != nullptr) {   //no rebalance in this step
        node->AVLTreeUpdateHeight();
        node = node->parent;
    }
}





