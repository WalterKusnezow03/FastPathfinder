// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFinder.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "p2/interfaces/Damageinterface.h"
#include "DrawDebugHelpers.h"
#include <cmath>
#include <algorithm>
#include "CoreMinimal.h"
#include <limits>
#include "priorityList.h"
#include "p2/pathFinding/priorityQueue.h"






PathFinder::PathFinder(UWorld *worldIn)
{
    worldPointer = worldIn;
    TopRight = new PathFinder::Quadrant(1,1);
	BottomRight = new PathFinder::Quadrant(1,-1);
	TopLeft = new PathFinder::Quadrant(-1,1);
	BottomLeft = new PathFinder::Quadrant(-1,-1);

}

PathFinder::~PathFinder()
{
    worldPointer = nullptr;
    pathFinderInstance = nullptr;
    delete (TopRight); 
    delete (BottomRight); 
    delete (BottomLeft); 
    delete (TopLeft); 
}

PathFinder* PathFinder::pathFinderInstance = nullptr;
int PathFinder::countNodes = 0;

PathFinder::Node::Node(FVector posIn){
    gx = 0;
    fx = 0;
    pos = posIn;
    camefrom = nullptr;
    closedFlag = true;
}

PathFinder::Node::~Node(){
}

PathFinder::Quadrant::Quadrant(int xSampleIn, int ySampleIn){
    xSample = xSampleIn;
    ySample = ySampleIn;
}

PathFinder::Quadrant::~Quadrant(){
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map.at(i).size(); j++){
            PathFinder::Chunk *c = map.at(i).at(j);
            if(c != nullptr){
                delete (c);
                map.at(i).at(j) = nullptr;
            }
        }
    }
}
PathFinder::Chunk::Chunk(){}
PathFinder::Chunk::~Chunk(){
    for (int i = 0; i < nodes.size(); i++){
        if(nodes.at(i) != nullptr){
            delete (nodes.at(i));
            nodes.at(i) = nullptr;
        }
    }
}



//constructors end









//PATH FINDER METHODS




// IMMER DT class::method();

/// @brief returns the instance of the poath finder. DO NOT DELETE
/// CAUTION if worldIn is a nullptr, you will get a nullptr! No World context is not allowed!
/// @param worldIn pass the world context in the edges should be collected from 
/// @return instance if PathFinder
PathFinder* PathFinder::instance(UWorld *worldIn){
    if(worldIn == nullptr){
        return nullptr;
    }

    if(pathFinderInstance == nullptr){
        pathFinderInstance = new PathFinder(worldIn);
    }
    return pathFinderInstance;
}




//debug drawing
void PathFinder::showPos(FVector e){
    showPos(e, FColor::Green);
}

void PathFinder::showPos(FVector e, FColor c){
    if(worldPointer && debugDrawNodes){
        FVector End = e + FVector(0, 0, 10000);
        DebugHelper::showLineBetween(worldPointer, e, End, c);
    }
}



/// @brief add nodes to the graph
/// @param vec 
void PathFinder::addNewNodeVector(std::vector<FVector>& vec){
    for (int i = 0; i < vec.size(); i++){
        addNewNode(vec.at(i));
    }

    //debugCountNodes();
}

/// @brief adds a single node to the graph
/// @param a 
void PathFinder::addNewNode(FVector a){
    PathFinder::Quadrant *q = askforQuadrant(a.X, a.Y);
    if(q != nullptr){
        q->add(a);
        
        
        //debug testing for checking if nodes were added, works properly
        /*
        PathFinder::Node *tryFind = findNode(a);
        if(tryFind != nullptr){
            showPos(tryFind->pos, FColor::Purple);
        }
        */
    }
}

PathFinder::Quadrant* PathFinder::askforQuadrant(int xIndex, int yIndex){
    //top left
    if(xIndex < 0 && yIndex >= 0){
        return this->TopLeft;
    }
    //top right
    if(xIndex >= 0 && yIndex >= 0){
        return this->TopRight; 
    }
    //bottom left
    if(xIndex < 0 && yIndex < 0){
        return this->BottomLeft;
    }
    //bottom right
    if(xIndex >= 0 && yIndex < 0){
        return this->BottomRight;
    }
    return nullptr;
}



/// @brief finds a node from the correct quadrant
/// @param node 
/// @return 
PathFinder::Node* PathFinder::findNode(FVector node){
    int x = node.X;
    int y = node.Y;
    PathFinder::Quadrant *q = askforQuadrant(x, y);
    if(q != nullptr){
        PathFinder::Node *nodeFound = q->findNode(node);
        if(nodeFound != nullptr){
            return nodeFound;
        }
    }
    return nullptr;
}


std::vector<PathFinder::Node *> PathFinder::getSubGraph(FVector a, FVector b){

    std::vector<PathFinder::Node *> nodes;
    std::vector<PathFinder::Node *> asked;

    //why is this just iterating over all quadrants:
    //the "askForArea(a,b)" method is clamping the coordinates by it self
    //to the correct values to properly get all nodes in the correct area.
    TArray<PathFinder::Quadrant*> array = {TopLeft, BottomLeft, TopRight, BottomRight};
    
    
    
    for (int i = 0; i < array.Num(); i++){
        if(array[i] != nullptr){

            asked = array[i]->askForArea(a, b);

            nodes.insert(nodes.end(), asked.begin(), asked.end());
        }
    }
    return nodes;
}


void PathFinder::debugCountNodes(){

    FVector a = FVector(-99999999999, 0, -99999999999);
    FVector b = FVector(99999999999, 0, 99999999999);

    std::vector<PathFinder::Node *> nodes = getSubGraph(a, b);

    FString string = FString::Printf(TEXT("collected COUNT %d"), PathFinder::countNodes);
    FString string2 = FString::Printf(TEXT("collected SUBGRAPH %d"), nodes.size());

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, string);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, string2);
    }
}





/// @brief returns a path from a given position a to an given position b
/// @param a fvector start point targeted
/// @param b fvector end point targeted
/// @return a path or an emtpy vector if no path was found
std::vector<FVector> PathFinder::getPath(FVector a, FVector b){

    PathFinder::Node *start = findNode(a);
    PathFinder::Node *end = findNode(b);

    if(start != nullptr && end != nullptr){

        //showPos(start->pos, FColor::Red);
        //showPos(end->pos, FColor::Red);

        std::vector<PathFinder::Node *> graph = getSubGraph(a, b);
        showPos(start->pos, FColor::Blue);
        showPos(end->pos, FColor::Red);
        DebugHelper::showLineBetween(worldPointer, start->pos, end->pos, FColor::Yellow);

        return findPath(start, end, graph);
    }



    return std::vector<FVector>();
}


/// @brief calculates the distance between 2 nodes and their positions
/// @param A 
/// @param B 
/// @return 
float PathFinder::distance(PathFinder::Node* A, PathFinder::Node *B){
    if(A != nullptr && B != nullptr){
        float d = FVector::Dist(A->pos, B->pos);
        return d;
    }
    return std::numeric_limits<float>::max();
}

float PathFinder::distance(FVector A, FVector B){
    return FVector::Dist(A, B);
}




/// @brief finds the path between 2 given nodes in the subgraph
/// @param start node from the graph
/// @param end node from the graph
/// @param subgraph graph enclosed by start and end node. Use Subgraph method
/// @return vector of positions: path
std::vector<FVector> PathFinder::findPath(
    Node *start, 
    Node *end, 
    std::vector<PathFinder::Node*> &subgraph
){
    screenMessage(FString::Printf(TEXT("subgraph size %d"), subgraph.size()));
    

    for (int i = 0; i < subgraph.size(); i++){
        PathFinder::Node *n = subgraph.at(i);
        if(n != nullptr){
            n->reset();
            n->closedFlag = false;
        }
    }

    start->camefrom = nullptr;
    start->closedFlag = false;
    start->gx = 0;
    start->fx = 0;

    end->camefrom = nullptr;
    end->closedFlag = false;

    std::vector<PathFinder::Node*> openList;

    //priorityList openList_;
    priorityQueue openList_;
    openList_.add(start);

    while(openList_.hasNodes()){
    //while(openList_.size() > 0){

        //PathFinder::Node* current = openList.at(0); //implement priority queue!
        //openList.erase(openList.begin() + 0);
        PathFinder::Node *current = openList_.popLowestFx();

        if (current != nullptr)
        {
            if(current == end){ //|| canSee(current, end)){
                //path found
                screenMessage("found path");
                return constructPath(end);
            }

            //show opened nodes: debugging
            if(debugDrawNodes){
                //showPos(current->pos, FColor::Blue);
            }
            //

            current->close();
            for (int i = 0; i < subgraph.size(); i++)
            {
                PathFinder::Node *n = subgraph.at(i);
                if(n != nullptr){
                    //bool wasClosed = n->closedFlag;
                    if(!n->isClosed()){
                        
                        //create edge at runtime: 
                        //all edges are rechecked during runtime 
                        //because otherwise it could not operate on subgraphs
                        //but is nesecarry to eliminate many nodes at once
                        if(canSee(current, n)){
                            

                            float gxNew = distance(current->pos, n->pos);
                            if(gxNew < n->gx){
                                //screenMessage(300);
                                float hxEnd = distance(n->pos, end->pos);
                                n->updateCameFrom(gxNew, hxEnd, *current);

                                
                            }
                            //ADD TO OPEN LIST!!
                            openList_.add(n); 
                        }

                        
                    }
                }
            }
        }
    }

    /*
    if (GEngine)
    {
        FString string = FString::Printf(TEXT("out of nodes"));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, string);
    }*/

    return std::vector<FVector>();
}



void PathFinder::screenMessage(int s){
    if (GEngine)
    {
        FString string = FString::Printf(TEXT("text %d"), s);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, string);
    }
}

void PathFinder::screenMessage(FString s) {
    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s);
    }
}



/// @brief checks if 2 nodes can see each other, damagable interfaces are excluded for now.
/// @param A position A
/// @param B position B
/// @return can see without interrupt
bool PathFinder::canSee(PathFinder::Node *A, PathFinder::Node*B){
    if(worldPointer && A && B){
        FVector Start = A->pos;
        FVector End = B->pos;
        //testing with more raycasts to ensure realibilty
        if (canSee(Start, End)){
            return true;
        }

        //adjustments if any entity might be in way
        Start.Z += ONE_METER * 1.5f;
        if (canSee(Start, End)){
            return true;
        }

        End.Z += ONE_METER * 1.5f;
        if (canSee(Start, End)){
            return true;
        }


        /*
        FVector Start = A->pos;
        FVector End = B->pos; // B->pos;
        */
        FVector dir = (B->pos - Start).GetSafeNormal();
        Start += dir * 20; //offset for entity raycast failure

        FHitResult HitResult;
		FCollisionQueryParams Params;
		//Params.AddIgnoredActor(this); // Ignore the character itself

		bool bHit = worldPointer->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

		// If the raycast hit something, log the hit actor's name
		if (bHit)
		{   
            //ein punkt weil hier ein value bzw ref call!, merken, wichtig!
            AActor *actor = HitResult.GetActor();
            if(actor != nullptr){
				
				

                //casting:
                //DT* name = Cast<DT>(actor);
				IDamageinterface* entity = Cast<IDamageinterface>(actor);
				if (entity){
                    float hitDistance = FVector::Dist(HitResult.ImpactPoint, End);
                    if(hitDistance <= 100){
                        return true; //ignore enteties
                    }
                }
            }
            //default hit: can see FALSE
            return false;
        }else{
            return true; //no hit: can see true
        }
    }
    return false;
}

/// @brief checks with a simple raycasts if nodes can see each other
/// @param Start 
/// @param End 
/// @return 
bool PathFinder::canSee(FVector Start, FVector End){
    if(worldPointer){
        FHitResult HitResult;
		FCollisionQueryParams Params;
		//Params.AddIgnoredActor(this); // Ignore the character itself

		bool bHit = worldPointer->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
        if(bHit){
            return false;
        }else{
            return true;
        }
    }
    return false;
}

std::vector<FVector> PathFinder::constructPath(PathFinder::Node *end){
    std::vector<FVector> list;
    if (end != nullptr)
    {
        while(end != nullptr){
            list.push_back(end->pos);
            end = end->camefrom;
        }

        std::reverse(list.begin(), list.end());
    }
    return list;
}





//QUADRANT METHODS

void PathFinder::Quadrant::add(FVector n){
    //std::abs for flipping negatives obviosuly
    int x = std::abs(n.X / CHUNKSIZE); //create new chunks?
    int y = std::abs(n.Y / CHUNKSIZE);

    while(map.size() <= x) {
        map.push_back(std::vector<PathFinder::Chunk * >());
    }

    // Ensure all lists up to map.Count have enough chunks
    for (int i = 0; i < map.size(); i++) {
        while (map[i].size() <= y) {
            map[i].push_back(new PathFinder::Chunk());
        }
    }

    // Add the node to the appropriate chunk
    map[x][y]->add(n);

            
}

//finds a node from a quadrant
PathFinder::Node* PathFinder::Quadrant::findNode(FVector pos){
    int x1 = std::abs(pos.X / CHUNKSIZE);
    int y1 = std::abs(pos.Y / CHUNKSIZE);

    if(map.size() > x1 && map.at(x1).size() > y1){
        if(map.at(x1).at(y1) != nullptr){
            return map.at(x1).at(y1)->findNode(pos);
        }
    }
    return nullptr;
}





/// @brief returns all lists from all chunks enclosed by an area
/// @param xA x value of first pos
/// @param yA z value of first pos
/// @param xB x value of second pos
/// @param zB z value of second pos
/// @return 
std::vector<PathFinder::Node*> PathFinder::Quadrant::nodesEnClosedBy(
    float xA, float yA, float xB, float yB
){
    std::vector<PathFinder::Node *> nodes;

    //abs for flipping neg values for the quadrants
    int x1 = std::abs(xA / CHUNKSIZE); //implicit conversion is allowed
    int y1 = std::abs(yA / CHUNKSIZE);
    int x2 = std::abs(xB / CHUNKSIZE); //implicit conversion is allowed
    int y2 = std::abs(yB / CHUNKSIZE);

    int fromX = std::min(x1, x2);
    int toX = std::max(x1, x2);
    //toX = std::min(tg btoX, map.size());
    

    int fromY = std::min(y1, y2);
    int toY = std::max(y1, y2);
    //toY = std::min(toY, map.at(0).size());

    for(int i = fromX; i <= toX; i++){
        for(int j = fromY; j <= toY; j++){
            if(map.size() > i && map.at(i).size() > j){ //hier mit punkt weil call by value
                std::vector<PathFinder::Node *> &read = map.at(i).at(j)->getNodes();
                if(read.size() > 0){
                    nodes.insert(nodes.end(), read.begin(), read.end());
                }

                FString string = FString::Printf(TEXT("read enclosed num size %d"), read.size());
                if(GEngine){
                    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, string);
                }
            }
        }
    }

    return nodes;
}



std::vector<PathFinder::Node*> PathFinder::Quadrant::askForArea(FVector a, FVector b){
    
    float lowerX = 0;
    float lowerY = 0;
    float higherX = 0;
    float higherY = 0;
    lowerX = std::min(a.X, b.X) - CHUNKSIZE; //+ extension
    lowerY = std::min(a.Y, b.Y) - CHUNKSIZE;
    higherX = std::max(a.X, b.X) + CHUNKSIZE;
    higherY = std::max(a.Y, b.Y) + CHUNKSIZE;

    float inf = std::numeric_limits<float>::infinity();

    if(xSample == 1 && ySample == 1){
        // Bottom-left quadrant
        lowerX = std::clamp(lowerX, 0.0f, inf); //(val, lowerclamp, higherclamp)
        lowerY = std::clamp(lowerY, 0.0f, inf);
        return nodesEnClosedBy(lowerX, lowerY, higherX, higherY);
    }

    if(xSample == -1 && ySample == -1){
        // Top-right quadrant
        higherX = std::clamp(higherX, -inf, 0.0f); 
        higherY = std::clamp(higherY, -inf, 0.0f);
        return nodesEnClosedBy(lowerX, lowerY, higherX, higherY);
    }

    if(xSample == -1 && ySample == 1){
        // Bottom-right quadrant
        higherX = std::clamp(higherX, -inf, 0.0f);
        lowerY = std::clamp(lowerY, 0.0f, inf);
        return nodesEnClosedBy(lowerX, lowerY, higherX, higherY);
    }

    if(xSample == 1 && ySample == -1){
        // Top-left quadrant
        lowerX = std::clamp(lowerX, 0.0f, inf);
        higherY = std::clamp(higherY, -inf, 0.0f);
        return nodesEnClosedBy(lowerX, lowerY, higherX, higherY);
    }

    std::vector<PathFinder::Node*> vec;
    // returns an empty list if none found
    return vec;
}

//CHUNK METHODS

/// @brief adds a new node to the vector with a position
/// @param vec position of the node to be added
void PathFinder::Chunk::add(FVector vec){
    //find closest node near by
    

    if(hasNode(vec) == false){
        nodes.push_back(new Node(vec));
        PathFinder::countNodes += 1;
    }
}






/// @brief returns the chunk nodes as reference
/// @return vector<Node> nodes as &ref
std::vector<PathFinder::Node*> &PathFinder::Chunk::getNodes(){
    return nodes;
}

/// @brief tries to find a node from a chunk, if not found: created
/// @param pos position of the targetet node
/// @return returns the closest node near by
PathFinder::Node* PathFinder::Chunk::findNode(FVector pos){
    if(nodes.size() <= 0){

        PathFinder::Node *s = new PathFinder::Node(pos);
        nodes.push_back(s);
        return s;
    }

    float closest = std::numeric_limits<float>::max();
    PathFinder::Node *closestNode = nodes.at(0);

    for (int i = 0; i < nodes.size(); i++)
    {
        PathFinder::Node *current = nodes.at(i);
        if (current != nullptr)
        {

            float Difference = FVector::Dist(pos, current->pos);

            if(Difference < closest){
                closest = Difference;
                closestNode = current;
            }
        }
    }
    return closestNode;
}




/// @brief tries to find a node from a chunk as BOOL
/// @param pos position of the targetet node
/// @return returns the closest node near by
bool PathFinder::Chunk::hasNode(FVector pos){
    if(nodes.size() <= 0){
        return false;
    }

    float closest = std::numeric_limits<float>::max();
    PathFinder::Node *closestNode = nodes.at(0);

    for (int i = 0; i < nodes.size(); i++)
    {
        PathFinder::Node *current = nodes.at(i);
        if (current != nullptr)
        {

            float Difference = FVector::Dist(pos, current->pos);

            if(Difference < closest){
                closest = Difference;
                closestNode = current;
            }
        }
    }
    if(closest <= (ONE_METER)){
        return true;
    }
    return false;
}




//NODE METHODS

void PathFinder::Node::reset(){
    camefrom = nullptr;
    gx = std::numeric_limits<float>::max();
    fx = gx;
    closedFlag = false;
}

void PathFinder::Node::updateCameFrom(float gxIn, float hxEnd, PathFinder::Node &came){
    this->camefrom = &came;

    oldfx = fx; //copy

    gx = gxIn;
    fx = gxIn + hxEnd;
}


void PathFinder::Node::close(){
    this->closedFlag = true;
}


bool PathFinder::Node::isClosed(){
    return closedFlag;
}






