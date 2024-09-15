// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * a modified a* version which operates on subgraphs and rechecks edges on runtime
 * the edges are build and checked on runtime because we want to operate on subgraphs
 * efficently. Also it adds supports for dynamic actors like vehicles blocking paths temporarily
 */
class P2_API PathFinder
{
public:
	static const bool debugDrawNodes = false; //false

	~PathFinder();

	static PathFinder *instance(UWorld *worldIn);
	//static void deleteInstance();

	void clear(); //clears ALL NODES

	void addNewNodeVector(std::vector<FVector> &vec, FVector &offset);
	void addNewNodeVector(std::vector<FVector> &vec);
	void addNewNode(FVector a);


	std::vector<FVector> getPath(FVector a, FVector b);

	class Node{
		public:
			static const int noneFx = -1;
			bool closedFlag;
			PathFinder::Node *camefrom = nullptr;
			float fx;
			float gx;
			FVector pos;
			Node(FVector posIn);
			~Node();
			void reset();
			void updateCameFrom(float gxIn, float hxEnd, Node &came);
			void close();
			bool isClosed();

			float oldfx;

			PathFinder::Node *nA = nullptr;
			PathFinder::Node *nB = nullptr;

			bool hasNeighbors();
	};

	void addNode(PathFinder::Node *node);
	bool reached(PathFinder::Node *a, PathFinder::Node *b);

private:
	std::vector<FVector> prevPath;

	bool passTangentailCheck(Node *a, Node *b);

	static constexpr int CHUNKSIZE = 2000; // 1m = 100, 20m = 2000
	static constexpr int ONE_METER = 70; //distance to keep between nodes

	PathFinder(UWorld *worldIn);
	class UWorld *worldPointer;

	static class PathFinder *pathFinderInstance;
	static int countNodes;

	void screenMessage(int s);
	void screenMessage(FString s);

	class Chunk{
		public:
			std::vector<PathFinder::Node*> nodes;
			Chunk();
			~Chunk();
			void add(FVector vec);
			void add(Node *node);
			std::vector<PathFinder::Node *> &getNodes();
			PathFinder::Node *findNode(FVector pos);

			bool hasNode(FVector pos);

			void clear();
		};

	class Quadrant{
		private:
			int xSample;
			int ySample;

		public:
			std::vector<std::vector<PathFinder::Chunk*>> map;
			Quadrant(int xSampleIn, int zSampleIn);
			~Quadrant();

			Node *findNode(FVector pos);
			std::vector<PathFinder::Node *> nodesEnClosedBy(float xA, float zA, float xB, float zB);

			std::vector<PathFinder::Node *> askForArea(FVector a, FVector b);

			void add(FVector n);
			void add(Node *node);

			void clear();
	};

	class Quadrant *TopRight;
	class Quadrant *BottomRight;
	class Quadrant *TopLeft;
	class Quadrant *BottomLeft;

	Quadrant *askforQuadrant(int xIndex, int zIndex);
	Node *findNode(FVector pos);

	void showPos(FVector e);
	void showPos(FVector e, FColor c);

	void debugCountNodes();

	float distance(Node *A, Node *B);
	float distance(FVector A, FVector B);

	

	std::vector<PathFinder::Node *> getSubGraph(FVector a, FVector b);

	std::vector<FVector> findPath(
		Node *start,
		Node *end,
		std::vector<PathFinder::Node *> &subgraph
	);

	std::vector<FVector> constructPath(
		Node *end
	);

	bool canSee(PathFinder::Node *A, PathFinder::Node *B);
	bool canSee(FVector &a, FVector &b);

	bool isCloseAndTooVertical(Node *a, Node *b);
};
