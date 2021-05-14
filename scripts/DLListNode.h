#ifndef DSList_NODE_H
#define DSList_NODE_H

template <typename T>
class DSLinkedList;

template <typename T>

class DLListNode{
    friend class DSLinkedList<T>;

    public:
    DLListNode(const T& item, DLListNode<T>* nextPtr = nullptr, DLListNode<T>* prevPtr = nullptr) : next(nextPtr),prev(prevPtr), data(item){}
    DLListNode() : next(nullptr), prev(nullptr){}
    T getData();

    private:
    T data; //templatized data stored in node
    DLListNode* next; //pointer to the next node in list
    DLListNode* prev;
    };


template <typename T>
T DLListNode<T>::getData() //returns data stored in node
{
    return data;
}

#endif