// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchUserType.generated.h"

UENUM()
enum class ETwitchUserType : uint8
{
	Mod,
	Staff,
	Admin,
	GlobalMod,
	Unset
};

struct TENTACLE_API FETwitchUserType
{
	using EnumType = ETwitchUserType;

	static const inline auto Mod = FName(TEXT("mod"));
	static const inline auto Staff = FName(TEXT("staff"));
	static const inline auto Admin = FName(TEXT("admin"));
	static const inline auto GlobalMod = FName(TEXT("global_mod"));

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{Mod, EnumType::Mod},
			{Staff, EnumType::Staff},
			{Admin, EnumType::Admin},
			{GlobalMod, EnumType::GlobalMod},
		};
		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EnumType::Unset;
	}

	static FName
	ToName(const EnumType Value)
	{
		static TMap<EnumType, FName> Map = {
			{EnumType::Mod, Mod},
			{EnumType::Staff, Staff},
			{EnumType::Admin, Admin},
			{EnumType::GlobalMod, GlobalMod},
		};

		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : "";
	}
};
