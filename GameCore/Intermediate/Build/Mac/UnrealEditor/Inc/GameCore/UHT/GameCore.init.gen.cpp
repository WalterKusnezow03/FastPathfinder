// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameCore_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_GameCore;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_GameCore()
	{
		if (!Z_Registration_Info_UPackage__Script_GameCore.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/GameCore",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xE0356E8C,
				0x5617783F,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_GameCore.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_GameCore.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_GameCore(Z_Construct_UPackage__Script_GameCore, TEXT("/Script/GameCore"), Z_Registration_Info_UPackage__Script_GameCore, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xE0356E8C, 0x5617783F));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
