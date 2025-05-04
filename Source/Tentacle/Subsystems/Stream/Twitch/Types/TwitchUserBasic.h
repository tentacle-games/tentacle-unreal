// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchUserBasic.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchUserBasic
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FLinearColor
	Color = FLinearColor::White;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	DisplayName;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FName
	Id;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FName
	Name;
};
