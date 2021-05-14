#include "AvlTree.h"

AvlNode* AvlTree::rightRotate(AvlNode *y){

    AvlNode *x = y->left;
    AvlNode *temp2 = x->right;

    // Perform rotation
    x -> right = y;
    y -> left = temp2;

    return x;
}

AvlNode* AvlTree::leftRotate(AvlNode *x){
    AvlNode *y = x->right;
    AvlNode *temp2 = y->left;

    // Perform rotation
    y -> left = x;
    x -> right = temp2;

    return y;
}




int AvlTree::getBalance(AvlNode *node){
    if(node == nullptr){
        return -1;
    }

    return getHeight(node->left) - getHeight(node->right);
}


AvlNode* AvlTree::insert(AvlNode *r, AvlNode *newNode){
    if(r == nullptr){
        //why didn't the r change
        r = newNode;
        return r;
    }else if(newNode->element < r->element){
        r->left = insert(r->left, newNode);
    }else if(newNode->element > r->element){
        r->right = insert(r->right, newNode);
    }else{
        cout << "Duplicate Exist" << endl;
        return r;
    }


    int balanceVal = getBalance(r);
    //left left case
    if(balanceVal > 1 && newNode->element < r->left->element){
        return rightRotate(r);
    }//right right case
    else if(balanceVal < -1 && newNode->element > r->right->element){
        return leftRotate(r);

    }//left right case
    else if(balanceVal > 1 && newNode->element > r->left->element){
        r->left = leftRotate(r->left);
        return rightRotate(r);

    }//right left case
    else if(balanceVal < -1 && newNode->element < r->right->element){


        r->right = rightRotate(r->right);
        return leftRotate(r);
    }
    return r;


}



AvlNode* AvlTree::deleteNode(AvlNode *node, Index element){
    //base case
    if(node == nullptr){
        return nullptr;
    }
        //If the key is to be delete is smaller than the r's key
        //then it lies in the left subtree
    else if(element < node->element){
        node->left = deleteNode(node->left, element);
    }

        //If the key to be deleted is greater than the r's key,
        //then it is  lies in right subtree
    else if(element > node->element){
        node->right = deleteNode(node->right, element);
    }else{
        //Value match
        if(node->left == nullptr){
            AvlNode* temp = node->right;
            delete node;
            return temp;
        }else if(node->right == nullptr){
            AvlNode* temp = node->left;
            delete node;
            return temp;
        }else{
            AvlNode* temp = minValue(node->right);
            node->element = temp->element;
            node->right = deleteNode(node->right, temp->element);
        }

    }
    //Rebalance
    int balanceVal = getBalance(node);
    if(balanceVal == 2 && getBalance(node->left) >= 0){
        return rightRotate(node);
    }else if(balanceVal == 2 && getBalance(node->left) == -1){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }else if(balanceVal == -2 && getBalance(node->right) <= 0){
        return leftRotate(node);
    }else if(balanceVal == -2 && getBalance(node->right) == 1){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;


}



int AvlTree::getHeight(AvlNode* r){
    if(r == nullptr){
        return -1;
    }else{
        int lHeight = getHeight(r->left);
        int rHeight = getHeight(r->right);

        if(lHeight > rHeight){
            return(lHeight + 1);
        }else{ return(rHeight +1); }
    }

}


void AvlTree::destroyAllNode(AvlNode* node){
    if(node){
        destroyAllNode(node->left);
        destroyAllNode(node->right);
        delete node;
    }

}




AvlNode* AvlTree::search(AvlNode* node, Index element){
    if(node == NULL || node->element == element) {
        return node;
    }

    if(element < node->element){
        return search(node->left, element);
    }

    if(element > node->element){
        return search(node->right, element);
    }
    return NULL;
}


AvlNode* AvlTree::minValue(AvlNode *node) {
    AvlNode *currentNode = node;
    while(currentNode->left != nullptr){
        currentNode = currentNode->left;
    }
    return currentNode;
}




void AvlTree::printTree(AvlNode *node, int space) {
    if(node == nullptr){
        return;
    }
    space += SPACE;
    printTree(node->right, space);
    cout << endl;
    for (int i = SPACE; i < space; i++)
        cout << " "; //
    cout << node->getData().getWord() << endl;
    printTree(node->left, space);

}


void AvlTree::replace(AvlNode *r, Index oldElement ,Index newElement){
    auto* newNode = new AvlNode(newElement);
    deleteNode(r, oldElement);
    insert(r, newNode);
}


