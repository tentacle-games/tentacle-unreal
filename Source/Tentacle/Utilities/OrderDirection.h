// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#pragma once

#include "OrderDirection.generated.h"

UENUM(BlueprintType)
enum class EOrderDirection : uint8
{
	Asc,
	Desc,
};

struct TENTACLE_API FEOrderDirection
{
	static const inline auto Asc = FName(TEXT("asc"));
	static const inline auto Desc = FName(TEXT("desc"));

	static FName
	ToName(const EOrderDirection Value)
	{
		static TMap<EOrderDirection, FName> Map = {
			{EOrderDirection::Asc, Asc},
			{EOrderDirection::Desc, Desc},
		};

		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : "";
	}

	static EOrderDirection
	ToEnum(const FName& Value)
	{
		static TMap<FName, EOrderDirection> Map = {
			{Asc, EOrderDirection::Asc},
			{Desc, EOrderDirection::Desc},
		};

		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EOrderDirection::Desc;
	}
};
