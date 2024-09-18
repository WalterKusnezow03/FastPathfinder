// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

#include "CoreMinimal.h"

/**
 * collects all edges from meshes convex
 */
class P2_API EdgeCollector
{
public:
	EdgeCollector();
	~EdgeCollector();
private:
	static const int GROUND_OFFSET = 70;

	class edgeData
    {
		public:
			edgeData(FVector bottomIn, FVector topIn);
			~edgeData();

			FVector top;
			FVector bottom;
	};

public:
	//std::vector<FVector>& getAllEdges(UWorld *World);
	void getAllEdges(UWorld *World);

	void getEdgesForActor(AActor *actor);

	void ComputeConvexHull(std::vector<edgeData> &points);

private:
	float edgeMinHeight;

	//std::vector<FVector> *readEdges;
	//std::vector<edgeData> *edgeDataEdges;
	std::vector<FVector> readEdges;
	std::vector<edgeData> edgeDataEdges;


	void getEdgesFromSingleMesh(
		UStaticMesh *StaticMesh, 
		FVector debugPos, 
		FTransform LocalToWorldTransform
		//, std::vector<edgeData> &vector
	);
	void getEdgesFromSingleMeshComponent(
		UStaticMeshComponent *MeshComponent
		//,std::vector<edgeData> &vector
	);

	bool isVertical(FVector A, FVector B);

	class UWorld *worldIn;

	// Innere Klasse
    
	void showPos(UWorld *world, FVector e);
	void showLine(FVector e, FVector g);
	void showEdges(std::vector<edgeData> &edges, UWorld *world);
	
	bool IsClockwise(const edgeData &a, const edgeData &b, const edgeData &c);

	void collectRaycasts(std::vector<edgeData> &edges, UWorld *world);
	void collectRaycast(edgeData &edge, UWorld *world);

	


	bool isExcludedType(AActor *actor);

	template <typename T>
	void findAllOfType(AActor &a, std::list<T *> &items);

	//testing needed - not known if nesecarry
	void clean(std::vector<edgeData> &vector);
	bool checkZExtension(edgeData &p, edgeData &update);



	//clean up in xy pane, not nesecarry, unclear if will be kept
	void CleanUpParalellEdges(std::vector<edgeData> &vector);
	bool xyExtension(FVector &a, FVector &b, FVector &c);
	float xyDotProduct(FVector &A, FVector &B);
};
