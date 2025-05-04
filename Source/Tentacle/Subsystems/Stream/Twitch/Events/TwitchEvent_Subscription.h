// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchUserBasic.h"
#include "TwitchEvent_Subscription.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchEvent_Subscription : public UTwitchEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FName
	UserId;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FName
	UserName;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	UserDisplayName;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Tier;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	bool
	IsGift = false;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);
		jsonField(FName, UserId, Json, "user_id");
		jsonField(FName, UserName, Json, "user_login");
		jsonField(FString, UserDisplayName, Json, "user_name");
		jsonField(FString, Tier, Json, "tier");
		jsonField(bool, IsGift, Json, "is_gift");
	}
};
