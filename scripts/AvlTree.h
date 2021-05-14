

#ifndef SEARCH_ENGINE_AVLTREE_H
#define SEARCH_ENGINE_AVLTREE_H
#include <string>
#include <iostream>
#include "../Index.h"

#define SPACE 8

class AvlNode{

public:


    explicit AvlNode(const Index &theElement) : element(theElement) {
        this->element = theElement;
        left = nullptr;
        right = nullptr;
    }
    

    Index getData(){
        return element;
    }

    Index element;
    AvlNode *left;
    AvlNode *right;
};




    class AvlTree{

    public:
        AvlNode *root;
        AvlTree(){
            root = nullptr;
        }
        AvlTree(const AvlTree & rhs) : root(nullptr){ *this = rhs; }
        ~AvlTree(){
            destroyAllNode(root);
        }

        AvlNode *rightRotate(AvlNode*);
        AvlNode *leftRotate(AvlNode*);
        AvlNode* insert(AvlNode *r, AvlNode *newNode);
        int getBalance(AvlNode*);
        AvlNode *deleteNode(AvlNode*, Index) ;
        AvlNode * search(AvlNode*, Index);
        void destroyAllNode(AvlNode*);
        int getHeight(AvlNode*);
        AvlNode* minValue(AvlNode*);
        void printTree(AvlNode*, int);
        void replace(AvlNode*, Index, Index);
};




#endif //SEARCH_ENGINE_AVLTREE_H
