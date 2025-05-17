// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameCore/interfaces/Interactinterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInteractinterface() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	GAMECORE_API UClass* Z_Construct_UClass_UInteractinterface();
	GAMECORE_API UClass* Z_Construct_UClass_UInteractinterface_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameCore();
// End Cross Module References
	void UInteractinterface::StaticRegisterNativesUInteractinterface()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UInteractinterface);
	UClass* Z_Construct_UClass_UInteractinterface_NoRegister()
	{
		return UInteractinterface::StaticClass();
	}
	struct Z_Construct_UClass_UInteractinterface_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UInteractinterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_GameCore,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UInteractinterface_Statics::Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "interfaces/Interactinterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UInteractinterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IInteractinterface>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UInteractinterface_Statics::ClassParams = {
		&UInteractinterface::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000840A1u,
		METADATA_PARAMS(Z_Construct_UClass_UInteractinterface_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UInteractinterface_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UInteractinterface()
	{
		if (!Z_Registration_Info_UClass_UInteractinterface.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInteractinterface.OuterSingleton, Z_Construct_UClass_UInteractinterface_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UInteractinterface.OuterSingleton;
	}
	template<> GAMECORE_API UClass* StaticClass<UInteractinterface>()
	{
		return UInteractinterface::StaticClass();
	}
	UInteractinterface::UInteractinterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UInteractinterface);
	UInteractinterface::~UInteractinterface() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UInteractinterface, UInteractinterface::StaticClass, TEXT("UInteractinterface"), &Z_Registration_Info_UClass_UInteractinterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInteractinterface), 1835687221U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_2040112111(TEXT("/Script/GameCore"),
		Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Interactinterface_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
