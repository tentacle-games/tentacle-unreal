// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchHypeTrainContributionType.generated.h"

UENUM(BlueprintType)
enum class ETwitchHypeTrainContributionType : uint8
{
	Bits,
	Subscription,
	Other,
};

struct TENTACLE_API FETwitchHypeTrainContributionType
{
	using EnumType = ETwitchHypeTrainContributionType;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{"bits", EnumType::Bits},
			{"subscription", EnumType::Subscription},
			{"other", EnumType::Other},
		};

		const auto FindResult = Map.Find(Value);
		return FindResult != nullptr ? *FindResult : EnumType::Other;
	}
};
