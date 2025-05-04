// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchBroadcasterType.generated.h"

UENUM()
enum class ETwitchBroadcasterType : uint8
{
	Partner,
	Affiliate,
	Unset
};

struct TENTACLE_API FETwitchBroadcasterType
{
	using EnumType = ETwitchBroadcasterType;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{"partner", EnumType::Partner},
			{"affiliate", EnumType::Affiliate},
		};
		const EnumType* FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EnumType::Unset;
	}
};
