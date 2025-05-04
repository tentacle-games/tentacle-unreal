#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TwitchUtils.generated.h"

#define twitchCommandAssert(Condition, Message) \
	if (!(Condition)) \
	{ \
		UTwitchUtils::SendMessageToTwitchUser(Command.User, Message); \
		return; \
	}

struct FTwitchUser;
struct FChatMessageEmote;
struct FChatMessageEmoji;

UCLASS()
class TENTACLE_API UTwitchUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// UFUNCTION(BlueprintCallable, Category="Tentacle")
	// static void SendMessageToTwitchUser(const FTwitchUser& User, const FString& Message);
};
