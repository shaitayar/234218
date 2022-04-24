#ifndef INC_234218_AVLTREE_H
#define INC_234218_AVLTREE_H

#include <iostream>
#include <memory>

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;


using std::ostream;
using std::shared_ptr;

int max(int a, int b) {
    return (a > b) ? a : b;
}


template<class T, class L>
struct Node {
    T *obj;
    Node *father;
    Node *left_son;
    Node *right_son;
    int height;
};

template<class T, class L>
class AvlTree {
    Node<T, L> *root;

    L compare;

    Node<T, L> *addNode(Node<T, L> *node, T *obj, StatusType *status);

    Node<T, L> *RightRotate(Node<T, L> *r);

    Node<T, L> *LeftRotate(Node<T, L> *r);

public:

    AvlTree(L compare) : compare(compare), root(NULL){};

    ~AvlTree() = default;

    int calcHeight(Node<T, L> *node);

    void insert(T *obj, StatusType *status);

    Node<T, L> *RemoveNode(int NodeID);

    Node<T, L> *RRRotate(Node<T, L> *r);

    Node<T, L> *LLRotate(Node<T, L> *r);


    Node<T, L> *LRRotate(Node<T, L> *r);

    Node<T, L> *RLRotate(Node<T, L> *r);

    /***maybe needed with O(1)*/
    void preOrder() const;

    void inorder() const;

    void postOrder() const;
};

/*** AVL Implementation */


template<class T, class L>
int calcBF(Node<T, L> *node) {
    if (node->left_son && node->right_son) {
        return node->left_son->height - node->right_son->height;
    } else if (node->left_son) {
        return node->left_son->height + 1;
    } else if (node->right_son) {
        return -(node->right_son->height + 1);
    } else return 0;
};


template<class T, class L>
int is_balanced(Node<T, L> *current) {
    int BF = calcBF(current);
    return (BF >= -1 && BF <= 1);
}

template<class T, class L>
Node<T,L> *createNode(T *obj) {
    auto *node = new Node<T,L>();
    node->obj = obj;
    node->father = NULL;
    node->left_son = NULL;
    node->right_son = NULL;
    node->height = 0;
    return node;
}

template<class T, class L>
void AvlTree<T, L>::insert(T *obj, StatusType *status) {
    status = (StatusType *) SUCCESS;
    root = addNode(root, obj, status);
}


template<class T, class L>
Node<T, L> *AvlTree<T, L>::RemoveNode(int NodeID) {
    //find node

    //remove

    //rotations
}


template<class T, class L>
int AvlTree<T, L>::calcHeight(Node<T, L> *node) {
    if (!node) return -1;
    else return node->height;
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::addNode(Node<T, L> *node, T *obj, StatusType *status) {
    if (node == NULL) {
        node = createNode<T,L>(obj);
    } else if (compare(obj, node->obj) > 0) {
        node->right_son = addNode(node->right_son, obj, status);
        (node->right_son)->father = node;
    } else if (compare(obj, node->obj) < 0) {
        node->left_son = addNode(node->left_son, obj, status);
        (node->left_son)->father = node;
    }

        //illegal, node already exist
    else {
        *status = FAILURE;
        return node;
    }

//update height
    node->height = max(calcHeight(node->left_son), calcHeight(node->right_son)) + 1;


    if (calcBF(node) == 2) {
        if (calcBF(node->left_son) >= 0) {
            return LLRotate(node);
        } else if (calcBF(node->left_son) == -1) {
            return LRRotate(node);
        }
    } else if (calcBF(node) == -2) {
        if (calcBF(node->right_son) <= 0) {
            return RRRotate(node);
        } else if (calcBF(node->right_son) == 1) {
            return RLRotate(node);
        }
    }

    return node;

}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::RRRotate(Node<T, L> *r) {
    return LeftRotate(r);
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::LLRotate(Node<T, L> *r) {
    return RightRotate(r);
}


template<class T, class L>
Node<T, L> *AvlTree<T, L>::RightRotate(Node<T, L> *r) {
    Node<T, L> *pb = r->left_son;
    Node<T, L> *pc = pb->right_son;
    if (r->father) {
        if (compare(((r->father)->left_son)->obj, r->obj)==0) {
            r->father->left_son = pb;
        } else {
            r->father->right_son = pb;
        }
    }
    pb->right_son = r;
    this->root = pb;
    r->left_son = pc;

    //update height
    pb->height = max(calcHeight(pb->left_son), calcHeight(pb->right_son)) + 1;
    r->height = max(calcHeight(r->left_son), calcHeight(r->right_son)) + 1;
    root->father=NULL;

    return root;
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::LeftRotate(Node<T, L> *r) {
    Node<T, L> *pb = r->right_son;
    Node<T, L> *pc = pb->left_son;
    if (r->father) {
        if (compare(((r->father)->left_son)->obj, r->obj)==0) {
            r->father->left_son = pb;
        } else {
            r->father->right_son = pb;
        }
    }
    pb->left_son = r;
    this->root = pb;
    r->right_son = pc;

    //update height
    pb->height = max(calcHeight(pb->left_son), calcHeight(pb->right_son)) + 1;
    r->height = max(calcHeight(r->left_son), calcHeight(r->right_son)) + 1;
    root->father=NULL;
    return root;
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::LRRotate(Node<T, L> *r) {
    LeftRotate(r->left_son);
    return RightRotate(r);
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::RLRotate(Node<T, L> *r) {
    RightRotate(r->right_son);
    return LeftRotate(r);
}


#endif

