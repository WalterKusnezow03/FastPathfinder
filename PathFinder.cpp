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
    nA = nullptr;
    nB = nullptr;
}

PathFinder::Node::~Node(){
    camefrom = nullptr;
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

//clear functions

/// @brief clears all nodes from the whole navmesh but doesnt delete the chunks
void PathFinder::clear(){
    TArray<PathFinder::Quadrant*> array = {TopLeft, BottomLeft, TopRight, BottomRight};
    for (int i = 0; i < array.Num(); i++){
        if(array[i] != nullptr){
            array[i]->clear();
        }
    }
}

void PathFinder::Quadrant::clear(){
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map.at(i).size(); j++){
            PathFinder::Chunk *c = map.at(i).at(j);
            if(c != nullptr){
                c->clear();
            }
        }
    }
}

void PathFinder::Chunk::clear(){
    for (int i = 0; i < nodes.size(); i++){
        if(nodes.at(i) != nullptr){
            delete (nodes.at(i));
            nodes.at(i) = nullptr;
        }
    }
    nodes.clear(); //finally clear the nodes
}



//clear functions end

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

//not recommended
/*
void PathFinder::deleteInstance(){
    if(pathFinderInstance != nullptr){
        delete pathFinderInstance;
        pathFinderInstance = nullptr;
    }
}*/



//debug drawing
void PathFinder::showPos(FVector e){
    if(debugDrawNodes){
        showPos(e, FColor::Green);
    }
}

void PathFinder::showPos(FVector e, FColor c){
    if(worldPointer && debugDrawNodes){
        FVector End = e + FVector(0, 0, 10000);
        DebugHelper::showLineBetween(worldPointer, e, End, c);
    }
}


/// @brief adds a new node vector (of locations) to the graph and applies an offset to each node
/// if wanted
/// @param vec vector to add to graph 
/// @param offset offset to apply to each node
void PathFinder::addNewNodeVector(std::vector<FVector> &vec, FVector &offset){
    for (int i = 0; i < vec.size(); i++){
        addNewNode(vec.at(i) + offset);
    }
}



/// @brief add nodes to the graph
/// @param vec vector to push completly
void PathFinder::addNewNodeVector(std::vector<FVector>& vec){
    for (int i = 0; i < vec.size(); i++){
        addNewNode(vec.at(i));
    }

    //debugCountNodes();
}

/// @brief adds a single node to the graph
/// @param a node to add
void PathFinder::addNewNode(FVector a){
    PathFinder::Quadrant *q = askforQuadrant(a.X, a.Y);
    if(q != nullptr){
        q->add(a);
        
        
        //debug testing for checking if nodes were added, works properly
        /*
        PathFinder::Node *tryFind = findNode(a);
        if(tryFind != nullptr){
            showPos(tryFind->pos, FColor::Purple);
        }*/
        
    }
}

void PathFinder::addNode(Node * node){
    if(node != nullptr){
        FVector posCopy = node->pos;
        PathFinder::Quadrant *q = askforQuadrant(posCopy.X, posCopy.Y);
        if(q != nullptr){
            q->add(node);
        }
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
        //check if is last path
        if(prevPath.size() > 0){
            FVector s = prevPath.front();
            FVector e = prevPath.back();
            if(
                FVector::Dist(s, start->pos) <= 300 && 
                FVector::Dist(e, end->pos) <= 300
            )
            //if (s == start->pos && e == end->pos)
            {
                return prevPath;
            }
        }
    

        //find path
        std::vector<PathFinder::Node *> graph = getSubGraph(a, b);
        
        if(debugDrawNodes){
            showPos(start->pos, FColor::Blue);
            showPos(end->pos, FColor::Red);
            DebugHelper::showLineBetween(worldPointer, start->pos, end->pos, FColor::Yellow);
        }
        

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
    //screenMessage(FString::Printf(TEXT("subgraph size %d"), subgraph.size()));
    

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
            if(reached(current, end)){
            //if(current == end){ //|| canSee(current, end)){
                //path found
                //screenMessage("found path");
                return constructPath(end);
            }

            //show opened nodes: debugging
            if(debugDrawNodes){
                showPos(current->pos, FColor::Blue);
            }
            

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


bool PathFinder::reached(Node *a, Node *b){
    if(a == nullptr || b == nullptr){
        return false;
    }
    if(a == b){
        return true;
    }
    //neighbor

    //distance
    if(FVector::Dist(a->pos, b->pos) <= 200){
        return true;
    }

    //can see
    if (canSee(a->pos, b->pos)){
        return true;
    }
    return false;
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

        // if edge is too vertical and to high: ignore, cant climb walls.
        // AB = B - A;
        if(isCloseAndTooVertical(A, B)){
            return false;
        }

        //pass tangental check to check for raycast or not
        if (passTangentailCheck(A,B) == false){
            return false; //not tangential, do not check
        }

        // vision checking
        FVector Start = A->pos;
        FVector End = B->pos;
        //testing with more raycasts to ensure realibilty
        if (canSee(Start, End)){
            return true;
        }

        //adjustments if any entity might be in way
        Start.Z += ONE_METER * 1.7f;
        End.Z += ONE_METER * 1.7f;
        if (canSee(Start, End)){
            return true;
        }

        

        
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
    return false; //issue: can see false.
}

/// @brief checks with a simple raycasts if nodes can see each other
/// @param Start 
/// @param End 
/// @return 
bool PathFinder::canSee(FVector &Start, FVector &End){
    if(worldPointer){
        FHitResult HitResult;
		FCollisionQueryParams Params;

        //add params from entity manager (contains all bots for example, which can be ignored)
        //part of a bigger context im working on, comment out or provide your own params
        if(EntityManager *e = worldLevel::entityManager()){
            Params = e->getIgnoredRaycastParams();
        }

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
    prevPath = list; //save copy
    return list;
}

/// @brief if edge is too vertical and to high: ignore, cant climb walls.
/// @param a node a 
/// @param b node b
/// @return too close and vertical true or false
bool PathFinder::isCloseAndTooVertical(Node *a, Node *b){

    if(a != nullptr && b != nullptr){
        // AB = B - A;
        FVector AB = b->pos - a->pos;
        float upZ = std::abs(AB.GetSafeNormal().Z);
        float scale = std::abs(AB.Z);
        if (upZ > 0.8f)
        {
            // skalarproduct up is near one / paralell to z axis
            if (AB.Z > ONE_METER)
            {
                return true;
            }
        }
    }
    return false;
}

/***
 * ---- QUADRANT METHODS ----
 */

/// @brief adds a node to the quadrant
/// @param n position to add
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


/// @brief adds a node to the quadrant (node node)
/// @param n position to add
void PathFinder::Quadrant::add(Node *n){
    if(n != nullptr){
        //std::abs for flipping negatives obviosuly
        int x = std::abs(n->pos.X / CHUNKSIZE); //create new chunks?
        int y = std::abs(n->pos.Y / CHUNKSIZE);

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
    lowerX = std::min(a.X, b.X); //-CHUNKSIZE; //+ extension
    lowerY = std::min(a.Y, b.Y); //- CHUNKSIZE;
    higherX = std::max(a.X, b.X); //+ CHUNKSIZE;
    higherY = std::max(a.Y, b.Y); //+ CHUNKSIZE;

    bool extendBounds = false;
    if(extendBounds){
        lowerX += - CHUNKSIZE; //+ extension
        lowerY += - CHUNKSIZE;
        higherX += CHUNKSIZE;
        higherY += CHUNKSIZE;
    }

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

/// @brief adds a new node to the node with a position
/// @param vec position of the node to be added
void PathFinder::Chunk::add(Node *node){
    if(node != nullptr){
        /*
        //find closest node near by
        if(hasNode(node->pos) == false){
            nodes.push_back(node);
            PathFinder::countNodes += 1;
        }
        */
        //will only check for duplicate nodes by adress
        for (int i = 0; i < nodes.size(); i++){
            if(nodes.at(i) == node){
                return;
            }
        }
        nodes.push_back(node);
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


bool PathFinder::Node::hasNeighbors(){
    return nA != nullptr && nB != nullptr;
}



/// @brief needs to pass the tangential check before being a node of interest
/// requires both passed nodes to have their very next neighbors and both neighbors being
/// part of the convex hull of the polygon the nodes / edges were collected from
/// @param a node a
/// @param b node b
/// @return is tangential no intersect or not
bool PathFinder::passTangentailCheck(Node *a, Node *b){
    if(a != nullptr && b != nullptr)
    {
        //must be tangential no intersect on both sides to be an connection of intersect
        if(a->hasNeighbors() && b->hasNeighbors())
        {
            bool dirAB_ok = false;
            FVector v0 = b->pos - a->pos;
            FVector vN(v0.Y, -v0.X, 0); // 90 grad drehen: - für eine var, xy tauschen, einen component negieren

            FVector v1 = b->nA->pos - b->pos; // AB = B - A connect to first neighbor
            FVector v2 = b->nB->pos - b->pos; //connect to second neighbor

            //(vN dot v1) * (vN dot v2) > 0 damit beide vektoren auf der selben seite sind. tangentiale konvexe verbindung
            float dotProduct1 = (vN.X * v1.X) + (vN.Y * v1.Y);
            float dotProduct2 = (vN.X * v2.X) + (vN.Y * v2.Y);
            if(dotProduct1 * dotProduct2 >= 0) // >=
            {//vorzeichen gleich, >0 selbe seite
                dirAB_ok = true;
            }


            bool dirBA_ok = false;
            v0 = a->pos - b->pos;

            v1 = (a->nA->pos - a->pos); // AB = B - A connect to first neighbor
            v2 = (a->nB->pos - a->pos); //connect to second neighbor

            //(vN dot v1) * (vN dot v2) > 0 damit beide vektoren auf der selben seite sind. tangentiale konvexe verbindung
            dotProduct1 = (vN.X * v1.X) + (vN.Y * v1.Y);
            dotProduct2 = (vN.X * v2.X) + (vN.Y * v2.Y);
            if(dotProduct1 * dotProduct2 >= 0){//vorzeichen gleich, >0 selbe seite
                dirBA_ok = true;
            }



            /*
            if(dirAB_ok && dirBA_ok){
                if(worldPointer){
                    FVector up(0, 0, 100);
                    DebugHelper::showLineBetween(worldPointer, a->pos, (a->pos + up), FColor::Red);
                    DebugHelper::showLineBetween(worldPointer, b->pos, (b->pos + up), FColor::Red);
                }
            }*/

            return dirAB_ok && dirBA_ok;
        }
        return true;
    }

    return true; //no neighbors, check raycasts
}