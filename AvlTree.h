#ifndef INC_234218_AVLTREE_H
#define INC_234218_AVLTREE_H

#include <iostream>
#include <memory>

int max(int a, int b) {
    return (a > b) ? a : b;
}

using std::ostream;
using std::shared_ptr;


template<class T>
struct Node {
    int ID;
    shared_ptr<T> obj;
    Node *left_son;
    Node *right_son;
    int height;
};

template<class T>
class AvlTree {
    Node<T> *root;

    Node<T> *addNode(Node<T> *node, const T &obj);

public:

    AvlTree() : root(NULL) {};

    ~AvlTree() = default;

    int calcHeight(Node<T> *node);

    void insert(const T &obj);

    Node<T> *RemoveNode(int NodeID);

    Node<T> * RightRotate (Node<T> * parent);

    Node<T> *LLRotate(Node<T> *parent);

    Node<T> *RRRotate(Node<T> *parent);

    Node<T> *LRRotate(Node<T> *parent);

    Node<T> *RLRotate(Node<T> *parent);

    /***maybe needed with O(1)*/
    void preOrder() const;

    void inorder() const;

    void postOrder() const;
};

/*** AVL Implementation */


template<class T>
int calcBF(Node<T> *node) {
    if (node->left_son && node->right_son) {
        return node->left_son->height - node->right_son->height;
    } else if (node->left_son) {
        return node->left_son->height;
    } else if (node->right_son) {
        return node->right_son->height;
    }
    else return 0;
};


template<class T>
int is_balanced(Node<T> *current) {
    int BF = calcBF(current);
    return (BF >= -1 && BF <= 1);
}

template<class T>
Node<T> *createNode(const T &obj) {
    Node<T> *node = new Node<T>();
    //node->obj = shared_ptr<T>(&obj);
    node->ID = obj.getID();
    node->left_son = NULL;
    node->right_son = NULL;
    node->height = -1;
    return node;
}

template<class T>
void AvlTree<T>::insert(const T &obj) {
    root = addNode(root, obj);
}


template<class T>
Node<T> *AvlTree<T>::RemoveNode(int NodeID) {
    //find node

    //remove

    //rotations
}


template<class T>
int AvlTree<T>::calcHeight(Node<T> *node) {
    if(!node) return -1;
    if (node->left_son && node->right_son) {
        return max(node->left_son->height, node->right_son->height);
    } else if (node->left_son) {
        return node->left_son->height;
    } else if (node->right_son) {
        return node->right_son->height;
    }
    return -1;
}

//ROTATE - IMPORTANT TO ADD
template<class T>
Node<T> *AvlTree<T>::addNode(Node<T> *node, const T &obj) {
    if (node==NULL) {
        node = createNode(obj);
    }

    else if (obj.getID() > node->ID) {
        node->right_son = addNode(node->right_son, obj);
        if (calcBF(node)==2){

        }
        else if(calcBF(node)==-2){

        }
    }

    else if (obj.getID() < node->ID) {
        node->left_son = addNode(node->left_son, obj);
    }

        //illegal, node already exist
    else {
        return node;
    }


//update height
    node->height = max(calcHeight(node->left_son), calcHeight(node->right_son))+1;

    return node;

}


template<class T>
Node<T> * AvlTree<T>:: RightRotate(Node<T> * parent){

}


#endif
