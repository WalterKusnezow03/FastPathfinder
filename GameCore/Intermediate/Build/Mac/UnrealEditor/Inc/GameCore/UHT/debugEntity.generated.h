// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "util/debugEntity.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GAMECORE_debugEntity_generated_h
#error "debugEntity.generated.h already included, missing '#pragma once' in debugEntity.h"
#endif
#define GAMECORE_debugEntity_generated_h

#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_SPARSE_DATA
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_RPC_WRAPPERS
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_ACCESSORS
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAdebugEntity(); \
	friend struct Z_Construct_UClass_AdebugEntity_Statics; \
public: \
	DECLARE_CLASS(AdebugEntity, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GameCore"), NO_API) \
	DECLARE_SERIALIZER(AdebugEntity) \
	virtual UObject* _getUObject() const override { return const_cast<AdebugEntity*>(this); }


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_INCLASS \
private: \
	static void StaticRegisterNativesAdebugEntity(); \
	friend struct Z_Construct_UClass_AdebugEntity_Statics; \
public: \
	DECLARE_CLASS(AdebugEntity, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GameCore"), NO_API) \
	DECLARE_SERIALIZER(AdebugEntity) \
	virtual UObject* _getUObject() const override { return const_cast<AdebugEntity*>(this); }


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AdebugEntity(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AdebugEntity) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AdebugEntity); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AdebugEntity); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AdebugEntity(AdebugEntity&&); \
	NO_API AdebugEntity(const AdebugEntity&); \
public: \
	NO_API virtual ~AdebugEntity();


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AdebugEntity(AdebugEntity&&); \
	NO_API AdebugEntity(const AdebugEntity&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AdebugEntity); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AdebugEntity); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AdebugEntity) \
	NO_API virtual ~AdebugEntity();


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_13_PROLOG
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_SPARSE_DATA \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_RPC_WRAPPERS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_ACCESSORS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_INCLASS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_SPARSE_DATA \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_ACCESSORS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_INCLASS_NO_PURE_DECLS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAMECORE_API UClass* StaticClass<class AdebugEntity>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
