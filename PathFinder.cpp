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
    //pathFinderInstance = nullptr;
    delete (TopRight); 
    delete (BottomRight); 
    delete (BottomLeft); 
    delete (TopLeft);

    clearDelegates();
}

PathFinder* PathFinder::pathFinderInstance = nullptr; //very imporntant, do not delete!

int PathFinder::countNodes = 0;

PathFinder::Node::Node(FVector posIn){
    gx = std::numeric_limits<float>::max(); //set to max for unknown status by default
    fx = gx;
    pos = posIn;
    camefrom = nullptr;
    closedFlag = false;
    nA = nullptr;
    nB = nullptr;
}

PathFinder::Node::~Node(){
    camefrom = nullptr;
    visible_tangential_Neighbors.clear();
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
    clearDelegates();
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


void PathFinder::clearDelegates(){
    //delete all delegates
    for (int i = 0; i < released.size(); i++){
        FTraceDelegate *delegate = released.at(i);
        if (delegate != nullptr)
        {
            //DebugHelper::logMessage("debug deleted delegate");
            delete delegate;
            
        }
    }
    released.clear();
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

/// @brief acces the pathFinder instance, WILL NOT CREATE ONE
/// BECAUSE WORLD CONTEXT IS NOT PROVIDED, CAN RETURN NULLPTR
/// DO NOT DELETE
/// @return
PathFinder* PathFinder::instance(){
    return pathFinderInstance;
}

/// @brief only call this method to delete the path finder
void PathFinder::deleteInstance(){
    if(pathFinderInstance != nullptr){
        delete pathFinderInstance;
        pathFinderInstance = nullptr;
    }
    
}




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
/// all nodes are independant
/// if wanted
/// @param vec vector to add to graph 
/// @param offset offset to apply to each node
void PathFinder::addNewNodeVector(std::vector<FVector> &vec, FVector &offset){
    for (int i = 0; i < vec.size(); i++){
        addNewNode(vec.at(i) + offset);
    }
}



/// @brief add nodes to the graph, all independant
/// @param vec vector to push completly
void PathFinder::addNewNodeVector(std::vector<FVector>& vec){
    for (int i = 0; i < vec.size(); i++){
        addNewNode(vec.at(i));
    }

}



/// @brief expects the vector to be a convex hull of an object / grounded nodes! Do not ignore!
/// @param vector vector of positions, convex hull!
void PathFinder::addConvexHull(std::vector<FVector> &vec){
    
    //create all nodes
    std::vector<Node *> outNodes;
    for (int i = 0; i < vec.size(); i++){
        PathFinder::Node *n = new PathFinder::Node(vec.at(i));
        outNodes.push_back(n);
    }

    // add the konvex neighbors
    for (int i = 0; i < vec.size(); i++)
    {
        PathFinder::Node *prev = nullptr;
        PathFinder::Node *next = nullptr;

        if (i == 0)
        {
            prev = outNodes.at(outNodes.size() - 1);
        }else{
            prev = outNodes.at(i - 1);
        }


        if(i == outNodes.size() - 1){
            next = outNodes.at(0);
        }
        else{
            next = outNodes.at(i + 1);
        }


        PathFinder::Node *current = outNodes.at(i);
        if(prev != nullptr && current != nullptr && next != nullptr){
            //current->nA = prev;
            //current->nB = next;
            current->setConvexNeighborA(prev); //es wird davon ausgegangen das sich nodes auf der hülle sehen
            current->setConvexNeighborB(next);
        }

    }

    //NEW:
    //new create polygons
    //PathFinder::ConvexPolygon *polygon = new PathFinder::ConvexPolygon(outNodes);
    //polygonstmp.push_back(polygon);


    //alle sofort in graphen ballern
    for (int i = 0; i < outNodes.size(); i++){
        if(outNodes.at(i) != nullptr){
            addNode(outNodes.at(i));

            //NEW:
            //convex hull index setzten für faster path on hull
            //outNodes.at(i)->hullindex = i;
        }
    }
}



/// @brief adds a single node to the graph
/// @param a node to add
void PathFinder::addNewNode(FVector a){
    PathFinder::Quadrant *q = askforQuadrant(a.X, a.Y);
    if(q != nullptr){
        q->add(a);
        
        
        
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
    int x = (int) node.X;
    int y = (int) node.Y;
    PathFinder::Quadrant *q = askforQuadrant(x, y);
    if(q != nullptr){
        PathFinder::Node *nodeFound = q->findNode(node);
        if(nodeFound != nullptr){
            DebugHelper::showScreenMessage("node found path finder", FColor::Green);
            return nodeFound;
        }
    }else{
        DebugHelper::showScreenMessage("QUADRANT IS NULL!!!!!", FColor::Red);
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
            if(asked.size() > 0){
                nodes.insert(nodes.end(), asked.begin(), asked.end());
            }

            
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

    if (GEngine && false)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, string);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, string2);
    }



    //draw nodes
    for (int i = 0; i < nodes.size(); i++){
        //each neighbor, draw line
        PathFinder::Node *current = nodes.at(i);
        if (current != nullptr)
        {
            for (int j = 0; j < current->visible_tangential_Neighbors.size(); j++){
                PathFinder::Node *currNeighbor = current->visible_tangential_Neighbors.at(j);
                if(currNeighbor != nullptr){
                    DebugHelper::showLineBetween(
                        worldPointer,
                        current->pos,
                        currNeighbor->pos,
                        FColor::Red,
                        100.0f
                    );

                }
            }
        }
    }
}



/// @brief returns a path from a given position a to an given position b
/// @param a fvector start point targeted
/// @param b fvector end point targeted
/// @return a path or an emtpy vector if no path was found
std::vector<FVector> PathFinder::getPath(FVector a, FVector b){

    //check if is last path
    if(prevPath.size() > 0){
        FVector s = prevPath.front();
        FVector e = prevPath.back();
        if(
            FVector::Dist(s, a) <= 500 && 
            FVector::Dist(e, b) <= 500
        ){
            return prevPath;
        }
    }

    PathFinder::Node *start = nullptr;
    PathFinder::Node *end = nullptr;
    start = findNode(a);
    if(start == nullptr){
        DebugHelper::showScreenMessage("START NODE NOT FOUND", FColor::Red);
    }

    end = findNode(b);
    if(end == nullptr){
        DebugHelper::showScreenMessage("END NODE NOT FOUND", FColor::Red);
    }



    if(start != nullptr && end != nullptr){
        
        //PREBUILD EDGES
        if(PREBUILD_EDGES_ENABLED){
            showPos(start->pos, FColor::Blue);
            showPos(end->pos, FColor::Purple);
            return findPath_prebuildEdges(start, end);
        }

        //LIVE CREATED EGDES

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
                        if(canSeeTangential(current, n)){
                            

                            float gxNew = current->gx + distance(current->pos, n->pos);
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
    if(FVector::Dist(a->pos, b->pos) <= 500){
        return true;
    }

    //can see
    if (PREBUILD_EDGES_ENABLED == false && canSee(a->pos, b->pos)){
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
bool PathFinder::canSeeTangential(PathFinder::Node *A, PathFinder::Node*B){
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

    }
    return false; //issue: can see false.
}

/// @brief checks with a simple raycasts if nodes can see each other
/// @param Start start node
/// @param End end node
/// @return edge of interest to pass / existent, efficent
bool PathFinder::canSee(FVector &Start, FVector &End){
    if(worldPointer){
        FHitResult HitResult;
		FCollisionQueryParams Params;

        //add params from entity manager (contains all bots for example, which can be ignored)
        //part of a bigger context im working on, comment out or provide your own params
        if(EntityManager *e = worldLevel::entityManager()){
            Params = e->getIgnoredRaycastParams();
        }
    
        //default casting
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
        float upZ = std::abs(AB.GetSafeNormal().Z); //if the normalized vector, Z is close to 1 its paralell to up axis
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



void PathFinder::draw(FVector &pos){
    FVector up = pos + FVector(0, 0, 10000);
    DebugHelper::showLineBetween(worldPointer, pos, up, FColor::Red, 5.0f);
}

//finds a node from a quadrant
PathFinder::Node* PathFinder::Quadrant::findNode(FVector pos){
    int x1 = std::abs(pos.X / CHUNKSIZE);
    int y1 = std::abs(pos.Y / CHUNKSIZE);

    if(map.size() > x1 && map.at(x1).size() > y1){
        if(map.at(x1).at(y1) != nullptr){
            PathFinder::Node* n = map.at(x1).at(y1)->findNode(pos);
            if(n != nullptr){
                //DebugHelper::showScreenMessage("quadrant found node return!", FColor::Green);
                return n;
            }
        }
    }
    //DebugHelper::showScreenMessage("quadrant not found node return!", FColor::Red);
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











/**
 * 
 * 
 * ---- CHUNK METHODS -----
 * 
 * 
 */

/// @brief adds a new node to the vector with a position
/// @param vec position of the node to be added
void PathFinder::Chunk::add(FVector vec){
    //find closest node near by
    

    if(hasNode(vec) == false){
        Node *node = new Node(vec);
        nodes.push_back(node);
        //connects to all nodes if enabled in header
        if(PathFinder *p = PathFinder::instance()){
            p->connect(node);
        }

        PathFinder::countNodes += 1;
    }
}

/// @brief adds a new node to the node with a position
/// @param vec position of the node to be added
void PathFinder::Chunk::add(Node *node){
    if(node != nullptr){
        
        //will only check for duplicate nodes by adress
        for (int i = 0; i < nodes.size(); i++){
            if(nodes.at(i) == node){
                return;
            }
        }
        nodes.push_back(node);
        //connects to all nodes if enabled in header
        if(PREBUILD_EDGES_ENABLED){
            if(PathFinder *p = PathFinder::instance()){
                p->connect(node);
            }
        }
        
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

    
    //test add node
    if(nodes.size() <= 0){
        DebugHelper::showScreenMessage("RETURNED ASYNC CONNECT NODE ", FColor::Yellow);
        return lateadd(pos);
    }


    float closest = std::numeric_limits<float>::max();
    PathFinder::Node *closestNode = nullptr;
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
    if(PathFinder::PREBUILD_EDGES_ENABLED && closestNode == nullptr){
        DebugHelper::showScreenMessage("ASYNC LATE CONNECT NODE ", FColor::Yellow);
        return lateadd(pos);
    }

    return closestNode;


    
}


PathFinder::Node* PathFinder::Chunk::lateadd(FVector pos){
    PathFinder::Node *s = new PathFinder::Node(pos);
    nodes.push_back(s);
    if(PathFinder::PREBUILD_EDGES_ENABLED){
        PathFinder *p = PathFinder::instance();
        if(s != nullptr && p != nullptr){
            p->connect(s);
        }
    }
    return s;
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




/**
 * 
 * --- NODE METHODS ---
 * 
 */

/// @brief resets the nodes: gx, fx, camefrom neighbor and the closed flag
void PathFinder::Node::reset(){
    camefrom = nullptr;
    gx = std::numeric_limits<float>::max(); //is set to max for unknown status
    fx = gx;
    closedFlag = false;
}

void PathFinder::Node::updateCameFrom(float gxIn, float hxEnd, PathFinder::Node &came){
    this->camefrom = &came;

    oldfx = fx; //copy for no reason

    gx = gxIn;
    fx = gxIn + hxEnd;
}


void PathFinder::Node::close(){
    this->closedFlag = true;
}


bool PathFinder::Node::isClosed(){
    return closedFlag;
}

/// @brief returns if has convex hull neighbors
/// @return 
bool PathFinder::Node::hasNeighbors(){
    return nA != nullptr && nB != nullptr;
}

bool PathFinder::Node::hasAnyNeighbors(){
    bool hasN = hasNeighbors();
    return hasN || visible_tangential_Neighbors.size() > 0;
}

/// @brief will set the a neighbor and also add the other convex node to tangential neighbors
/// because IT IS CONVEX!
/// @param n node 
void PathFinder::Node::setConvexNeighborA(Node *n){
    if(n != nullptr){
        nA = n;
        addTangentialNeighbor(n);
    }
}
/// @brief will set the a neighbor and also add the other convex node to tangential neighbors
/// because IT IS CONVEX!
/// @param n node 
void PathFinder::Node::setConvexNeighborB(Node *n){
    if(n != nullptr){
        nB = n;
        addTangentialNeighbor(n);
    }
}
/// @brief adds a node to the tangential connected neighbors, will allow duplicate add. Just dont.
/// will add thread safely
/// @param n must not be nullptr
void PathFinder::Node::addTangentialNeighbor(Node *n){
    if(n != nullptr){
        FScopeLock Lock(&CriticalSection); //lock because of async raycasting
        visible_tangential_Neighbors.push_back(n);
    }
}




/**
 * 
 * 
 * CONNECT SECTION
 * 
 * 
 */



/// @brief connects a node in all quadrants IF ENABLED BOOL IN HEADER FILE
///
/// --- ISSUES I AM AWARE OF : ---
/// if 2 nodes are compared to each other which are part of 1 convex hull the condition
/// of tangentiality wont be ever true. 
/// since it still brings some computanional overhead
/// the plottet nodes will maybe tracked in polygonal shape-objects some time in future.
/// it is unclear for me whether i will implement that because searching for the node
/// in a list brings with O(n) rougly the same overhead as checking the tangential edges for
/// all points, which is also already greatly reduced by limiting a max distance and 
/// the subgraph functionality.
/// ---> it wont be needed most likely
/// @param node node to connect
void PathFinder::connect(Node *node){
    if(node != nullptr && PathFinder::PREBUILD_EDGES_ENABLED){

        //find min max x and y for distance
    
        int lowerX = node->pos.X - PREBUILD_MAXDISTANCE;
        int lowerY = node->pos.Y - PREBUILD_MAXDISTANCE;
        int higherX = node->pos.X + PREBUILD_MAXDISTANCE;
        int higherY = node->pos.Y + PREBUILD_MAXDISTANCE;

        FVector a(lowerX, lowerY, 0);
        FVector b(higherX, higherY, 0);

        std::vector<Node *> enclosedByMaxDistance = getSubGraph(a, b);

        DebugHelper::showScreenMessage("try connect start", FColor::Red);

        for (int i = 0; i < enclosedByMaxDistance.size(); i++){
            Node *compare = enclosedByMaxDistance.at(i);
            if(compare != nullptr && compare != node){
                // includes tangential check if possible!
                if(PathFinder *p = PathFinder::instance()){

                    if(PathFinder::ASYNC_EDGE_PREBUILDING){
                        asyncCanSee(node, enclosedByMaxDistance.at(i));
                    }else{
                        //if (p->canSee(node->pos, enclosedByMaxDistance.at(i)->pos)) 
                        if (p->canSeeTangential(node, enclosedByMaxDistance.at(i))) 
                        {
                            node->addTangentialNeighbor(compare);
                            compare->addTangentialNeighbor(node);

                            //DebugHelper::showLineBetween(worldPointer, node->pos, compare->pos);

                            //DebugHelper::showScreenMessage("connected!");
                            
                        }
                    }
                    
                }
            }
            
        }



    }
}

/// @brief connects two nodes asynchronosly if those are tangential
/// @param a node a
/// @param b node b
/// both nodes must not be nullptr,
/// dont delete the nodes, they are passed into the lambda!
void PathFinder::asyncCanSee(Node *a, Node *b){
    if(a != nullptr && b != nullptr){

        //needs still to pass the tangential check. Remember: if no convex hull, automaically passes the test
        if(!passTangentailCheck(a,b)){
            return;
        }

        if(worldPointer){
            DebugHelper::showScreenMessage("async connect start", FColor::Red);

            FHitResult HitResult;
            FCollisionQueryParams Params;

            //add params from entity manager (contains all bots for example, which can be ignored)
            //part of a bigger context im working on, comment out or provide your own params
            if(EntityManager *e = worldLevel::entityManager()){
                Params = e->getIgnoredRaycastParams();
            }
            
            //async cast if prebuild
            if(PREBUILD_EDGES_ENABLED){

                //bool result = false;
                FVector start = a->pos;
                FVector end = b->pos;

                /**
                 * EAsyncTraceType::Single: Use this for a single line trace (just one raycast).
                 * EAsyncTraceType::Multi: Use this if you want to collect multiple hits along the ray
                 */
                

                FTraceDelegate *MyTraceDelegate = requestDelegate(a, b);
                if(MyTraceDelegate != nullptr){
                    // Now pass the delegate by reference
                    worldPointer->AsyncLineTraceByChannel(
                        EAsyncTraceType::Single,    // Or Multi, depending on what you need
                        start,                      // Start point (FVector)
                        end,                        // End point (FVector)
                        ECC_Visibility,             // Collision channel
                        Params,            // Collision query parameters
                        FCollisionResponseParams(), // Response parameters
                        //&MyTraceDelegate //call back 
                        MyTraceDelegate //call back 
                    );
                }else{
                    DebugHelper::showScreenMessage("issue with delegate occured");
                }

                
            }
        }
    }
}



/// @brief request trace delegate to connect nodes a and b on 
/// @param a 
/// @param b 
/// @return 
FTraceDelegate *PathFinder::requestDelegate(Node *a, Node *b){

    if(a != nullptr && b != nullptr){
        FScopeLock Lock(&delegate_CriticalSection_a);

        FTraceDelegate *delegate = nullptr;
        if (released.size() > 0)
        {
            delegate = released.back();
            released.pop_back();
        }
        if(delegate == nullptr){
            delegate = new FTraceDelegate();
        }
        if(delegate != nullptr){
            delegate->BindLambda(
                [a, b, delegate, this]
                (const FTraceHandle &TraceHandle, FTraceDatum &TraceData){

                // Lambda logic for handling the trace result
                bool bHit = TraceData.OutHits.Num() > 0;

                if(bHit){
                    FHitResult hitP = TraceData.OutHits[0];
                    FVector hitPos = hitP.ImpactPoint;
                    if(FVector::Dist(hitPos, b->pos) <= 100){
                        bHit = false; //testing needed
                        //DebugHelper::showScreenMessage("async trace false positive", FColor::Purple);
                    }

                    
                }

                //no hit, can see.
                if(!bHit){
                    a->addTangentialNeighbor(b);
                    b->addTangentialNeighbor(a);

                    DebugHelper::showScreenMessage("async trace made new", FColor::Yellow);

                    if(this->worldPointer ){
                        DebugHelper::showLineBetween(
                            worldPointer,
                            a->pos,
                            b->pos,
                            FColor::Blue,
                            1.0f
                        );
                    }
                }

                

                if(PathFinder *i = PathFinder::instance()){
                    i->freeDelegate(delegate);
                }        
            });
        }
        
        return delegate;
    }
    return nullptr;
}

/// @brief synchronously releases the ftrace delegate for re usal
/// @param d ftracedelegate to realease
void PathFinder::freeDelegate(FTraceDelegate *d){
    if(d != nullptr){

        d->Unbind();
        FScopeLock Lock(&delegate_CriticalSection_a);
        released.push_back(d);
    }
}







/// @brief custom path finding method for graph with prebuild edges
/// @param start start node
/// @param end end node
/// @return the path if the minimal one found
std::vector<FVector> PathFinder::findPath_prebuildEdges(
    Node *start,
	Node *end
){
    if(start == nullptr || end == nullptr){
        std::vector<FVector> o;
        return o;
    }
    //DebugHelper::showScreenMessage("ask path");
    start->camefrom = nullptr;
    start->closedFlag = false;
    start->gx = 0;
    start->fx = 0;
    end->reset();
    end->camefrom = nullptr;
    end->closedFlag = false;


    //bounding box for traversed nodes
    /*
    FVector center = (start->pos + end->pos) / 2;
    int lowerX = std::min(start->pos.X, end->pos.X);
    int lowerY = std::min(start->pos.Y, end->pos.Y);
    int higherX = std::max(start->pos.X, end->pos.X);
    int higherY = std::max(start->pos.Y, end->pos.Y);

    FVector lower(lowerX, lowerY, 0);
    FVector higher(higherX, higherY, 0);
    */

    //int boundingBoxIncreaseFrac = 2;
    //lower += (center - lower) * boundingBoxIncreaseFrac; // AB = B - A
    //higher += (center - higher) * boundingBoxIncreaseFrac; // AB = B - A



    std::vector<Node *> markedForCleanUp; //must be cleaned before returning path
    priorityQueue open;
    open.add(start);

    while(open.hasNodes()){
        PathFinder::Node *current = open.popLowestFx();
        

        if (current != nullptr)
        {
            //debugDraw
            PathFinder::Node *prevNode = current->camefrom;
            if(prevNode != nullptr){
                DebugHelper::showLineBetween(
                    worldPointer,
                    current->pos,
                    prevNode->pos,
                    FColor::Red,
                    5.0f
                );
            }

        
            markedForCleanUp.push_back(current); // dont forget to push back for cleaning up later
            
            if (current == end){

                std::vector<FVector> outputPath = constructPath(end);
                
                //clean all status to prevent issues, everything must be cleared
                for (int i = 0; i < markedForCleanUp.size(); i++)
                {
                    Node *n = markedForCleanUp.at(i);
                    if(n != nullptr){
                        n->reset();
                    }
                }
                DebugHelper::showScreenMessage("Path Found", FColor::Purple);
                return outputPath;
            }

            //not opened yet
            current->close(); //close node

            //DebugHelper::showScreenMessage("neighbors", current->visible_tangential_Neighbors.size(), FColor::Red);
            
            //traverse NOT opened neighbors and add to open if not added yet (will be handeld by queue automatically)
            for (int i = 0; i < current->visible_tangential_Neighbors.size(); i++){
                Node *neighbor = current->visible_tangential_Neighbors[i];
                if(neighbor != nullptr){
                    if(!neighbor->isClosed()){ //open only if not closed

                        float gxNew = current->gx + distance(current->pos, neighbor->pos);
                        //DebugHelper::showScreenMessage("try gx ", gxNew, FColor::Purple);
                        //DebugHelper::showScreenMessage("compare to gx ", neighbor->gx, FColor::Purple);
                        if(gxNew < neighbor->gx){
                            //DebugHelper::showScreenMessage("update gx ", gxNew, FColor::Green);
                            float hxEnd = distance(neighbor->pos, end->pos);
                            neighbor->updateCameFrom(gxNew, hxEnd, *current);
                        }
                        //ADD TO OPEN LIST!! //if readded is bubbled up automatically!
                        open.add(neighbor);

                        //even if a node wasnt the lowest it must be cleaned later!
                        markedForCleanUp.push_back(neighbor);
                    }else{
                        //DebugHelper::showScreenMessage("is closed", FColor::Purple);
                    }
                }
            }
        }else{
            //issue
            break;
        }
    }

    //no path found, make sure to reset all nodes flag status
    for (int i = 0; i < markedForCleanUp.size(); i++){
        Node *n = markedForCleanUp.at(i);
        if(n != nullptr){
            n->reset();
        }
    }

    DebugHelper::showScreenMessage("no path found");


    std::vector<FVector> placeholder;
    return placeholder;
}


/// @brief checks if a node is within the bounding box enclosed by a and b (ordering is not important)
/// @param a pos a
/// @param b pos b
/// @param check node to check, must not be nullptr
/// @return within box or not. If no node provided, default is false
bool PathFinder::isInBounds(FVector &a, FVector &b, PathFinder::Node *check){
    if(check != nullptr){
        FVector c = check->pos;
        return (a.X <= c.X && a.Y <= c.Y && c.X <= b.X && c.Y <= b.Y);
    }
    return false;
}

/**
 * 
 * --- TANGENTIAL CHECKING ---
 * 
 */


/// @brief needs to pass the tangential check before being a node of interest
/// requires both passed nodes to have their very next neighbors and both neighbors being
/// part of the convex hull of the polygon the nodes / edges were collected from
/// ---> if a or b dont have neighbors (not part of a convex hull, true is automatically returned, test passed.)
/// @param a node a
/// @param b node b
/// @return is tangential: no intersection of polygons or not
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



            
            if(dirAB_ok && dirBA_ok){
                if(worldPointer){
                    //DebugHelper::showLineBetween(worldPointer, a->pos, b->pos, FColor::Green, 100.0f);
                }
            }

            return dirAB_ok && dirBA_ok;
        }

        if(worldPointer && false){
            DebugHelper::showLineBetween(worldPointer, a->pos, b->pos, FColor::Yellow, 100.0f);
        }
        return true; //if is not part of a convexx hull, true by default
    }
    
    return false; //issue 
}









/**
 * 
 * 
 * POLY GON CONVEX HULL SECTION
 * 
 * 
 */
/*
bool PathFinder::Node::sameHull(Node *other){
    if(this->polygon != nullptr && this->polygon == other->polygon){
        return true;
    }
    return false;
}

/// @param nodesIn 
PathFinder::ConvexPolygon(std::vector<PathFinder::Node *> nodesIn){
    //nodes = nodesIn;
    
    //check which nodes can actually see each other?
    //or plain adding? unclear.

    nodes = nodesIn;
}

/// @brief testing needed
/// @param a 
/// @param b 
/// @return 
std::vector<FVector> PathFinder::ConvexPolygon::findFastPathOnHull(Node* a, Node *b){
    if(a == nullptr || b == nullptr){
        std::vector<FVector> none;
        return none;
    }

    

    int aIndex = a->hullindex; //always search from a
    int bIndex = b->hullindex;

    if(
        aIndex != -1 && bIndex != -1 &&
        aIndex < nodes.size() && bIndex < nodes.size()
    ){

        std::vector<Node *> dirA;
        std::vector<Node *> dirB;
        float sumA = 0;
        float sumB = 0;


        dirA.push_back(nodes[aIndex]);
        dirB.push_back(nodes[aIndex]);

        int currentSearch1 = aIndex;//will save the current position in both directions on hull
        int currentSearch2 = aIndex;
        int prevSearch1 = aIndex; //save the prev index
        int prevSearch2 = aIndex;
        bool search1Locked = false;
        bool search2Locked = false;

        while(currentSearch1 != bIndex && currentSearch2 != bIndex){ //look out for target


            //resembles a modulo operation around hull
            if(!search1Locked){
                prevSearch1 = currentSearch1;
                currentSearch1++;
                if(currentSearch1 >= nodes.size()){
                    currentSearch1 = 0; //to front
                }
                //add distance
                Node *prev = nodes[prevSearch1];
                Node *current = nodes[currentSearch1];
                dirA.push_back(current);
                sumA += PathFinder::distance(prev, current);

                if(current == b){
                    search1Locked = true;
                }
            }

            if(!search2Locked){
                prevSearch2 = currentSearch2;
                currentSearch2--;
                if(currentSearch2 < 0){
                    currentSearch2 = nodes.size() - 1; //to back
                }
                //add distance
                Node *prev = nodes[prevSearch2];
                Node *current = nodes[currentSearch2];
                dirB.push_back(current);
                sumB += PathFinder::distance(prev, current);
                //lock search and return in case of better sum
                if(current == b){
                    search2Locked = true;
                }
            }
            
            //if any of the searches reached the destination we need to choose the lower local gx path
            //which is sumA and sumB for clw and cclw on convex hull
            if(search1Locked){
                if(sumA <= sumB){
                    return dirA;
                }
            }
            if(search2Locked){
                if(sumB <= sumA){
                    return dirB;
                }
            }

        }
    }


}
*/