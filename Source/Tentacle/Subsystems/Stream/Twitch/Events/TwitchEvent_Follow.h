// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent.h"
#include "TwitchEvent_Follow.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchEvent_Follow : public UTwitchEvent
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

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		jsonField(FName, UserId, Json, "user_id");
		jsonField(FName, UserName, Json, "user_name");
		jsonField(FString, UserDisplayName, Json, "user_display_name");
	}
};
