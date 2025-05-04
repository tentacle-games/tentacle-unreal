// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchUserBasic.h"
#include "TwitchEvent_Cheer.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchEvent_Cheer : public UTwitchEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	Bits = 0;

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
	bool
	IsAnonymous = false;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Message;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);
		jsonField(int32, Bits, Json, "bits");
		jsonField(bool, IsAnonymous, Json, "is_anonymous");
		jsonField(FString, Message, Json, "message");
		jsonFieldOptional(FName, UserId, Json, "user_id");
		jsonFieldOptional(FName, UserName, Json, "user_login");
		jsonFieldOptional(FString, UserDisplayName, Json, "user_name");
	}
};
