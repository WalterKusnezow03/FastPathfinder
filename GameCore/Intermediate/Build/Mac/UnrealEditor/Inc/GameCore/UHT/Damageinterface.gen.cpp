// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameCore/interfaces/Damageinterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDamageinterface() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	GAMECORE_API UClass* Z_Construct_UClass_UDamageinterface();
	GAMECORE_API UClass* Z_Construct_UClass_UDamageinterface_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameCore();
// End Cross Module References
	void UDamageinterface::StaticRegisterNativesUDamageinterface()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UDamageinterface);
	UClass* Z_Construct_UClass_UDamageinterface_NoRegister()
	{
		return UDamageinterface::StaticClass();
	}
	struct Z_Construct_UClass_UDamageinterface_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UDamageinterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_GameCore,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDamageinterface_Statics::Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "interfaces/Damageinterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UDamageinterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IDamageinterface>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UDamageinterface_Statics::ClassParams = {
		&UDamageinterface::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UDamageinterface_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UDamageinterface_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UDamageinterface()
	{
		if (!Z_Registration_Info_UClass_UDamageinterface.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDamageinterface.OuterSingleton, Z_Construct_UClass_UDamageinterface_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UDamageinterface.OuterSingleton;
	}
	template<> GAMECORE_API UClass* StaticClass<UDamageinterface>()
	{
		return UDamageinterface::StaticClass();
	}
	UDamageinterface::UDamageinterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDamageinterface);
	UDamageinterface::~UDamageinterface() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Damageinterface_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Damageinterface_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UDamageinterface, UDamageinterface::StaticClass, TEXT("UDamageinterface"), &Z_Registration_Info_UClass_UDamageinterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDamageinterface), 2638534275U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Damageinterface_h_730108121(TEXT("/Script/GameCore"),
		Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Damageinterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_interfaces_Damageinterface_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
