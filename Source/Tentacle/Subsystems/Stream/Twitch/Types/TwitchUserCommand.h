#pragma once

#include "TwitchUserCommand.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchUserCommand
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString Name;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	TArray<FString> Args;
};
