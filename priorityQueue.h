// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "p2/pathFinding/PathFinder.h"

/**
 * 
 */
class P2_API priorityQueue
{
public:
	priorityQueue();
	~priorityQueue();

	void add(PathFinder::Node *node);
	PathFinder::Node *popLowestFx();

	bool hasNodes();

	void show();

private:
	std::vector<PathFinder::Node *> nodes;
	void downheap();
	void bubbleUpfrom(int index);

	/// @brief saves the index in the vector for a node
	/// to bubble up nodes if they are refreshed 
	std::map<PathFinder::Node *, int> indexMap;
};
