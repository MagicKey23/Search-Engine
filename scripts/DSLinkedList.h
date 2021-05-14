#ifndef DLLINKEDLIST_H
#define DLLINKEDLIST_H

#include <iostream>

using namespace std;

template <typename T>
class DLListNode {
public:
    DLListNode() {
        next = prev = nullptr;
    }
    DLListNode(const T& el, DLListNode *n = nullptr, DLListNode *p = nullptr) {
        data = el; next = n; prev = p;
    }
    T data;
    DLListNode *next, *prev;
};

template <typename T>
class DSLinkedList //linked list of DLListNode objects
{
public:
    DSLinkedList(){
        head = tail = nullptr;
    }
    DSLinkedList(const DSLinkedList<T>& other) = delete;
    DSLinkedList(DSLinkedList<T>&& other) = delete;
    ~DSLinkedList();

    void print(); //prints the contents of the linked list
    DLListNode<T>* search(T); //searches for a value in the linked list and returns the point to object that contains that value
    T back();
    T front();
    int getSize();
    void pop();
    T peek();
    void push_front(T); //inserts new DLListNode before the first DLListNode in the list
    void push_back(T); //inserts new DLListNode after the last DLListNode in the list\
    //OverLoad
    DSLinkedList<T>& operator=(const DSLinkedList<T>& other) = delete;
    DSLinkedList<T>& operator=(DSLinkedList<T>&& other) = delete;

// Inner class Iterator
    class Iterator {
        friend class DSLinkedList;
    private:
        DLListNode<T> *DLListNodePtr;
        // The constructor is private, so only our friends
        // can create instances of Iterators.
        Iterator(DLListNode<T> *newPtr) : DLListNodePtr(newPtr) {}
    public:
        Iterator() : DLListNodePtr(nullptr) {}

        // Overload for the comparison operator !=
        bool operator!=(const Iterator& itr) const {
            return DLListNodePtr != itr.DLListNodePtr;
        }

        // Overload for the dereference operator *
        T& operator*() const {
            return DLListNodePtr->data;
        }

        // Overload for the postincrement operator ++
        Iterator operator++(int) {
            Iterator temp = *this;
            DLListNodePtr = DLListNodePtr->next;
            return temp;
        }
    }; // End of inner class Iterator

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    
private:
    DLListNode<T> *head; //stores the pointer of first object in the linked list
    DLListNode<T> *tail; //stored the pointer of the last object in the linked list
    bool isEmpty(); //utility functions used to see if the list contains no elements
    int size = 0;
};



template <typename T>
DSLinkedList<T>::~DSLinkedList()
{
    if ( !isEmpty() ) // List is not empty
    {
        DLListNode<T> *currentPtr = head;
        DLListNode<T> *tempPtr;

        while ( currentPtr != 0 ) // delete remaining DLListNodes
        {
            tempPtr = currentPtr;
            currentPtr = currentPtr->next;
            delete tempPtr;
        }
    }
}

template <typename T>
bool DSLinkedList<T>::isEmpty()
{
    if(head == nullptr && tail == nullptr) //if the start pointer and end pointer are NULL then the list is empty
        return true;
    else
        return false;

}

template <typename T>
void DSLinkedList<T>::push_front(T dataIn)
{
    if(isEmpty()) //if the list is empty create first element of the list
    {
        DLListNode<T> * newPtr = new DLListNode<T>(dataIn); //creates new DLListNode
        head  = newPtr; //head and tail pointer are same becuase there is only one object in list
        tail = newPtr;
    }else //if DLListNode(s) exist in list insert additional object before the first
    {
        DLListNode<T> * newPtr = new DLListNode<T>(dataIn);
        newPtr->next = head; //the next pointer of the new DLListNode points to the DLListNode that was previously first
        head = newPtr; //the pointer for the new DLListNode is now the starting DLListNode
        head->next->prev = newPtr; // the next pointer in the front of head now point to head as prev DLListNode
    }
    size++;
}

template <typename T>
void DSLinkedList<T>::push_back(T dataIn)
{
    if(isEmpty()) //if the list is empty create first element of the list (same as first case in insert at begin)
    {
        DLListNode<T> * newPtr = new DLListNode<T>(dataIn);
        head = newPtr;
        tail = newPtr;

    }else //if DLListNode(s) exist in the list then insert new DLListNode at the end of the list
    {
        DLListNode<T> * newPtr = new DLListNode<T>(dataIn);
        newPtr->prev = tail;
        tail->next = newPtr; //the current last DLListNode's next pointer points to the new DLListNode
        tail = newPtr; //the new DLListNode is now the last DLListNode in the list

    }

    size++;
}


template <typename T>
void DSLinkedList<T>::print()
{
    if(isEmpty())
    {
        cout << "List is Empty" << endl;

    }else
    {
        DLListNode<T> * currentPtr = head;

        cout << "List datas: ";
        while(currentPtr != nullptr) //prints until the end of the list is reached
        {
            cout << currentPtr->data << ' ';
            currentPtr = currentPtr->next; //moves to next DLListNode in list
        }
        cout << endl;
    }
}

template <typename T>
DLListNode<T>* DSLinkedList<T>::search(T key) //search functions that searches for DLListNode that contains data equal to the key
{
    DLListNode<T>* currentNode;
    bool found = false;

    currentNode = head;

    while((!found) && (currentNode != nullptr)) //runs through list until data is found within a DLListNode or end of list is reached
    {
        if(currentNode->data == key) //if the DLListNode's data equals the key then the DLListNode has been found
            found = true;
        else
            currentNode = currentNode->next; //moves to next DLListNode in list
    }
    return currentNode; //returns pointer to the DLListNode that contains data equal to key (NULL if not found)
}

template <typename T>
T DSLinkedList<T>::back(){
    return tail->data;
}

template <typename T>
T DSLinkedList<T>::front(){
    return head->data;
}

template <typename T>
int DSLinkedList<T>::getSize(){
    return size;
}

template <typename T>

void DSLinkedList<T>::pop(){
    if(size == 1){
        DLListNode <T> *temp;
        temp = head;
        head = nullptr;
        tail = nullptr;
        delete temp;
    }else if(!isEmpty()) {
        DLListNode <T> *temp;
        temp = tail;
        tail = tail->prev;
        delete temp;
    }else{
        cout << "no data" << endl;
    }
    size--;

}

template <typename T>
T DSLinkedList<T>::peek() {
    if (!isEmpty()) {
        return head->getData();
    } else {
        cout << "no data" << endl;
    }
}


#endif