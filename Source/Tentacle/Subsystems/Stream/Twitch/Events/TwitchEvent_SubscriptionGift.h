// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchUserBasic.h"
#include "TwitchEvent_SubscriptionGift.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchEvent_SubscriptionGift : public UTwitchEvent
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
	int32
	Total = 0;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	CumulativeTotal = 0; // -1 if info not available

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	bool
	IsAnonymous = false;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);
		jsonField(FName, UserId, Json, "user_id");
		jsonField(FString, UserDisplayName, Json, "user_name");
		jsonField(FName, UserName, Json, "user_login");
		jsonField(FString, Tier, Json, "tier");
		jsonField(int32, Total, Json, "total");
		jsonField(int32, CumulativeTotal, Json, "cumulative_total");
		jsonField(bool, IsAnonymous, Json, "is_anonymous");
	}
};
