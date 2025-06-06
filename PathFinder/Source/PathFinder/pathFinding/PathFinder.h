// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class raycastTask;

/**
 * a modified a* version 
 * 
 * 2 modes:
 * 
 * 1)
 * which operates on subgraphs and rechecks edges on runtime
 * the edges are build and checked on runtime because we want to operate on subgraphs
 * efficently. Also it adds supports for dynamic actors like vehicles blocking paths temporarily
 * 
 * it also eliminates all non tangential edges during runtime because they are never part 
 * of a shortest path!
 * 
 * 2)
 * A node which will prebuild all tangential edges when adding a node
 * toggle the according boolean in this header file:
 * will automatically connect nodes, reduces runtime overhead because minimal tangential graph is already build
 * 
 */
class PATHFINDER_API PathFinder
{
public:
	static const bool debugDrawNodes = true; //false

	~PathFinder();

	FCollisionQueryParams collsionParamsLowDetailAndFast();

	static PathFinder *instance(UWorld *worldIn);
	static PathFinder *instance();
	static void deleteInstance();

	void debugShowAllNodes(UWorld *world);

	void clear(); //clears ALL NODES

	void addNewNodeVector(std::vector<FVector> &vec, FVector &offset);
	void addNewNodeVector(std::vector<FVector> &vec, std::vector<FVector> &offsets);
	void addNewNodeVector(std::vector<FVector> &vec);
	void addNewNode(FVector a);

	void addConvexHull(std::vector<FVector> &vec);

	std::vector<FVector> getPath(FVector a, FVector b);

	FVector findFurthestConnectedNodeFrom(FVector &other);

	enum class PathTraceMode
	{
		SyncTrace,
		SyncTraceByTick,
		AsyncTrace
	};

	class Node
	{
		public:
			static const int noneFx = -1;

			/// @brief will tell if the node is closed (on the closed list) or not
			bool closedFlag;
			/// @brief came from neighbor
			PathFinder::Node *camefrom = nullptr;
			float fx;
			float gx;
			FVector pos;
			Node(FVector posIn);
			Node(Node &other);
			Node &operator=(Node &other);

			~Node();
			void reset();
			void updateCameFrom(float gxIn, float hxEnd, Node &came);
			void close();
			bool isClosed();

			float oldfx;

			void setConvexNeighborA(Node *n);
			void setConvexNeighborB(Node *n);
			void addTangentialNeighbor(Node *n);

			PathFinder::Node *nA = nullptr;
			PathFinder::Node *nB = nullptr;

			bool hasNeighbors(); //convex hull neighbors
			bool hasAnyNeighbors(); //any visible neighbors 

			std::vector<Node *> visible_tangential_Neighbors;

			// new: hull index
			int hullindex = -1;
			bool sameHull(Node *other);

			void show(UWorld *world);

		private:
			FCriticalSection CriticalSection;
	};

	void addNode(PathFinder::Node *node);
	
	void debugCountNodes();

	void draw(FVector &pos);

	bool passTangentailCheck(Node *a, Node *b);

private:
	std::vector<FVector> prevPath;

	bool reached(PathFinder::Node *a, PathFinder::Node *b);
	

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
			/// @brief is a vector of pointers in case the vector is copied internally
			/// and nodes must stay active while path finding
			std::vector<PathFinder::Node*> nodes;
			Chunk();
			~Chunk();
			void add(FVector vec);
			void add(Node *node);
			std::vector<PathFinder::Node *> &getNodes();
			PathFinder::Node *findNode(FVector pos);
			PathFinder::Node *findNodeInDirection(FVector &node, FVector &dir);

			bool hasNode(FVector pos);

			void clear();

			PathFinder::Node *lateadd(FVector pos);

			void debugShowAllNodes(UWorld *world);

			// new:
			//std::vector<PathFinder::ConvexPolygon *> polygons;
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
			Node *findNodeInDirection(FVector &node, FVector &dir);
			std::vector<PathFinder::Node *> nodesEnClosedBy(float xA, float zA, float xB, float zB);

			std::vector<PathFinder::Node *> askForArea(FVector a, FVector b);

			void add(FVector n);
			void add(Node *node);

			void clear();

			void fillMapTo(int xIndex, int yIndex);

			void debugShowAllNodes(UWorld *world);

			int chunkCount();
	};

	class Quadrant *TopRight;
	class Quadrant *BottomRight;
	class Quadrant *TopLeft;
	class Quadrant *BottomLeft;

	Quadrant *askforQuadrant(int xIndex, int zIndex);
	Node *findNode(FVector pos);
	Node *findNodeInDirection(FVector &node, FVector &dir);

	void showPos(FVector e);
	void showPos(FVector e, FColor c);

	
	

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

	bool canSeeTangential(PathFinder::Node *A, PathFinder::Node *B);
	bool canSee(FVector &a, FVector &b);

	bool isCloseAndTooVertical(Node *a, Node *b);

	int traceCount;

	/// @brief will tell whether the graph is build if nodes are added at any time
	static constexpr bool PREBUILD_EDGES_ENABLED = true;

	/// @brief will tell whether the raycast for adding nodes will be async or an synchron operation
	static constexpr bool ASYNC_EDGE_PREBUILDING = true;
	static constexpr int PREBUILD_MAXDISTANCE = 5000; // 10000 / 100 = 100 meter, keep to 50.
	void connect(PathFinder::Node *node);
	void asyncCanSee(Node *a, Node *b);

	std::vector<FVector> findPath_prebuildEdges(
		Node *start,
		Node *end
	);

	bool isInBounds(FVector &a, FVector &b, PathFinder::Node *check);

	/*
	class ConvexPolygon{
		public:
			ConvexPolygon(std::vector<PathFinder::Node *> &nodes);
			~ConvexPolygon();
			std::vector<PathFinder::Node *> nodes; // must be sorted properly from conex hull
			//2D vector for nodes which can see each other in one row
			//std::vector<std::vector<PathFinder::Node *>> nodes
			std::vector<FVector> findFastPathOnHull(Node *a, Node *b);
	};


	
	

	std::vector<PathFinder::ConvexPolygon *> polygonstmp; //will store polygons here for now
	*/

	FCriticalSection fillQuadrant_CriticalSection;
	FCriticalSection delegate_CriticalSection_a; 
	FCriticalSection delegate_CriticalSection_b;
	
	std::vector<FTraceDelegate *> released;
	FTraceDelegate *requestDelegate(Node *a, Node *b);

	void clearDelegates();

public:
	void freeDelegate(FTraceDelegate *d);

	PathTraceMode traceMode = PathTraceMode::AsyncTrace;

	//::AsyncTrace;

	//NEW
	void Tick();

	void addActorToIgnoreRaycastParams(AActor *actor);
	FCollisionQueryParams getIgnoredRaycastParams();

private:
	void addNewRaytask(Node *a, Node *b);
	std::vector<raycastTask> rayTasksVec;


	//ignored actors
	FCollisionQueryParams collisionIgnoreParams;
};
