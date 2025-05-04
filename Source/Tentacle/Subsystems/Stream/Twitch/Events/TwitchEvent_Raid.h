// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent.h"
#include "TwitchEvent_Raid.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchEvent_Raid : public UTwitchEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FName
	FromBroadcasterUserId;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FName
	FromBroadcasterUserName;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	FromBroadcasterUserDisplayName;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	Viewers = 0;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);
		jsonField(FName, FromBroadcasterUserId, Json, "from_broadcaster_user_id");
		jsonField(FName, FromBroadcasterUserName, Json, "from_broadcaster_user_login");
		jsonField(FString, FromBroadcasterUserDisplayName, Json, "from_broadcaster_user_name");
		jsonField(int32, Viewers, Json, "viewers");
	}
};
