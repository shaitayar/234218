#ifndef INC_234218_AVLTREE_H
#define INC_234218_AVLTREE_H

#include <iostream>

using std::ostream;
using std::max;
/*
int max(int a, int b) {
    return (a > b) ? a : b;
}
*/
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

    /**HELP FUNCTIONS*/
    Node<T, L> *addNode(Node<T, L> *node, T *obj);

    Node<T, L> *RightRotate(Node<T, L> *r);

    Node<T, L> *LeftRotate(Node<T, L> *r);

    Node<T, L> *RemoveNode(Node<T, L> *node, int NodeID);

    Node<T, L> *balance(Node<T, L> *node);


public:

    AvlTree(L compare) : compare(compare), root(NULL) {};

    ~AvlTree()=default;

    void DestroyTree();

    int calcHeight(Node<T, L> *node);

    void insert(T *obj);

    void deleteNode(int NodeID);

    Node<T, L> *RRRotate(Node<T, L> *r);

    Node<T, L> *LLRotate(Node<T, L> *r);

    Node<T, L> *LRRotate(Node<T, L> *r);

    Node<T, L> *RLRotate(Node<T, L> *r);

    Node<T, L> *find(int NodeID);

    void preOrder() const;

    void print() const;

    void inorder(Node<T, L> *) const;

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
Node<T, L> *AvlTree<T, L>::balance(Node<T, L> *node) {
    if (!node) return NULL;
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
int is_balanced(Node<T, L> *current) {
    int BF = calcBF(current);
    return (BF >= -1 && BF <= 1);
}

template<class T, class L>
Node<T, L> *createNode(T *obj) {
    auto *node = new Node<T, L>();
    node->obj = obj;
    node->father = NULL;
    node->left_son = NULL;
    node->right_son = NULL;
    node->height = 0;
    return node;
}

template<class T, class L>
void AvlTree<T, L>::insert(T *obj) {
    root = addNode(root, obj);
}

template<class T, class L>
void AvlTree<T, L>::deleteNode(int NodeID) {
    root = RemoveNode(root, NodeID);
}

template<class T, class L>
Node<T, L> *find_minimal(Node<T, L> *node) {
    Node<T, L> *iter = node;
    while (iter->left_son) {
        iter = iter->left_son;
    }
    return iter;
}


/***
 * Recursive RemoveNode function
 * complexity: O(logn)
 */
template<class T, class L>
Node<T, L> *AvlTree<T, L>::RemoveNode(Node<T, L> *node, int NodeID) {
    if (node == NULL) return node;

    //if node key is bigger than NodeID - then left subtree
    if (node->obj->getID()> NodeID) {
        node->left_son = RemoveNode(node->left_son, NodeID);
    } else if (node->obj->getID()< NodeID) {
        node->right_son = RemoveNode(node->right_son, NodeID);
    }
        //find the Node to delete
    else {
        //node has one or zero sons
        if (!node->left_son || !node->right_son) {
            //has left
            if (node->left_son) {
                Node<T, L> *temp = node->left_son;
                T *obj_to_del = node->obj;
                node->obj = temp->obj;
                /**not necessary*/
                node->left_son = temp->left_son;
                node->right_son = temp->right_son;

                delete obj_to_del;
                delete temp;

            }
            //has right
            else if (node->right_son) {

                Node<T, L> *temp = node->right_son;
                T *obj_to_del = node->obj;
                node->obj = temp->obj;
                /**not necessary*/
                node->left_son = temp->left_son;
                node->right_son = temp->right_son;

                delete obj_to_del;
                delete temp;

            }
                //no sons
            else {
                Node<T, L> *temp;
                temp = node;
                node=NULL;

                //delete temp->obj;
                delete temp;
            }
        }
            //node has two sons
        else {
            //o(log (current node height))
            Node<T, L> *temp = find_minimal(node->right_son);
            std::cout<<"here!"<<std::endl;
            node->obj = temp->obj;
            node->right_son = RemoveNode(node->right_son, node->obj->getID());
        }
    }
    if (node==NULL) return node;
    node->height = max(calcHeight(node->left_son), calcHeight(node->right_son)) + 1;
    return balance(node);
}


template<class T, class L>
int AvlTree<T, L>::calcHeight(Node<T, L> *node) {
    if (!node) return -1;
    else return node->height;
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::addNode(Node<T, L> *node, T *obj) {
    if (node == NULL) {
        node = createNode<T, L>(obj);
    } else if (compare(obj, node->obj) > 0) {
        node->right_son = addNode(node->right_son, obj);
        (node->right_son)->father = node;
    } else if (compare(obj, node->obj) < 0) {
        node->left_son = addNode(node->left_son, obj);
        (node->left_son)->father = node;
    }

        //illegal, node already exist
    else {
        return node;
    }

//update height
    node->height = max(calcHeight(node->left_son), calcHeight(node->right_son)) + 1;

    return balance(node);
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
        if ((r->father)->left_son == r) {
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
    root->father = NULL;

    return root;
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::LeftRotate(Node<T, L> *r) {
    Node<T, L> *pb = r->right_son;
    Node<T, L> *pc = pb->left_son;
    if (r->father) {
        if (compare(((r->father)->left_son)->obj, r->obj) == 0) {
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
    root->father = NULL;
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

template<class T, class L>
Node<T, L> *AvlTree<T, L>::find(int NodeID) {
    Node<T, L> *iter = this->root;
    while (iter && compare(iter->obj, NodeID)) {
        if (compare(iter->obj, NodeID) > 0) {
            iter = iter->left_son;
        } else iter = iter->right_son;
    }
    return iter;
}

template<class T, class L>
void AvlTree<T, L>::inorder(Node<T, L> *p) const {
    if (p == NULL) return;
    inorder(p->left_son);
    p->obj->print();
    inorder(p->right_son);
}

template<class T, class L>
void AvlTree<T, L>::print() const {
    inorder(root);
}



template<class T, class L>
void DestroyTreeAux(Node<T, L> *node) {
    if (!node) return;
    DestroyTreeAux(node->right_son);
    DestroyTreeAux(node->left_son);
    //delete node->obj;
    delete node;
}

template<class T, class L>
void AvlTree<T,L>::DestroyTree(){
    DestroyTreeAux(root);
}

#endif

