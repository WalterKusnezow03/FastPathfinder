// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GAMECORE_API AActorUtil
{
public:

	static void findDirectChildsByName(AActor &actor, FString namerfac, TArray<UChildActorComponent *> &container);

	static void findAllChildsByName(AActor &actor, FString namepart, TArray<UChildActorComponent *> &container);

	//show and hide
	static void showActor(AActor &actor, bool show);
	static void showChildActorComponent(UChildActorComponent &component, bool show);

	//collision
	static void enableColliderOnActor(AActor &actor, bool enable);

	//calulate bounds
	static void calculateActorBounds(AActor *actor, int &x, int &y, int &z);
	static void calculateActorBounds(AActor *actor, int &x, int &y, int &z, FVector &origin, FVector &extent);
	

	/// @brief finds all components of a type starting from
	/// UObject
	///		UActorComponent
	///			USceneComponent
	///				UPrimitiveComponent
	///					UStaticMeshComponent
	///					to USkeletalMeshComponent
	/// @tparam T derived from UActorComponent or more 
	/// @param actor 
	/// @param container 
	template <typename T>
	static void findAllComponentsByType(AActor &actor, std::vector<T *> &container){
		static_assert(std::is_base_of<UActorComponent, T>::value, "must be UActorComponent derived");
		/**
		 * UObject
			UActorComponent
				USceneComponent
					UPrimitiveComponent
						UStaticMeshComponent
						USkeletalMeshComponent
		 */
	
		//check childs
		TArray<UChildActorComponent *> childActors;
		actor.GetComponents<UChildActorComponent>(childActors);
		for (int i = 0; i < childActors.Num(); i++){
			if(UChildActorComponent *c = childActors[i]){
	
				//get aactor from the uchildactor component
				AActor *fromChild = c->GetChildActor();
				if (fromChild != nullptr)
				{
					findAllComponentsByType<T>(*fromChild, container);
				}
			}
		}
	
		//check own
		TArray<T *> foundOfType;
		actor.GetComponents<T>(foundOfType);
		for (int i = 0; i < foundOfType.Num(); i++){
			if(T *t = foundOfType[i]){
				container.push_back(t);
			}
		}
	}





private:
	AActorUtil();
	~AActorUtil();
};
