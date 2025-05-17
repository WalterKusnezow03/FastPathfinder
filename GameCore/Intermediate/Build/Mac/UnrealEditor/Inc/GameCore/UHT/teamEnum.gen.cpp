// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameCore/team/teamEnum.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeteamEnum() {}
// Cross Module References
	GAMECORE_API UEnum* Z_Construct_UEnum_GameCore_teamEnum();
	UPackage* Z_Construct_UPackage__Script_GameCore();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_teamEnum;
	static UEnum* teamEnum_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_teamEnum.OuterSingleton)
		{
			Z_Registration_Info_UEnum_teamEnum.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_GameCore_teamEnum, (UObject*)Z_Construct_UPackage__Script_GameCore(), TEXT("teamEnum"));
		}
		return Z_Registration_Info_UEnum_teamEnum.OuterSingleton;
	}
	template<> GAMECORE_API UEnum* StaticEnum<teamEnum>()
	{
		return teamEnum_StaticEnum();
	}
	struct Z_Construct_UEnum_GameCore_teamEnum_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_GameCore_teamEnum_Statics::Enumerators[] = {
		{ "teamEnum::none", (int64)teamEnum::none },
		{ "teamEnum::playerTeam", (int64)teamEnum::playerTeam },
		{ "teamEnum::enemyTeam", (int64)teamEnum::enemyTeam },
		{ "teamEnum::neutralTeam", (int64)teamEnum::neutralTeam },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_GameCore_teamEnum_Statics::Enum_MetaDataParams[] = {
		{ "enemyTeam.Name", "teamEnum::enemyTeam" },
		{ "ModuleRelativePath", "team/teamEnum.h" },
		{ "neutralTeam.Name", "teamEnum::neutralTeam" },
		{ "none.Name", "teamEnum::none" },
		{ "playerTeam.Comment", "//default\n" },
		{ "playerTeam.Name", "teamEnum::playerTeam" },
		{ "playerTeam.ToolTip", "default" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_GameCore_teamEnum_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_GameCore,
		nullptr,
		"teamEnum",
		"teamEnum",
		Z_Construct_UEnum_GameCore_teamEnum_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_GameCore_teamEnum_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_GameCore_teamEnum_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_GameCore_teamEnum_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_GameCore_teamEnum()
	{
		if (!Z_Registration_Info_UEnum_teamEnum.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_teamEnum.InnerSingleton, Z_Construct_UEnum_GameCore_teamEnum_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_teamEnum.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_team_teamEnum_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_team_teamEnum_h_Statics::EnumInfo[] = {
		{ teamEnum_StaticEnum, TEXT("teamEnum"), &Z_Registration_Info_UEnum_teamEnum, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3090084454U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_team_teamEnum_h_1230884727(TEXT("/Script/GameCore"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_team_teamEnum_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_team_teamEnum_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
