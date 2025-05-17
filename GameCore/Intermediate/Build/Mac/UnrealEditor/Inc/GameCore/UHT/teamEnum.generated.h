// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "team/teamEnum.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GAMECORE_teamEnum_generated_h
#error "teamEnum.generated.h already included, missing '#pragma once' in teamEnum.h"
#endif
#define GAMECORE_teamEnum_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UnrealProjects_p2_Plugins_GameCore_Source_GameCore_team_teamEnum_h


#define FOREACH_ENUM_TEAMENUM(op) \
	op(teamEnum::none) \
	op(teamEnum::playerTeam) \
	op(teamEnum::enemyTeam) \
	op(teamEnum::neutralTeam) 

enum class teamEnum;
template<> struct TIsUEnumClass<teamEnum> { enum { Value = true }; };
template<> GAMECORE_API UEnum* StaticEnum<teamEnum>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
