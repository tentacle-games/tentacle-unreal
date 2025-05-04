// © 2024 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "TwitchChatThreadMessage.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchChatThreadMessage
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString Id;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FName UserId;
};
