#pragma once

#include "CoreMinimal.h"


/**
 * simple vector class, not iterable
 */
template <typename T>
class GAMECORE_API TVector{

public:
    TVector(){
        sizeIndex = 0;
    }
    TVector(int size){
        sizeIndex = 0;
        vec.reserve(size);
    }

    ~TVector(){

    }

    TVector(TVector<T> &other){
        *this = other; //assign to other, overload the "=" operator
    }

    int size() const{
        return sizeIndex;
    }

    bool empty(){
        return sizeIndex <= 0;
    }

    bool contains(T &element){
        if(size() > 0){
            for (int i = 0; i < size(); i++){
                if(this->at(i) == element){
                    return true;
                }
            }
        }
        return false;
    }

    void clear(){
        sizeIndex = 0;
    }

    T &at(int index) {
        if(index >= 0 && index < sizeIndex && index < vec.size()){
            return vec.at(index);
        }
        throw std::out_of_range("Index out of range");
    }

    //void push_back(T t);
    void push_back(const T &t){ //its passing a reference to what ever t is, even a pointer or a value, no matter
        if(sizeIndex >= 0 && sizeIndex < vec.size()){
            vec[sizeIndex] = t;
            sizeIndex++;
        }else{
            vec.push_back(t);
            sizeIndex = vec.size();
        }
    }


    void push_back(TVector<T> &t){
        for (int i = 0; i < t.size(); i++){
            push_back(t.at(i));
        }
    }


    void push_front(const T &t){
        insert(0, t);
    }

    void insert(int index, TVector<T> &other){
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




    void insert(int index, const T &element){
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

    void erase(int index){
        if(index >= 0 && index < sizeIndex && vec.size() > 0 && sizeIndex > 0){
                
            vec.erase(vec.begin() + index);
            sizeIndex--;
            if (sizeIndex < 0)
            {
                sizeIndex = 0;
            }
            return;
        }
        //throw std::out_of_range("Index out of range");
    }

    T& front(){
        if(vec.size() > 0){
            return vec.front();
        }
        throw std::out_of_range("Index out of range");
    }

    T& back(){
        if(vec.size() > 0){
            if(sizeIndex == vec.size()){
                return vec.back();
            }else{
                return vec.at(sizeIndex - 1);
            }
        }
        throw std::out_of_range("Index out of range");
    }

    
    
    void pop_back(){
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


    T &operator[](int index){
        if(index >= 0 && index < size() && index < vec.size()){
            return vec.at(index);
        }
        throw std::out_of_range("Index out of range");
    }

    TVector<T> &operator=(TVector<T> &other){
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

    std::vector<T> copy(){
        std::vector<T> output;
        for (int i = 0; i < size(); i++){
            output.push_back(vec[i]);
        }
        return output;
    }

private:
    std::vector<T> vec;

    int sizeIndex;





};