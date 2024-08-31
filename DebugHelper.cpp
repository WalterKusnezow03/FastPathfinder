// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugHelper.h"

DebugHelper::DebugHelper()
{
}

DebugHelper::~DebugHelper()
{
}

/// @brief shows a scnreen message in green color
/// @param s string to show
void DebugHelper::showScreenMessage(FString s){
    if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, s);
	}
}

/// @brief showsa screen message and a color
/// @param s 
/// @param color 
void DebugHelper::showScreenMessage(FString s, FColor color){
    if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, color, s);
	}
}

/// @brief shows a screen message and a number of choice
/// @param s string
/// @param argument number to concatenate 
void DebugHelper::showScreenMessage(FString s, int argument){
	showScreenMessage(s, argument, FColor::Green);
}

void DebugHelper::showScreenMessage(FString s, int argument, FColor color){
	FString res = s;
	res.Append(FString::Printf(TEXT("%d"), argument));
	showScreenMessage(res, color);
}







void DebugHelper::showLineBetween(UWorld *world, FVector Start, FVector End, FColor color){
	if(world != nullptr){
		DrawDebugLine(world, Start, End, color, false, 100.0f, 0, 1.0f);
	}
}

/// @brief draws a line between 2 given points
/// @param world world to draw in
/// @param Start start point
/// @param End end point
void DebugHelper::showLineBetween(UWorld *world, FVector Start, FVector End){
	showLineBetween(world, Start, End, FColor::Blue);
}




void DebugHelper::showLine(UWorld *world, std::vector<FVector> &vec){
	showLine(world, vec, FColor::Green);
}

/// @brief draw line for a complete set of points
/// @param world world to draw in
/// @param vec all points to connect in order
void DebugHelper::showLine(UWorld *world, std::vector<FVector> &vec, FColor color){
	if(world != nullptr){
		for(int i = 1; i < vec.size(); i++){
			showLineBetween(world, vec.at(i - 1), vec.at(i), color);
		}
	}
}




void DebugHelper::showLine(UWorld *world, TArray<FVector> &array){
	showLine(world, array, FColor::Green);
}


void DebugHelper::showLine(UWorld *world, TArray<FVector> &array, FColor color){
	if(world != nullptr){
		for(int i = 1; i < array.Num(); i++){
			showLineBetween(world, array[i-1], array[i], color);
		}
	}
}