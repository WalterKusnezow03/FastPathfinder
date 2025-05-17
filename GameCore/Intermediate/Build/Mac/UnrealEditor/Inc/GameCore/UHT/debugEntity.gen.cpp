// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameCore/util/debugEntity.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodedebugEntity() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	GAMECORE_API UClass* Z_Construct_UClass_AdebugEntity();
	GAMECORE_API UClass* Z_Construct_UClass_AdebugEntity_NoRegister();
	GAMECORE_API UClass* Z_Construct_UClass_UDamageinterface_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameCore();
// End Cross Module References
	void AdebugEntity::StaticRegisterNativesAdebugEntity()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AdebugEntity);
	UClass* Z_Construct_UClass_AdebugEntity_NoRegister()
	{
		return AdebugEntity::StaticClass();
	}
	struct Z_Construct_UClass_AdebugEntity_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AdebugEntity_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_GameCore,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AdebugEntity_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "util/debugEntity.h" },
		{ "ModuleRelativePath", "util/debugEntity.h" },
	};
#endif
		const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AdebugEntity_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UDamageinterface_NoRegister, (int32)VTABLE_OFFSET(AdebugEntity, IDamageinterface), false },  // 2638534275
		};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AdebugEntity_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AdebugEntity>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AdebugEntity_Statics::ClassParams = {
		&AdebugEntity::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		UE_ARRAY_COUNT(InterfaceParams),
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AdebugEntity_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AdebugEntity_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AdebugEntity()
	{
		if (!Z_Registration_Info_UClass_AdebugEntity.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AdebugEntity.OuterSingleton, Z_Construct_UClass_AdebugEntity_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AdebugEntity.OuterSingleton;
	}
	template<> GAMECORE_API UClass* StaticClass<AdebugEntity>()
	{
		return AdebugEntity::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AdebugEntity);
	AdebugEntity::~AdebugEntity() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AdebugEntity, AdebugEntity::StaticClass, TEXT("AdebugEntity"), &Z_Registration_Info_UClass_AdebugEntity, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AdebugEntity), 4100078540U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_3843163701(TEXT("/Script/GameCore"),
		Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_util_debugEntity_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
