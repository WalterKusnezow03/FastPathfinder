// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class P2_API DebugHelper
{
public:
	DebugHelper();
	~DebugHelper();

	//Messages
	static void showScreenMessage(FString s);
	static void showScreenMessage(FString s, FColor color);
	static void showScreenMessage(FString s, int argument);
	static void showScreenMessage(FString s, int argument, FColor color);
	static void showScreenMessage(FString s, FVector a, FVector b, FColor color);
	static void showScreenMessage(FString s, FVector2D a, FVector2D b, FColor color);

	//FVector
	static void showLineBetween(UWorld *world, FVector Start, FVector End);
	static void showLineBetween(UWorld *world, FVector Start, FVector End, FColor color);
	static void showLine(UWorld *world, std::vector<FVector> &vec);
	static void showLine(UWorld *world, std::vector<FVector> &vec, FColor color);
	static void showLine(UWorld *world, TArray<FVector> &vec);
	static void showLine(UWorld *world, TArray<FVector> &vec, FColor color);
	
	//Fvector 2D
	static void showLineBetween(UWorld *world, FVector2D Start, FVector2D End);
	static void showLineBetween(UWorld *world, FVector2D Start, FVector2D End, int zOffset);
	static void showLineBetween(UWorld *world, FVector2D Start, FVector2D End, int zOffset, FColor color);

private:
	static FString connect(int a, int b);

};
