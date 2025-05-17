// Copyright Epic Games, Inc. All Rights Reserved.

#include "PathFinderModule.h"
#include "GameCore/DebugHelper.h"

#define LOCTEXT_NAMESPACE "FPathFinderModule"

void FPathFinderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FPathFinderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


/**
 * ATTENTION: PathFinder Collect edges will only be called from this class and only once on level start
 */
void FPathFinderModule::StartPathFinder(UWorld *world){
	if(world == nullptr){
		return;
	}

	if (world)
	{
		EdgeCollector c = EdgeCollector();
		c.getAllEdges(world); //pushes them to the navmesh on its own
	}
}

void FPathFinderModule::EndPathFinder(){
	//clears all nodes from graph
    PathFinder *p = PathFinder::instance();
    if (p != nullptr)
    {
        //p->clear();

        p->deleteInstance();

        FString s = FString::Printf(TEXT("debug end play: deleted path finder"));
        DebugHelper::logMessage(s);
    }
}






#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPathFinderModule, PathFinder)