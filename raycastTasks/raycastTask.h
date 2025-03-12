
#pragma once
#include "CoreMinimal.h"
#include "p2/pathFinding/PathFinder.h"


class P2_API raycastTask{

public:
    raycastTask();
    ~raycastTask();

    raycastTask(const raycastTask &other);
    raycastTask &operator=(const raycastTask & other);

    void setup(
        UWorld *world,
        PathFinder::Node *aIn,
        PathFinder::Node *bIn
    );

    void execute();

private:
    bool passTangentialCheck();
    bool syncRaycastCanSee();

    UWorld *worldPointer = nullptr;
    PathFinder::Node *a = nullptr;
    PathFinder::Node *b = nullptr;

    bool wasExecuted = false;

    FCriticalSection locker;
};