// Fill out your copyright notice in the Description page of Project Settings.


#include "FVectorTouple.h"

/// @brief parameters will be saved, you can access them via the first() and second() method
/// @param aIn first vector to save
/// @param bIn second vector to save
FVectorTouple::FVectorTouple(FVector aIn, FVector bIn)
{
    a = aIn;
    b = bIn;
}

FVectorTouple::~FVectorTouple()
{
}

/// @brief get the first vector from the touple
/// @return first vector from constructor args
FVector &FVectorTouple::first(){
    return a;
}

/// @brief get the second vector from the touple
/// @return second vector from constructor args
FVector &FVectorTouple::second(){
    return b;
}
