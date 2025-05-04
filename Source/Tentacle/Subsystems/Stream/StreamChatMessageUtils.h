// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/StreamSharedTypes.h"
#include "StreamChatMessageUtils.generated.h"

UCLASS()
class TENTACLE_API UStreamChatMessageUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void
	BuildEmojiMap(const TSharedPtr<FJsonObject>& Json, TMap<FName, FChatMessageEmoji>& Emojis);

	static void
	BuildEmoteMap(const TSharedPtr<FJsonObject>& Data, TMap<FName, FChatMessageEmote>& Emotes);

	UFUNCTION(BlueprintPure, Category="Tentacle")
	static bool
	HasEmoji(const class UStreamChatMessage* ChatMessage, const FName EmojiName);

	UFUNCTION(BlueprintPure, Category="Tentacle")
	static int32
	EmojiCount(const UStreamChatMessage* ChatMessage, const FName EmojiName);

	UFUNCTION(BlueprintPure, Category="Tentacle")
	static int32
	EmojiContainingCount(const UStreamChatMessage* ChatMessage, const FString& PartialEmojiName);

	UFUNCTION(BlueprintPure, Category="Tentacle")
	static bool
	HasEmote(const UStreamChatMessage* ChatMessage, const FName EmoteName);

	UFUNCTION(BlueprintPure, Category="Tentacle")
	static int32
	EmoteCount(const UStreamChatMessage* ChatMessage, const FName EmoteName);

	UFUNCTION(BlueprintPure, Category="Tentacle")
	static int32
	EmoteCountContaining(const UStreamChatMessage* ChatMessage, const FString& PartialEmoteName);
};
