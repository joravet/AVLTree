#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>

// A node in the AVL tree that stores a double
class Node {
public:
    double key;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(double nodeKey) {
        key = nodeKey;
    }
    //update height
    void AVLTreeUpdateHeight();
    //get balance factor
    int AVLTreeGetBalance(Node* node);
    //replace node child pointer with new value
    bool AVLTreeReplaceChild(Node* parent, Node* currentChild, Node* newChild);
    //set pointers
    bool AVLTreeSetChild(Node* parent, bool whichChild, Node* child);
};

// An AVL tree that can insert with and without rebalancing
class AVLTree
{
public:
    AVLTree() {};
    ~AVLTree();

    // Insert a new element and rebalance the tree
    void AVLTreeInsert(Node* node, bool AVL);
    // Insert a new element without rebalancing the tree
    void insertWithoutRebalance(Node* node);
    Node* AVLTreeRotateRight(Node* node);
    Node* AVLTreeRotateLeft(Node* node);
    Node* AVLTreeRebalance(Node* node);

    Node* root = nullptr;
    void deleteTree(Node* node);
};

#endif // !AVLTREE_H
