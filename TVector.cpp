

#include "TVector.h"


template <typename T>
TVector<T>::TVector(){
    sizeIndex = 0;
}

template <typename T>
TVector<T>::TVector(int size){
    sizeIndex = 0;
    vec.reserve(size);
}


template <typename T>
TVector<T>::~TVector(){
    //vec.clear();
}

template <typename T>
TVector<T>::TVector(TVector<T> &other){
    *this = other; //assign to other, overload the "=" operator
}

template <typename T>
TVector<T>& TVector<T>::operator=(TVector<T> &other){
    //dont do self assigment
    if(this == &other){ //compare both ADRESSES
        return *this;
    }

    this->sizeIndex = other.sizeIndex;
    this->vec.reserve(sizeIndex);

    //only copy to the wanted index
    for (int i = 0; i < other.size(); i++){
        this->vec.push_back(other[i]); //manuell jedes element kopieren, aber nur bis zur fake grösse
    }

    return *this;
}

template <typename T>
T & TVector<T>::operator[](int index){
    if(index >= 0 && index < size() && index < vec.size()){
        return vec.at(index);
    }
    throw std::out_of_range("Index out of range");
}



template <typename T>
int TVector<T>::size(){
    return sizeIndex;
}

template <typename T>
bool TVector<T>::empty(){
    return sizeIndex <= 0;
}

template <typename T>
void TVector<T>::clear(){
    sizeIndex = 0;
}

template <typename T>
void TVector<T>::erase(int index){
    if(index >= 0 && index < sizeIndex && vec.size() > 0 && sizeIndex > 0){
        vec.erase(vec.begin() + index);
        sizeIndex--;
        if (sizeIndex < 0)
        {
            sizeIndex = 0;
        }
        return;
    }
    throw std::out_of_range("Index out of range");
}


/// @brief pushes one element in the vector
/// @tparam T type of the vector
/// @param t item to push
template <typename T>
void TVector<T>::push_back(const T &t){ //its passing a reference to what ever t is, even a pointer or a value, no matter
    if(sizeIndex >= 0 && sizeIndex < vec.size()){
        vec[sizeIndex] = t;
        sizeIndex++;
    }else{
        vec.push_back(t);
        sizeIndex = vec.size();
    }
}

/// @brief push back another TVectors data into this vector
/// @tparam T 
/// @param t 
template <typename T>
void TVector<T>::push_back(const TVector<T> &t){
    for (int i = 0; i < t.size(); i++){
        push_back(t.at(i));
    }
}

/// @brief pushes an element to the front of the vector
/// @tparam T 
/// @param t 
template <typename T>
void TVector<T>::push_front(const T &t){
    insert(0, t);
}

/// @brief returns the first element of the vector
/// @tparam T type
/// @return element at first position if any available
template <typename T>
T& TVector<T>::front(){
    if(vec.size() > 0){
        return vec.front();
    }
    throw std::out_of_range("Index out of range");
}

/// @brief returns the last element of the vector
/// @tparam T type
/// @return returns the last element
template <typename T>
T& TVector<T>::back(){
    if(vec.size() > 0){
        if(sizeIndex == vec.size()){
            return vec.back();
        }else{
            return vec.at(sizeIndex - 1);
        }
    }
    throw std::out_of_range("Index out of range");
}

/// @brief pops the very last element
/// @tparam T type
template <typename T>
void TVector<T>::pop_back(){
    if(sizeIndex == vec.size() && vec.size() > 0){
        vec.pop_back();
        sizeIndex = vec.size();
    }else{
        sizeIndex--; //one back
        if(sizeIndex < 0){
            sizeIndex = 0;
        }
    }
    throw std::out_of_range("Index out of range");
}

/// @brief returns the element at an index if valid
/// @tparam T type
/// @param index index to get, must be in bounds 
/// @return element at index by reference
template <typename T>
T &TVector<T>::at(int index){
    if(index >= 0 && index < sizeIndex && index < vec.size()){
        return vec.at(index);
    }
    throw std::out_of_range("Index out of range");
}

/// @brief inserts an element infront of the index
/// any out of bounce will be handled automatically by push_back or insert infront
/// @param index 
/// @param element 
template <typename T>
void TVector<T>::insert(int index, const T &element){
    //no out of bounce
    if(index >= vec.size() || index >= sizeIndex){
        index = sizeIndex;
    }
    if(index < 0){
        index = 0;
    }

    //real end, need to push back
    if(sizeIndex >= vec.size()){
        push_back(element);
        sizeIndex = vec.size();
        return;
    }

    //inbetween 0 and fake size (means just inserting and increasing count)
    if(index < sizeIndex){
        vec.insert(vec.begin() + index, element);
        sizeIndex++; //increment obviously
        return;
    }

    //fake size to end (means in the puffer zone of size index to end insertion, right at the edge overriden)
    if(index >= sizeIndex && index < vec.size() && sizeIndex < vec.size()){
        index = sizeIndex;
        vec.at(index) = element; //override end, increase fake counter
        sizeIndex++;
        return;
    }




    //end

}


/// @brief inserts all elements of other vector infront of the index
/// @tparam T type param
/// @param index index to insert infront
/// @param other other vector 
template <typename T>
void TVector<T>::insert(int index, TVector<T> &other){
    if(index < sizeIndex){
        for (int i = 0; i < other.size(); i++){
            insert(index + i, other.at(i));
        }
    }else{
        //just "append" them all
        for (int i = 0; i < other.size(); i++){
            insert(sizeIndex, other.at(i));
        }
    }
}


/// @brief checks if a given element is contained in the vector
/// @tparam T type
/// @param element element to search 
/// @return true if found
template <typename T>
bool TVector<T>::contains(T &element){
    if(size() > 0){
        for (int i = 0; i < size(); i++){
            if(this->at(i) == element){
                return true;
            }
        }
    }
    return false;
}