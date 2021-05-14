//
// Created by tirem on 3/23/2021.
//

#ifndef PA04_AMAZING_DSSTACK_H
#define PA04_AMAZING_DSSTACK_H

template <class T>
class DSStack {
private:
    T* datas;
    int capacity;
    int size;

public:
    DSStack();
    DSStack(int);
    DSStack(const DSVector<T>& original);
    ~DSStack();

    void resize();
    void push_back(const T&);
    int getSize();
    int getCapacity();
    T peek();
    bool empty();
    void pop();
    void swap(int, int);
    DSStack<T>& operator=(const DSStack<T>&);
    T& operator[] (const int);


};
template <class T>
DSStack<T>::DSStack(){
    this->capacity = 10;
    this->size = 0;
    this->datas = new T[capacity];
}
template <class T>

DSStack<T>::DSStack(int v){
    this->capacity = v;
    this->size = 0;
    this->datas = new T[capacity];
}
template <class T>
DSStack<T>::DSStack(const DSVector<T>& original){
    this->capacity = original.capacity;
    this->size = original.size;
    this->datas = new T[capacity];

    for(int i = 0; i < original.size; i++){
        this->datas[i] = original.datas[i];
    }
}
template <class T>
DSStack<T>::~DSStack(){
    delete[] datas;
}
template <class T>
void DSStack<T>::resize(){
    T* temp = new T[2*capacity];
    for(int i = 0; i < size; i++){
        temp[i] = datas[i];
    }
    capacity *= 2;
    delete[] datas;
    datas = temp;
}
template <class T>
void DSStack<T>::push_back(const T& value){
    if(size == capacity){
        resize();
    }

    datas[size++] = value;
}
template <class T>
int DSStack<T>::getSize(){
    return size;
}
template <class T>
int DSStack<T>::getCapacity(){
    return capacity;
}
template <class T>
T DSStack<T>::peek(){
    return datas[size-1];
}
template <class T>
bool DSStack<T>::empty(){
    if(size == 0){
        return true;
    }
    return false;
};

template <class T>
void DSStack<T>::pop(){
    if(size == 0){
        throw std::out_of_range("Nothing to pop");
    }
    T empty;
    datas[size-1] = empty;
    size--;
}
template <class T>

void DSStack<T>::swap(int index1, int index2){
    T temp = datas[index1];
    datas[index1] = datas[index2];
    datas[index2] = temp;
}


template <class T>

DSStack<T>& DSStack<T>::operator=(const DSStack<T>& oldVector) {

    if (this == &oldVector) {
        return *this;
    }

    //Create new vector
    if(this->empty() == false){
        delete[] datas;
    }


        this->capacity = oldVector.capacity;
        this->size = oldVector.size;
        this->datas = new T[oldVector.capacity];
        for(int i = 0; i < oldVector.size;i++){
            this->datas[i]= oldVector[i];
    }

    return *this;
}

template <class T>
T& DSStack<T>::operator[] (const int index){
    if(index >= capacity){
        throw std::out_of_range("bad index value");
    }
    return datas[index];
}


#endif //PA04_AMAZING_DSSTACK_H
