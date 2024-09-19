// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugHelper.h"

DebugHelper::DebugHelper()
{
}

DebugHelper::~DebugHelper()
{
}

/**
 * 
 *  --- SCREEN MESSAGES ---
 * 
 */

/// @brief showsa screen message and a color
/// @param s 
/// @param color 
void DebugHelper::showScreenMessage(FString s, FColor color){

	bool check = false;
	if(check){
		FString filterString = "filter string";
		if(s.Contains(filterString) == false ){ 
			return;
		}
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, color, s);
	}
}




/// @brief shows a scnreen message in green color
/// @param s string to show
void DebugHelper::showScreenMessage(FString s){
	showScreenMessage(s, FColor::Green);
}



void DebugHelper::showScreenMessage(FString s, int argument, FColor color){
	FString res = s;
	res.Append(FString::Printf(TEXT("%d"), argument));
	showScreenMessage(res, color);
}


/// @brief shows a screen message and a number of choice
/// @param s string
/// @param argument number to concatenate 
void DebugHelper::showScreenMessage(FString s, int argument){
	showScreenMessage(s, argument, FColor::Green);
}



void DebugHelper::showScreenMessage(FString s, FVector2D a, FVector2D b, FColor color){
	FString sOut = s;
	FString xPart = connect(a.X, b.X);
	FString yPart = connect(a.Y, b.Y);

	sOut = sOut + TEXT("\n") +
				   xPart + TEXT("\n") +
				   yPart + TEXT("\n");

	showScreenMessage(sOut, color);
}

void DebugHelper::showScreenMessage(FString s, FVector a, FVector b, FColor color){

	FString sOut = s;
	FString xPart = connect(a.X, b.X);
	FString yPart = connect(a.Y, b.Y);
	FString zPart = connect(a.Z, b.Z);

	sOut = sOut + TEXT("\n") +
				   xPart + TEXT("\n") +
				   yPart + TEXT("\n") +
				   zPart + TEXT("\n");

	showScreenMessage(sOut, color);
}

FString DebugHelper::connect(int a, int b){
	FString out = FString::Printf(TEXT("%d"), a);
	out += TEXT(" ");
	out += FString::Printf(TEXT("%d"), b);
	return out;
}



/**
 * 
 *  --- DRAW LINES ---
 *
 */



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




void DebugHelper::showLineBetween(UWorld *world, FVector2D Start, FVector2D End){
	showLineBetween(world, Start, End, 100);
}

void DebugHelper::showLineBetween(UWorld *world, FVector2D Start, FVector2D End, int zOffset){
	showLineBetween(world, Start, End, zOffset, FColor::Blue);
}

void DebugHelper::showLineBetween(UWorld *world, FVector2D Start, FVector2D End, int zOffset, FColor color){
	FVector sA(
		Start.X,
		Start.Y,
		zOffset);
	FVector eB(
		End.X,
		End.Y,
		zOffset);
	showLineBetween(world, sA, eB, color);
}