// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathFinder.h"

/**
 * 
 */
class P2_API priorityList
{
public:
	priorityList();
	~priorityList();

	void add(PathFinder::Node *node);
	PathFinder::Node *popLowestFx();

	bool hasNodes();

	

private:
	
	std::vector<PathFinder::Node *> nodes;

};
