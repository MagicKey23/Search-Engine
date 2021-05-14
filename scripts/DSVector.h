#ifndef INC_20F_AUTO_IDX_DSVECTOR_H
#define INC_20F_AUTO_IDX_DSVECTOR_H
#include <stdexcept>
    template<class T>
    class DSVector{
    private:
        T* datas;
        int capacity;
        int size;

    public:
    /*
     * Constructor
     */
    void resize();
    DSVector();
    DSVector(int);
    DSVector(const DSVector<T>& original);


    /*
     * Assign operator
     */
    DSVector<T>& operator=(const DSVector<T>&);
    T& operator[] (const int);
    /*
     * destructor
     */
    ~DSVector();
    /**
     * Methods
     */
     /*
      * at
      * @param index
      * @return value at the location at index
      */
    T& at(const int);
    /*
     * Push back
     * add value to the back of the index
     *
     */
    void push_back(const T&);
    int getSize();
    int getCapacity();
    T& front();
    T& back();
    T* cbegin();
    T* cend();
    T pop_back();
    void swap(int, int);
    void insert(T& , const int&);
    void clear();
    bool empty();
    bool isExist(const T&);
    void removeAt(int);
};

template <class T>
DSVector<T>::DSVector(){
    this->capacity = 10;
    this->size = 0;
    this->datas = new T[capacity];
};

template <class T>
DSVector<T>::DSVector(int v){
    this->capacity = v;
    this->size = 0;
    this->datas = new T[capacity];

};
template <class T>

DSVector<T>::DSVector(const DSVector<T>& original){
        this->capacity = original.capacity;
        this->size = original.size;
        this->datas = new T[capacity];

        for(int i = 0; i < original.size; i++){
            this->datas[i] = original.datas[i];
        }
}


template <class T>
void DSVector<T>::resize(){
    T* temp = new T[2*capacity];
    for(int i = 0; i < size; i++){
        temp[i] = datas[i];
    }
    capacity *= 2;
    delete[] datas;
    datas = temp;

}

template <class T>
DSVector<T>::~DSVector(){
    delete[] datas;
}


template <class T>
bool DSVector<T>::empty(){
    if(size == 0){
        return true;
    }
    return false;
}
template <class T>
bool DSVector<T>::isExist(const T& data){
    for(int i = 0; i < getSize();i++){
        if(datas[i] == data){
            return true;
        }
    }
    return false;
}


template <class T>
T& DSVector<T>::operator[] (const int index){
        if(index >= capacity){
            throw std::out_of_range("bad index value");
        }
        return datas[index];
}


template <class T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T>& oldVector) {

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
T& DSVector<T>::at(const int index){
    return datas[index];
}

template <class T>
void DSVector<T>::push_back(const T& value){
        if(size == capacity){
            resize();
        }

        datas[size++] = value;

}

template <class T>
int DSVector<T>::getSize(){
    return size;
}
template <class T>

int DSVector<T>::getCapacity(){
    return capacity;
}
template <class T>

T& DSVector<T>::front(){
    return datas[0];
}
template <class T>

T& DSVector<T>::back(){
    return datas[size-1];
}
template <class T>
T* DSVector<T>::cbegin(){
    return &datas[0];
}

template <class T>

T* DSVector<T>::cend(){
    return &datas[size-1];
}

template <class T>

void DSVector<T>::clear(){
    size = 0 ;
}
template <class T>

T DSVector<T>::pop_back(){
    if(size == 0){
        throw std::out_of_range("Nothing to pop");
    }


    T val = datas[size-1];

//    T* temp = new T[capacity];
//
//
//    for(int i = 0; i < size-1; i++){
//        temp[i] = datas[i];
//    }
//
//    delete[] datas;
//
//    datas = temp;
    T empty;
    datas[size-1] = empty;
    size--;
    return val;
}

template <class T>

void DSVector<T>::swap(int index1, int index2){

    T temp = datas[index1];
    datas[index1] = datas[index2];
    datas[index2] = temp;
}
template <class T>

void DSVector<T>::insert(T& val, const int& position){
    if(size == capacity){
        resize();
    }

    //Create a new vector
    T* temp = new T[capacity+1];
    //Make sure the location is find
    bool inserted = false;

    for(int i=0; i < size+1; i++) {
        //When the position equals to the one to be insert in
        if(i == position){
            //set the value to be insert at that location
            temp[i] = val;
            //set value of old datas to the one upper location
            temp[i+1] = datas[i];

            i += 1;
            inserted = true;
        }else if(inserted){

            temp[i] = datas[i-1];
        }else{
            temp[i] = datas[i];
        }
    }

    delete[] datas;
    datas = temp;

    size++;
}

template <class T>
void DSVector<T>::removeAt(int index){
    for(int i = size - index - 1; i < size-1;i++){
        datas[i] = datas[i+1];
    }
    size--;
}





#endif //INC_20F_AUTO_IDX_DSVECTOR_H
