// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "Tentacle/Subsystems/Stream/StreamChatMessageUtils.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent.h"
#include "TwitchEvent_SubscriptionMessage.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchEvent_SubscriptionMessage : public UTwitchEvent
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
	FString
	Message;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TMap<FName, FChatMessageEmoji>
	Emojis;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TMap<FName, FChatMessageEmote>
	Emotes;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	CumulativeMonths = 0;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	StreakMonths = 0; // -1 if info not available

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	DurationMonths = 0;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);
		jsonField(FName, UserId, Json, "user_id");
		jsonField(FName, UserName, Json, "user_login");
		jsonField(FString, UserDisplayName, Json, "user_name");
		jsonField(FString, Message, Json, "message", "text");

		FJsonObjectPtr EmotesJson;
		jsonField(FJsonObjectPtr, EmotesJson, Json, "message", "emotes");
		UStreamChatMessageUtils::BuildEmoteMap(EmotesJson, Emotes);

		FJsonObjectPtr EmojisJson;
		jsonField(FJsonObjectPtr, EmojisJson, Json, "message", "emojis");
		UStreamChatMessageUtils::BuildEmojiMap(EmojisJson, Emojis);

		jsonField(FString, Tier, Json, "tier");
		jsonField(int32, CumulativeMonths, Json, "cumulative_months");
		jsonField(int32, StreakMonths, Json, "streak_months");
		jsonField(int32, DurationMonths, Json, "duration_months");
	}
};
