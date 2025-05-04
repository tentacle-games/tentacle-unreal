// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Tentacle/Subsystems/Stream/StreamChatMessageUtils.h"
#include "Tentacle/Subsystems/Stream/StreamSharedTypes.h"
#include "Tentacle/Utilities/Json.h"
#include "StreamChatMessage.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UStreamChatMessage : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FChatCommand
	Command;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FDateTime
	CreatedAt;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TMap<FName /*EmojiCode*/, FChatMessageEmoji>
	Emojis;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TMap<FName /*EmoteId*/, FChatMessageEmote>
	Emotes;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Html;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Id;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	EStreamPlatform
	Platform;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Text;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FName
	ViewerId;

	FJsonObjectPtr
	RawData;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		jsonFieldOptional(FName, Command.Name, Json, "$command");
		jsonField(TArray<FString>, Command.Args, Json, "$commandArgs");
		jsonField(FDateTime, CreatedAt, Json, "$createdAt");

		FJsonObjectPtr EmojisJson;
		jsonField(FJsonObjectPtr, EmojisJson, Json, "$emojis");
		UStreamChatMessageUtils::BuildEmojiMap(EmojisJson, Emojis);

		FJsonObjectPtr EmotesJson;
		jsonField(FJsonObjectPtr, EmotesJson, Json, "$emotes");
		UStreamChatMessageUtils::BuildEmoteMap(EmotesJson, Emotes);

		jsonField(FString, Html, Json, "$html");
		jsonField(FString, Id, Json, "$id");
		jsonFieldEnum(EStreamPlatform, Platform, Json, "$platform");
		jsonField(FString, Text, Json, "$text");
		jsonField(FName, ViewerId, Json, "$viewerId");

		RawData = Json;
	}
};
