
#ifndef SEARCH_ENGINE_HASHTABLE_H
#define SEARCH_ENGINE_HASHTABLE_H

#define TABLE_SIZE 1000003 // use a large prime number
#include <iostream>
#include <iomanip>
#include "hashFunction.h"
#include <string>

using namespace std;

template <class TKey, class TValue> class Hashtable;
template <class TKey, class TValue> class HashtableItem;
template <class TKey, class TValue> class HashtableDataMembers;

template <class TKey, class TValue> class HashtableDataMembers
{
public:
    HashtableItem<TKey, TValue> **table;
    HashtableItem<TKey, TValue> *cursorItem;
    unsigned int cursorIndex, tableSize;
    HashtableDataMembers();
    ~HashtableDataMembers();
};

template <class TKey, class TValue> class Hashtable
{
private:
    HashtableDataMembers<TKey, TValue> *dm;

public:
    Hashtable();
    Hashtable(const Hashtable &obj);
    ~Hashtable();
    bool Add(const TKey &key, const TValue &value); // Insert new Value
    const Hashtable<TKey, TValue> &operator=(const Hashtable<TKey, TValue> &obj); //Assignment operator
    HashtableItem<TKey, TValue> *operator[](const TKey &key) const;
    void Remove(const TKey &key); // removes exist table
    void Clear(); // Remove everything
    HashtableItem<TKey, TValue> *GetFirst(); // Iterator
    HashtableItem<TKey, TValue> *GetNext();
    TValue Search(const TKey &key);
    bool KeyExist(const TKey &key);
    void ChangeValue(const TKey &key, const TValue &value);

};

template <class TKey, class TValue>
class HashtableItem
{
private:
    HashtableItem<TKey, TValue> *next;
    TKey key;
    TValue value;

    // keep these private to prevent the client from creating this object
    HashtableItem() {}
    HashtableItem(const TKey &key, const TValue &value);
    ~HashtableItem();

public:
    const TKey &Key() const;
    const TValue &Value() const;
    const TValue &operator=(const TValue &value);
   //Friend Functions
    friend bool Hashtable<TKey, TValue>::Add(const TKey &key, const TValue &value);
    friend HashtableDataMembers<TKey, TValue>::HashtableDataMembers();
    friend HashtableDataMembers<TKey, TValue>::~HashtableDataMembers();
    friend void Hashtable<TKey, TValue>::Remove(const TKey &key);
    friend const Hashtable<TKey, TValue> &Hashtable<TKey, TValue>::operator=(const Hashtable<TKey, TValue> &obj);
    friend HashtableItem<TKey, TValue> *Hashtable<TKey, TValue>::operator[](const TKey &key) const;
    friend HashtableItem<TKey, TValue> *Hashtable<TKey, TValue>::GetNext();
    friend void Hashtable<TKey, TValue>::Clear();
    friend TValue Hashtable<TKey, TValue>::Search(const TKey &key);
    friend bool Hashtable<TKey, TValue>::KeyExist(const TKey &key);
    friend void Hashtable<TKey, TValue>::ChangeValue(const TKey &key, const TValue &value);

};





// class HashtableDataMembers
template <class TKey, class TValue>
HashtableDataMembers<TKey, TValue>::HashtableDataMembers()
{
    cursorItem = nullptr;
    cursorIndex = 0;
    tableSize = TABLE_SIZE + 1; // add one to the TABLE_SIZE because the int hash_func can actually return TABLE_SIZE
    table = new HashtableItem<TKey, TValue>*[tableSize]();
    for (unsigned int i = 0; i < tableSize; table[i++] = nullptr);
}
template <class TKey, class TValue>
HashtableDataMembers<TKey, TValue>::~HashtableDataMembers()
{
    for (unsigned int i = 0; i < tableSize; i++)
    {
        if (table[i])
        {
            delete table[i];
            table[i] = nullptr; // clean-up the memory
        }
    }
    delete[] table;
}




// class Hashtable

template <class TKey, class TValue>
bool Hashtable<TKey, TValue>::Add(const TKey &key, const TValue &value)
{
    hashFunction hash;
    unsigned int i = hash.hash_function(key);
    HashtableItem<TKey, TValue> **nodePointer;
    for (nodePointer = &dm->table[i]; (*nodePointer) && ((*nodePointer)->key != key); nodePointer = &(*nodePointer)->next);
    if (*nodePointer) { // then found
        return false;
    }
    (*nodePointer) = new HashtableItem<TKey, TValue>(key, value);
    return true;

}

template <class TKey, class TValue>
bool Hashtable<TKey, TValue>::KeyExist(const TKey &key){
    hashFunction hash;
    unsigned int i = hash.hash_function(key);
    HashtableItem<TKey, TValue> **nodePointer;
    for (nodePointer = &dm->table[i]; (*nodePointer) && ((*nodePointer)->key != key); nodePointer = &(*nodePointer)->next);
    if (*nodePointer) { // then found
        return true;
    }
    return false;

}

template <class TKey, class TValue>

void Hashtable<TKey, TValue>::ChangeValue(const TKey &key, const TValue &value){
    hashFunction hash;
    int i = hash.hash_function(key);
    HashtableItem<TKey, TValue> **nodePointer = &dm->table[i];
    if((*nodePointer)->key == key){
        (*nodePointer)->operator=(value);
    }

}



template <class TKey, class TValue>
Hashtable<TKey, TValue>::Hashtable()
{
    dm = new HashtableDataMembers<TKey, TValue>();
}
template <class TKey, class TValue>
Hashtable<TKey, TValue>::Hashtable(const Hashtable &obj)
{
    dm = new HashtableDataMembers<TKey, TValue>();
    this->operator=(obj);
}
template <class TKey, class TValue>
Hashtable<TKey, TValue>::~Hashtable()
{
    delete dm;
    dm = nullptr;
}
template <class TKey, class TValue>
const Hashtable<TKey, TValue> &Hashtable<TKey, TValue>::operator=(const Hashtable<TKey, TValue> &obj)
{
    if (this != &obj)
    {
        unsigned int i;
        Clear();
        if (dm->tableSize != obj.dm->tableSize)
        {
            if (dm->table)
                delete[]dm->table;
            dm->tableSize = obj.dm->tableSize;
            dm->table = new HashtableItem<TKey, TValue>*[dm->tableSize]();
            for (i = 0; i < dm->tableSize; dm->table[i++] = nullptr);
        }
        dm->cursorIndex = obj.dm->cursorIndex;
        for (i = 0; i < obj.dm->tableSize; i++)
        {
            HashtableItem<TKey, TValue> **objectPointer, **nodePointer;
            objectPointer = &obj.dm->table[i];
            nodePointer = &dm->table[i];
            while (*objectPointer)
            {
                (*nodePointer) = new HashtableItem<TKey, TValue>((*objectPointer)->key, (*objectPointer)->value);
                if (obj.dm->cursorItem == *objectPointer)
                    dm->cursorItem = *nodePointer;
                nodePointer = &(*nodePointer)->next;
                objectPointer = &(*objectPointer)->next;
            }
        }
    }
    return (*this);
}

template <class TKey, class TValue>
HashtableItem<TKey, TValue> *Hashtable<TKey, TValue>::operator[](const TKey &key) const
{
    hashFunction hash;
    unsigned int i = hash.hash_function(key);
    HashtableItem<TKey, TValue> *pnode;
    for (pnode = dm->table[i]; pnode && (pnode->key != key); pnode = pnode->next);
    return pnode;
}
template <class TKey, class TValue> void Hashtable<TKey, TValue>::Remove(const TKey &key)
{
    unsigned int i = hash_function(key);
    HashtableItem<TKey, TValue> **nodePointer, *tmp;
    for (nodePointer = &dm->table[i]; (*nodePointer) && ((*nodePointer)->key != key); nodePointer = &(*nodePointer)->next);
    if (*nodePointer)
    {
        tmp = (*nodePointer);
        (*nodePointer) = (*nodePointer)->next;
        tmp->next = nullptr;
        delete tmp;
    }
}
template <class TKey, class TValue>
void Hashtable<TKey, TValue>::Clear()
{
    for (unsigned int i = 0; i < dm->tableSize; i++)
    {
        if (dm->table[i])
        {
            delete dm->table[i];
            dm->table[i] = nullptr;
        }
    }
}
template <class TKey, class TValue>
HashtableItem<TKey, TValue> *Hashtable<TKey, TValue>::GetFirst()
{
    unsigned int i;
    dm->cursorItem = nullptr;
    dm->cursorIndex = 0;

    for (i = dm->cursorIndex; i < dm->tableSize && dm->table[i] == nullptr; i++);
    if (i < dm->tableSize)
    {
        dm->cursorItem = dm->table[i];
        dm->cursorIndex = i;
    }
    return dm->cursorItem;
}
template <class TKey, class TValue>
HashtableItem<TKey, TValue> *Hashtable<TKey, TValue>::GetNext()
{
    if (dm->cursorItem && dm->cursorItem->next)
        dm->cursorItem = dm->cursorItem->next;
    else
    {
        unsigned int i;
        for (i = dm->cursorIndex + 1; i < dm->tableSize && dm->table[i] == nullptr; i++);
        if (i < dm->tableSize)
        {
            dm->cursorItem = dm->table[i];
            dm->cursorIndex = i;
        }
        else
        {
            dm->cursorItem = nullptr;
            dm->cursorIndex = 0;
        }
    }
    return dm->cursorItem;
}

template<class TKey, class TValue>
TValue Hashtable<TKey, TValue>::Search(const TKey &key) {
    hashFunction hash;
    unsigned int i  = hash.hash_function(key);
    HashtableItem<TKey, TValue> **nodePointer = &dm->table[i];
        if((*nodePointer)->key == key){
            return (*nodePointer)->value;
        }
    return 0;
}


// class HashtableItem
template <class TKey, class TValue>
HashtableItem<TKey, TValue>::HashtableItem(const TKey &xKey, const TValue &xValue)
{
    key = xKey;
    value = xValue;
    next = nullptr;
}
template <class TKey, class TValue>
HashtableItem<TKey, TValue>::~HashtableItem()
{
    if (this->next)
    {
        delete this->next;
        this->next = nullptr; // clean-up memory
    }
}
template <class TKey, class TValue>
const TKey &HashtableItem<TKey, TValue>::Key() const
{
    return this->key;
}
template <class TKey, class TValue>
const TValue &HashtableItem<TKey, TValue>::Value() const
{
    return this->value;
}
template <class TKey, class TValue>
const TValue &HashtableItem<TKey, TValue>::operator=(const TValue &value)
{
    this->value = value;
    return value;
}




#endif //SEARCH_ENGINE_HASHTABLE_H
