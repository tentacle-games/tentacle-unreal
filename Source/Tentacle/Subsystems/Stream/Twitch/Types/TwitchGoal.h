// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchGoalType.h"
#include "TwitchGoal.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchGoal
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Id;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Description;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	ETwitchGoalType
	Type = ETwitchGoalType::Unknown;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	TargetAmount = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	CurrentAmount = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsAchieved = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FDateTime
	StartedAt;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FDateTime
	EndedAt;
};
