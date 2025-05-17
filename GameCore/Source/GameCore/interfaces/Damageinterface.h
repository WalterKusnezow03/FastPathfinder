// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameCore/team/teamEnum.h"
#include "Damageinterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageinterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * interface for taking damage and team management
 */
class IDamageinterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//methods
	virtual void takedamage(int d) = 0; //= 0 schreiben damit sie pure virtual sind
	virtual void takedamage(int d, FVector &hitpoint) = 0;

	virtual void takedamage(int d, bool surpressed) = 0;
	virtual void takedamage(int d, FVector &hitpoint, bool surpressed) = 0;

	//virtual void setTeam(int teamIn) = 0;
	//virtual int getTeam() = 0;
	virtual void setTeam(teamEnum t) = 0;
	virtual teamEnum getTeam() = 0;
};
