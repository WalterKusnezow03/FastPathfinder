// Fill out your copyright notice in the Description page of Project Settings.


#include "p2/pathFinding/PathFinder.h"
#include "priorityQueue.h"

priorityQueue::priorityQueue()
{
}

priorityQueue::~priorityQueue()
{
}


void priorityQueue::add(PathFinder::Node *node){
    if(node != nullptr){
        //(am letzten index einfügen, bubble up)
        //solange das über mir grösser ist, swap

        if(indexMap.find(node) != indexMap.end()){
            int index = indexMap[node];
            bubbleUpfrom(index); //refresh
        }else{
            nodes.push_back(node);
            bubbleUpfrom(nodes.size() - 1);
        }

    }
}

void priorityQueue::bubbleUpfrom(int index){
    if (nodes.size() > 1 && index > 0 && index < nodes.size()){

        float copyfx = nodes.at(index)->fx;

        
        int parentIndex = (int)((index - 1) / 2); // abrunden default

        
        while (parentIndex >= 0){
            PathFinder::Node *parentNode = nodes.at(parentIndex);
            if(parentNode != nullptr){
                if(parentNode->fx > copyfx){
                    //swap
                    PathFinder::Node *tmp = parentNode;
                    nodes.at(parentIndex) = nodes.at(index);
                    nodes.at(index) = tmp;

                    //replot in index map, updated positions
                    indexMap[nodes.at(parentIndex)] = parentIndex;
                    indexMap[nodes.at(index)] = index;

                    //next level
                    index = parentIndex; //one up
                    parentIndex = (int)((parentIndex - 1) / 2); //one up

                    

                }else{
                    return;
                }
            }else{
                return;
            }
        }
    }
}








PathFinder::Node *priorityQueue::popLowestFx(){
    if(hasNodes()){
        PathFinder::Node *front = nodes.front();
        //remove from index map
        if(front != nullptr){
            indexMap.erase(front);
        }
        downheap();

        if(front != nullptr){
            //DebugHelper::showScreenMessage("popped fx", front->fx);
        }

        return front;
    }
    return nullptr;
}

void priorityQueue::downheap(){
    //special cases
    if(nodes.size() == 1){
        //only one node
        nodes.erase(nodes.begin());
        return;
    }

    //default
    if(nodes.size() > 1){
        nodes.at(0) = nodes.back(); //replace first
        nodes.erase(nodes.begin() + nodes.size() - 1); //rmv last
    }

    

    int parentIndex = 0;
    int left = 1;
    int right = left + 1;

    while(true){
        left = 1 + (parentIndex * 2);
        right = left + 1;

        if(
            parentIndex >= nodes.size() || left >= nodes.size()
        ){
            return;
        }

        // bubble down swap mit left or right (0 based bin heap)
        // child left = 1 + i * 2 
        // child right = left + 1;

        int lowerIndex = left;
        if (right < nodes.size()) //if right exists
        {
            lowerIndex = nodes.at(left)->fx < nodes.at(right)->fx ? left : right;
        }

        //check the lower to get up
        //parent is larger than smaller child
        if(nodes.at(parentIndex)->fx > nodes.at(lowerIndex)->fx){
            //swap
            PathFinder::Node *parentCopy = nodes.at(parentIndex);
            nodes.at(parentIndex) = nodes.at(lowerIndex);
            nodes.at(lowerIndex) = parentCopy;

            //update index map
            indexMap[nodes.at(parentIndex)] = parentIndex;
            indexMap[nodes.at(lowerIndex)] = lowerIndex;

            //next level
            parentIndex = lowerIndex;
            
        }else{
            return;
        }
    }

    
}

bool priorityQueue::hasNodes(){
    return nodes.size() > 0;
}


