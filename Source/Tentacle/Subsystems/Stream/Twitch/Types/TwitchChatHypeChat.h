// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "TwitchChatHypeChat.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchChatHypeChat
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	Amount = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Currency;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	DecimalPlaces = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsSystemMessage = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	Level = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	LocalizedAmount = 0;
};
