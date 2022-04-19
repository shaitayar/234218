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
    Node *father;
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

    Node<T> * RightRotate (Node<T> * r);
    Node<T> * LeftRotate (Node<T> * r);

    Node<T> *LRRotate(Node<T> *r);

    Node<T> *RLRotate(Node<T> *r);

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
        return node->left_son->height+1;
    } else if (node->right_son) {
        return -(node->right_son->height+1);
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
    node->father=NULL;
    node->left_son = NULL;
    node->right_son = NULL;
    node->height = 0;
    return node;
}

template<class T>
void AvlTree<T>::insert(const T &obj) {
    root= addNode(root, obj);
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
    else return node->height;
}

//ROTATE - IMPORTANT TO ADD
template<class T>
Node<T> *AvlTree<T>::addNode(Node<T> *node, const T &obj) {
    if (node==NULL) {
        node = createNode(obj);
    }

    else if (obj.getID() > node->ID) {
        node->right_son = addNode(node->right_son, obj);
        (node->right_son)->father = node;
    }

    else if (obj.getID() < node->ID) {
        node->left_son = addNode(node->left_son, obj);
        (node->left_son)->father = node;

    }

    //illegal, node already exist
    else {
        return node;
    }


//update height
    node->height = max(calcHeight(node->left_son), calcHeight(node->right_son))+1;


    if (calcBF(node)==2){
        if(calcBF(node->left_son)>=0){
            return LeftRotate(node);
        }
        else if(calcBF(node->left_son)==-1){
            return LRRotate(node);
        }
    }
    else if(calcBF(node)==-2){
        if(calcBF(node->right_son)<=0){
            return RightRotate(node);
        }
        else if(calcBF(node->right_son)==1){
            return RLRotate(node);
        }
    }

    return node;

}


template<class T>
Node<T> * AvlTree<T>:: LeftRotate(Node<T> * r){
    Node<T> * pb = r->left_son;
    Node<T> * pc = pb->right_son;
    if(r->father) {
        if (((r->father)->left_son)->ID == r->ID) {
            r->father->left_son = pb;
        } else {
            r->father->right_son = pb;
        }
    }
    pb->right_son = r;
    this->root = pb;
    r->left_son = pc;

    //update height
    pb->height = max(calcHeight(pb->left_son), calcHeight(pb->right_son))+1;
    r->height = max(calcHeight(r->left_son), calcHeight(r->right_son))+1;

    return root;
}

template<class T>
Node<T> * AvlTree<T>::RightRotate (Node<T> * r){
    Node<T> * pb = r->right_son;
    Node<T> * pc = pb->left_son;
    if(r->father) {
        if (((r->father)->left_son)->ID == r->ID) {
            r->father->left_son = pb;
        } else {
            r->father->right_son = pb;
        }
    }
    pb->left_son = r;
    this->root = pb;
    r->right_son = pc;

    //update height
    pb->height = max(calcHeight(pb->left_son), calcHeight(pb->right_son))+1;
    r->height = max(calcHeight(r->left_son), calcHeight(r->right_son))+1;

    return root;
}

template<class T>
Node<T> *AvlTree<T>::LRRotate(Node<T> *r){
    LeftRotate(r->left_son);
    return RightRotate(r);
}

template<class T>
Node<T> *AvlTree<T>::RLRotate(Node<T> *r){
    RightRotate(r->right_son);
    return LeftRotate(r);
}

#endif

