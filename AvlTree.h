#ifndef INC_234218_AVLTREE_H
#define INC_234218_AVLTREE_H

#include <iostream>
#include <math.h>
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
    int size;

    /**HELP FUNCTIONS*/
    Node<T, L> *addNode(Node<T, L> *node, T *obj, bool *is_success);

    Node<T, L> *RightRotate(Node<T, L> *r);

    Node<T, L> *LeftRotate(Node<T, L> *r);

    Node<T, L> *RemoveNode(Node<T, L> *node, T *Data, bool is_obj);

    Node<T, L> *balance(Node<T, L> *node);


public:

    explicit AvlTree(L compare) : compare(compare), root(NULL), size(0) {};

    ~AvlTree() = default;

    void DestroyTree(bool is_obj);

    int calcHeight(Node<T, L> *node);

    void insert(T *obj);

    void deleteNode(T *data, bool is_obj);

    Node<T, L> *RRRotate(Node<T, L> *r);

    Node<T, L> *LLRotate(Node<T, L> *r);

    Node<T, L> *LRRotate(Node<T, L> *r);

    Node<T, L> *RLRotate(Node<T, L> *r);

    Node<T, L> *find(int NodeID);

    Node<T, L> *getMaxNode();

    void print() const;

    void printToList(int **) const;

    void inorder(Node<T, L> *) const;

    int getSize() const { return size; }

    void getNMax(int, int **);

    void getMatch(int MinEmployeeID, int MaxEmployeeID, int MinSalary,
                  int MinGrade,
                  int *TotalNumOfEmployees, int *NumOfEmployees);

    void treeToArr(T **arr);

    void arrToTree(T **arr, int size);

    Node<T,L>* buildEmptyTree(int height_neede, Node<T,L> * parent);

    };

/*** AVL Implementation */
template<class T, class L>
int getNMaxAux(Node<T, L> *root, int **Employees, int n, int counter) {
    if (root == NULL || counter == n) return counter;
    counter = getNMaxAux(root->left_son, Employees, n, counter);
    (*Employees)[counter++] = root->obj->getMax();
    counter = getNMaxAux(root->right_son, Employees, n, counter);
    return counter;
}

template<class T, class L>
void AvlTree<T, L>::getNMax(int n, int **Employees) {
    getNMaxAux(root, Employees, n, 0);
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::getMaxNode() {
    Node<T, L> *iter = root;
    while (iter && iter->right_son) {
        iter = iter->right_son;
    }
    return iter;
}

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
    bool is_success = false;
    root = addNode(root, obj, &is_success);
    if (is_success) size++;
}

template<class T, class L>
void AvlTree<T, L>::deleteNode(T *data, bool is_obj) {

    if (!data) return;

    root = RemoveNode(root, data, is_obj);
    size--;
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
Node<T, L> *AvlTree<T, L>::RemoveNode(Node<T, L> *node, T *data, bool is_obj) {
    if (node == NULL) return node;

    //if node key is bigger than NodeID - then left subtree
    if (compare(node->obj, data) > 0) {
        node->left_son = RemoveNode(node->left_son, data, is_obj);
    } else if (compare(node->obj, data) < 0) {
        node->right_son = RemoveNode(node->right_son, data, is_obj);
    }
        //find the Node to delete
    else {
        //node has one or zero sons
        if (!node->left_son || !node->right_son) {
            //has left
            if (node->left_son) {
                Node<T, L> *temp = node->left_son;
                node->obj = temp->obj;
                /**not necessary*/
                node->left_son = temp->left_son;
                node->right_son = temp->right_son;
                if (is_obj) delete temp->obj;
                delete temp;

            }
                //has right
            else if (node->right_son) {

                Node<T, L> *temp = node->right_son;
                node->obj = temp->obj;
                /**not necessary*/
                node->left_son = temp->left_son;
                node->right_son = temp->right_son;
                if (is_obj) delete temp->obj;
                delete temp;

            }
                //no sons
            else {
                Node<T, L> *temp;
                temp = node;
                node = NULL;
                if (is_obj) delete temp->obj;
                delete temp;
            }
        }
            //node has two sons
        else {
            //o(log (current node height))
            Node<T, L> *temp = find_minimal(node->right_son);
            node->obj = temp->obj;
            node->right_son = RemoveNode(node->right_son, node->obj, is_obj);
        }
    }
    if (node == NULL) return node;
    node->height = max(calcHeight(node->left_son), calcHeight(node->right_son)) + 1;
    return balance(node);
}


template<class T, class L>
int AvlTree<T, L>::calcHeight(Node<T, L> *node) {
    if (!node) return -1;
    else return node->height;
}

template<class T, class L>
Node<T, L> *AvlTree<T, L>::addNode(Node<T, L> *node, T *obj, bool *is_success) {
    if (node == NULL) {
        node = createNode<T, L>(obj);
        *is_success = true;
    } else if (compare(obj, node->obj) > 0) {
        node->right_son = addNode(node->right_son, obj, is_success);
        (node->right_son)->father = node;
    } else if (compare(obj, node->obj) < 0) {
        node->left_son = addNode(node->left_son, obj, is_success);
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
    r->height = max(calcHeight(r->left_son), calcHeight(r->right_son)) + 1;
    pb->height = max(calcHeight(pb->left_son), calcHeight(pb->right_son)) + 1;
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
    r->height = max(calcHeight(r->left_son), calcHeight(r->right_son)) + 1;
    pb->height = max(calcHeight(pb->left_son), calcHeight(pb->right_son)) + 1;
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
int inorder_back(Node<T, L> *p, int **keys, int index) {
    if (p == NULL) return index;
    index = inorder_back(p->right_son, keys, index);
    (*keys)[index++] = p->obj->getID();
    index = inorder_back(p->left_son, keys, index);

    return index;
}

template<class T, class L>
void AvlTree<T, L>::print() const {
    inorder(root);
}

template<class T, class L>
void AvlTree<T, L>::printToList(int **keys) const {
    inorder_back(root, keys, 0);
}


template<class T, class L>
void DestroyTreeAux(Node<T, L> *node, bool is_obj) {
    if (!node) return;
    DestroyTreeAux(node->right_son, is_obj);
    DestroyTreeAux(node->left_son, is_obj);
    if (is_obj) delete node->obj;
    delete node;
}

template<class T, class L>
void AvlTree<T, L>::DestroyTree(bool is_obj) {
    DestroyTreeAux(root, is_obj);
}

template<class T, class L>
Node<T, L> *FindMin(Node<T, L> *root, int MinEmployeeID) {
    Node<T, L> *iter = root;
    while (iter->left_son->obj->getID() >= MinEmployeeID) {
        iter = iter->left_son;
    }
    return iter;
}

template<class T, class L>
void inorderRange(Node<T, L> *node, int MinEmployeeID, int MaxEmployeeID, int MinSalary, int MinGrade,
                  int *TotalNumOfEmployees, int *NumOfEmployees) {
    if (node == NULL) return;
    if (node->obj->getID() < MinEmployeeID) return;
    inorderRange(node->left_son, MinEmployeeID, MaxEmployeeID, MinSalary, MinGrade, TotalNumOfEmployees,
                 NumOfEmployees);
    if (node->obj->getID() > MaxEmployeeID) return;
    *TotalNumOfEmployees += 1;
    if (node->obj->getSalary() >= MinSalary && node->obj->getGrade() >= MinGrade) *NumOfEmployees += 1;
    inorderRange(node->right_son, MinEmployeeID, MaxEmployeeID, MinSalary, MinGrade, TotalNumOfEmployees,
                 NumOfEmployees);
}


template<class T, class L>
void AvlTree<T, L>::getMatch(int MinEmployeeID, int MaxEmployeeID, int MinSalary,
                             int MinGrade,
                             int *TotalNumOfEmployees, int *NumOfEmployees) {
    inorderRange(root, MinEmployeeID, MaxEmployeeID, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);
}

template<class T, class L>
int treeToArrAUX(Node<T, L> *root, T **arr, int index) {
    if (root == NULL) return index;
    index = treeToArrAUX(root->left_son, arr, index);
    (arr)[index++] = root->obj;
    index = treeToArrAUX(root->right_son, arr, index);

    return index;
}

template<class T, class L>
void AvlTree<T, L>::treeToArr(T **arr) {
    treeToArrAUX(root, arr, 0);
}
/*
template<class T, class L>
Node<T, L> *arrToTreeAux(T **arr, int start, int end, int h) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node<T, L> *root = createNode<T, L>(arr[mid]);
    root->father = NULL;
    root->left_son = arrToTreeAux<T, L>(arr, start, mid -1, h++);
    if (root->left_son) root->left_son->father = root;
    root->right_son = arrToTreeAux<T, L>(arr, mid + 1, end, h++);
    if (root->right_son) root->right_son->father = root;
    root->height = h;
    return root;
}
*/

template <class T, class L>
Node<T,L>* AvlTree<T, L>::buildEmptyTree(int height_needed, Node<T,L> * parent){
    if (height_needed<=0) return NULL;
    auto node = new Node<T,L>();
    node->height=height_needed-1;
    node->father=parent;
    node->left_son = buildEmptyTree(height_needed-1, node);
    node->right_son = buildEmptyTree(height_needed-1, node);
    return node;
}
template <class T, class L>
int inorderBackRemoveExtra(Node<T,L> * node, int  nodes_to_remove){
    if (node==NULL || nodes_to_remove<=0) return nodes_to_remove;
    nodes_to_remove = inorderBackRemoveExtra(node->right_son, nodes_to_remove);
    nodes_to_remove= inorderBackRemoveExtra(node->left_son, nodes_to_remove);
    if(node->height ==0) {
        if (node->father->left_son ==node) node->father->left_son = NULL;
        else if(node->father->right_son ==node) node->father->right_son = NULL;
        delete node;
        std::cout<<"removed!"<<std::endl;
        return nodes_to_remove-1;
    }
    return nodes_to_remove;
}

template<class T, class L>
int inorderFillTree(Node<T,L> * node, T** arr, int size, int index){
    if (node==NULL ||index==size) return index;
    index = inorderFillTree(node->left_son,arr,size, index);
    node->obj= arr[index++];
    index = inorderFillTree(node->right_son, arr, size, index);
    return index;
}

template<class T, class L>
void AvlTree<T, L>::arrToTree(T **arr, int size) {
    int height_needed = std::ceil( std::log2(size));
    int current_nodes = std::pow(2,height_needed);
    int nodes_to_remove = current_nodes-size-1;
    root = buildEmptyTree(height_needed, NULL);
    inorderBackRemoveExtra(root, nodes_to_remove);
    inorderFillTree(root, arr,size,0);
}

#endif

