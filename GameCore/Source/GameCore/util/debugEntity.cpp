// Fill out your copyright notice in the Description page of Project Settings.


#include "debugEntity.h"

// Sets default values
AdebugEntity::AdebugEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AdebugEntity::BeginPlay()
{
	Super::BeginPlay();
	clicked = false;
	takedamage(0);
}

// Called every frame
void AdebugEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	debugFunction(DeltaTime);
}

void AdebugEntity::takedamage(int d){
	if(!clicked){
		clicked = true;
		//debugFunction();
	}
}
void AdebugEntity::takedamage(int d, FVector &from){
	takedamage(d);
}


void AdebugEntity::takedamage(int d, bool surpressed){
	takedamage(d);
}
void AdebugEntity::takedamage(int d, FVector &hitpoint, bool surpressed){
	takedamage(d);
}

/// @brief sets the team, is empyt here, will not be set
/// @param team 
void AdebugEntity::setTeam(teamEnum team){
}

/// @brief will always return neutralTeam
/// @return 
teamEnum AdebugEntity::getTeam(){
	return teamEnum::neutralTeam;
}




void AdebugEntity::debugFunction(){
	
}


void AdebugEntity::debugFunction(float deltaTime){

}



