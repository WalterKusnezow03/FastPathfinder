#pragma once

#include "CoreMinimal.h"


/**
 * simple vector class, not iterable
 */
template <typename T>
class P2_API TVector{

public:
    TVector();
    TVector(int size);
    ~TVector();
    TVector(TVector<T> &other);

    int size();
    bool empty();
    bool contains(T &element);
    void clear();
    //void push_back(T t);
    void push_back(const T &t);
    void push_back(const TVector<T> &t);

    void push_front(const T &t);

    void insert(int index, TVector<T> &other);
    void insert(int index, const T &element);

    void erase(int index);
    T& front();
    T& back();
    T &at(int index);
    void pop_back();

    T &operator[](int index);
    TVector<T> &operator=(TVector<T> &ref);

private:
    std::vector<T> vec;

    int sizeIndex;
};