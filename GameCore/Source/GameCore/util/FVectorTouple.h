// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GAMECORE_API FVectorTouple
{
public:
	FVectorTouple(FVector aIn, FVector bIn);
	~FVectorTouple();

	FVector &first();
	FVector &second();

private:
	FVector a;
	FVector b;
	

};
