#pragma once

#include "CoreMinimal.h"

template <typename T, typename U>
class GAMECORE_API TTouple{

public:
    TTouple(T t, U u){
        this->_first = t;
        this->_last = u;
    }
    ~TTouple(){

    }

    T& first(){
        return _first;
    }
    
    U& last(){
        return _last;
    }

private:
    T _first;
    U _last;
};