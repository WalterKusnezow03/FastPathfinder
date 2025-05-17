// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "interfaces/Interactinterface.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GAMECORE_Interactinterface_generated_h
#error "Interactinterface.generated.h already included, missing '#pragma once' in Interactinterface.h"
#endif
#define GAMECORE_Interactinterface_generated_h

#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_SPARSE_DATA
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_RPC_WRAPPERS
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_ACCESSORS
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMECORE_API UInteractinterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInteractinterface) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMECORE_API, UInteractinterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInteractinterface); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	GAMECORE_API UInteractinterface(UInteractinterface&&); \
	GAMECORE_API UInteractinterface(const UInteractinterface&); \
public: \
	GAMECORE_API virtual ~UInteractinterface();


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	GAMECORE_API UInteractinterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	GAMECORE_API UInteractinterface(UInteractinterface&&); \
	GAMECORE_API UInteractinterface(const UInteractinterface&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(GAMECORE_API, UInteractinterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInteractinterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInteractinterface) \
	GAMECORE_API virtual ~UInteractinterface();


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUInteractinterface(); \
	friend struct Z_Construct_UClass_UInteractinterface_Statics; \
public: \
	DECLARE_CLASS(UInteractinterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/GameCore"), GAMECORE_API) \
	DECLARE_SERIALIZER(UInteractinterface)


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_GENERATED_BODY_LEGACY \
		PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_GENERATED_UINTERFACE_BODY() \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_STANDARD_CONSTRUCTORS \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_GENERATED_UINTERFACE_BODY() \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IInteractinterface() {} \
public: \
	typedef UInteractinterface UClassType; \
	typedef IInteractinterface ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_INCLASS_IINTERFACE \
protected: \
	virtual ~IInteractinterface() {} \
public: \
	typedef UInteractinterface UClassType; \
	typedef IInteractinterface ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_10_PROLOG
#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_22_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_SPARSE_DATA \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_RPC_WRAPPERS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_ACCESSORS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_INCLASS_IINTERFACE \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_SPARSE_DATA \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_ACCESSORS \
	FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_13_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAMECORE_API UClass* StaticClass<class UInteractinterface>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
