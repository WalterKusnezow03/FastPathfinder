// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

#include "CoreMinimal.h"

/**
 * 
 */
class P2_API EdgeCollector
{
public:
	EdgeCollector();
	~EdgeCollector();
private:
	class edgeData
    {
		public:
			edgeData(FVector bottomIn, FVector topIn);
			~edgeData();

			FVector top;
			FVector bottom;

			
	};
public:
	std::vector<FVector>& getAllEdges(UWorld *World, float minHeight);
	std::vector<FVector> &getReadEdges();

	void getEdgesForActor(AActor *actor, std::vector<FVector> &vector);

private:
	float edgeMinHeight;

	std::vector<FVector> *readEdges;

	
	void getEdgesFromSingleMesh(
		UStaticMesh *StaticMesh, 
		FVector debugPos, 
		FTransform LocalToWorldTransform, 
		std::vector<edgeData> &vector
	);
	void getEdgesFromSingleMeshComponent(UStaticMeshComponent *MeshComponent, std::vector<edgeData> &vector);

	bool isVertical(FVector A, FVector B);

	class UWorld *worldIn;

	// Innere Klasse
    
	void showPos(UWorld *world, FVector e);
	void showLine(FVector e, FVector g);
	void showEdges(std::vector<edgeData> &edges, UWorld *world);
	void ComputeConvexHull(std::vector<edgeData> &points);
	bool IsClockwise(const edgeData &a, const edgeData &b, const edgeData &c);

	void collectRaycasts(std::vector<edgeData> &edges, UWorld *world);
	void collectRaycast(edgeData &edge, UWorld *world);

	std::vector<edgeData> *edgeDataEdges;


	bool isExcludedType(AActor *actor);

	template <typename T>
	void findAllOfType(AActor &a, std::list<T *> &items);

	//testing needed - not known if nesecarry
	void clean(std::vector<edgeData> &vector);
	bool checkExtension(edgeData &p, edgeData &update);
};
