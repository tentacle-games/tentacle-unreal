// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Tentacle/Utilities/Common.h"
#include "Tentacle/Subsystems/Stream/StreamChatMessage.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchChatHypeChat.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchChatParentMessage.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchChatThreadMessage.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchUser.h"
#include "TwitchChatMessage.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchChatMessage : public UStreamChatMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString
	RaidBroadcasterId;

	UPROPERTY(BlueprintReadOnly)
	FDateTime
	RaidCreatedAt;

	UPROPERTY(BlueprintReadOnly)
	int32
	Bits = 0;

	UPROPERTY(BlueprintReadOnly)
	FName
	ChannelId;

	UPROPERTY(BlueprintReadOnly)
	FTwitchChatHypeChat
	HypeChat;

	UPROPERTY(BlueprintReadOnly)
	bool
	IsCheer = false;

	UPROPERTY(BlueprintReadOnly)
	bool
	IsFirst = false;

	UPROPERTY(BlueprintReadOnly)
	bool
	IsHighlight = false;

	UPROPERTY(BlueprintReadOnly)
	bool
	IsHypeChat = false;

	UPROPERTY(BlueprintReadOnly)
	bool
	IsRedemption = false;

	UPROPERTY(BlueprintReadOnly)
	bool
	IsReply = false;

	UPROPERTY(BlueprintReadOnly)
	bool
	IsReturningChatter = false;

	UPROPERTY(BlueprintReadOnly)
	FTwitchChatParentMessage
	ParentMessage;

	UPROPERTY(BlueprintReadOnly)
	FName
	RewardId;

	UPROPERTY(BlueprintReadOnly)
	FTwitchChatThreadMessage
	ThreadMessage;

	UPROPERTY(BlueprintReadOnly)
	FTwitchUser
	User;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		jsonFieldOptional(FString, RaidBroadcasterId, Json, "$raidBroadcasterId");
		jsonFieldOptional(FDateTime, RaidCreatedAt, Json, "$raidCreatedAt");
		jsonField(int32, Bits, Json, "bits");
		jsonFieldOptional(FName, ChannelId, Json, "channel_id");
		jsonFieldOptional(int32, HypeChat.Amount, Json, "hype_chat_amount");
		jsonFieldOptional(FString, HypeChat.Currency, Json, "hype_chat_currency");
		jsonFieldOptional(int32, HypeChat.DecimalPlaces, Json, "hype_chat_decimal_places");
		jsonFieldOptional(bool, HypeChat.IsSystemMessage, Json, "hype_chat_is_system_message");
		jsonFieldOptional(int32, HypeChat.Level, Json, "hype_chat_level");
		jsonFieldOptional(int32, HypeChat.LocalizedAmount, Json, "hype_chat_localized_amount");
		jsonField(bool, IsCheer, Json, "is_cheer");
		jsonField(bool, IsFirst, Json, "is_first");
		jsonField(bool, IsHighlight, Json, "is_highlight");
		jsonField(bool, IsHypeChat, Json, "is_hype_chat");
		jsonField(bool, IsRedemption, Json, "is_redemption");
		jsonField(bool, IsReply, Json, "is_reply");
		jsonField(bool, IsReturningChatter, Json, "is_returning_chatter");
		jsonFieldOptional(FString, ParentMessage.Id, Json, "parent_message_id");
		jsonFieldOptional(FString, ParentMessage.Text, Json, "parent_message_text");
		jsonFieldOptional(FString, ParentMessage.User.DisplayName, Json, "parent_message_user_display_name");
		jsonFieldOptional(FName, ParentMessage.User.Id, Json, "parent_message_user_id");
		jsonFieldOptional(FName, ParentMessage.User.Name, Json, "parent_message_user_name");
		jsonFieldOptional(FName, RewardId, Json, "reward_id");
		jsonFieldOptional(FString, ThreadMessage.Id, Json, "thread_message_id");
		jsonFieldOptional(FName, ThreadMessage.UserId, Json, "thread_message_user_id");

		FJsonObjectPtr UserInfoJson;
		jsonField(FJsonObjectPtr, UserInfoJson, Json, "user_info");
		User.SetFromJson(UserInfoJson);
	}
};
