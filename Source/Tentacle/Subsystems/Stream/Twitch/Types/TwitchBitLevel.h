// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Engine/DataTable.h"
#include "TwitchBitLevel.generated.h"

UENUM(BlueprintType, Category="Tentacle")
enum class ETwitchBitLevelType : uint8
{
	One,
	OneHundred,
	OneThousand,
	FiveThousand,
	TenThousand,
};

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchBitLevel : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	ETwitchBitLevelType
	Type = ETwitchBitLevelType::One;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	Amount = 1;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	UStaticMesh*
	StaticMesh = nullptr;
};
