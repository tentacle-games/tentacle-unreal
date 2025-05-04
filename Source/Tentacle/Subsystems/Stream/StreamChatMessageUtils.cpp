// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "StreamChatMessageUtils.h"
#include "Tentacle/Subsystems/Stream/StreamChatMessage.h"

void
UStreamChatMessageUtils::BuildEmojiMap(const FJsonObjectPtr& Json, TMap<FName, FChatMessageEmoji>& Emojis)
{
	softAssert(Json.IsValid());

	for (const auto& EmojiEntry : Json->Values)
	{
		FJsonObjectPtr* EmojiJsonPtr;
		if (EmojiEntry.Value->TryGetObject(EmojiJsonPtr))
		{
			const auto EmojiJson = *EmojiJsonPtr;

			FChatMessageEmoji Emoji;
			jsonField(FName, Emoji.Code, EmojiJson, "code")
			jsonField(FName, Emoji.Name, EmojiJson, "name")
			jsonField(int32, Emoji.Count, EmojiJson, "count")

			const auto Positions = EmojiJson->GetArrayField(TEXT("positions"));
			for (const auto& PositionJson : Positions)
			{
				FJsonObjectPtr* PositionJsonPtr;
				if (PositionJson->TryGetObject(PositionJsonPtr))
				{
					const auto PositionObjectJson = *PositionJsonPtr;

					FStringPosition Position;
					jsonField(int32, Position.Start, PositionObjectJson, "start")
					jsonField(int32, Position.End, PositionObjectJson, "end");
					Emoji.Positions.Add(Position);
				}

				Emojis.Add(Emoji.Name, Emoji);
			}
		}
	}
}

void
UStreamChatMessageUtils::BuildEmoteMap(const TSharedPtr<FJsonObject>& Data, TMap<FName, FChatMessageEmote>& Emotes)
{
	softAssert(Data.IsValid());

	for (const auto& [EmoteKey, EmoteValue] : Data->Values)
	{
		FJsonObjectPtr* EmoteJsonPtr;
		if (EmoteValue->TryGetObject(EmoteJsonPtr))
		{
			const auto EmoteJson = *EmoteJsonPtr;

			FChatMessageEmote Emote;
			jsonField(FName, Emote.Id, EmoteJson, "id")
			jsonField(FName, Emote.Name, EmoteJson, "name")
			jsonField(int32, Emote.Count, EmoteJson, "count")

			const auto Positions = EmoteJson->GetArrayField(TEXT("positions"));
			for (const auto& PositionJson : Positions)
			{
				FJsonObjectPtr* PositionJsonPtr;
				if (PositionJson->TryGetObject(PositionJsonPtr))
				{
					const auto PositionObjectJson = *PositionJsonPtr;

					FStringPosition Position;
					jsonField(int32, Position.Start, PositionObjectJson, "start")
					jsonField(int32, Position.End, PositionObjectJson, "end");
					Emote.Positions.Add(Position);
				}
			}

			Emotes.Add(Emote.Name, Emote);
		}
	}
}

bool
UStreamChatMessageUtils::HasEmoji(const UStreamChatMessage* ChatMessage, const FName EmojiName)
{
	return ChatMessage->Emojis.Contains(EmojiName);
}

int32
UStreamChatMessageUtils::EmojiCount(const UStreamChatMessage* ChatMessage, const FName EmojiName)
{
	if (!ChatMessage->Emojis.Contains(EmojiName))
		return 0;

	return ChatMessage->Emojis[EmojiName].Count;
}

int32
UStreamChatMessageUtils::EmojiContainingCount(const UStreamChatMessage* ChatMessage, const FString& PartialEmojiName)
{
	int32 Count = 0;

	for (const auto& [EmojiName, Emoji] : ChatMessage->Emojis)
	{
		if (Emoji.Name.ToString().Contains(PartialEmojiName))
			Count += Emoji.Count;
	}

	return Count;
}

bool
UStreamChatMessageUtils::HasEmote(const UStreamChatMessage* ChatMessage, const FName EmoteName)
{
	return ChatMessage->Emotes.Contains(EmoteName);
}

int32
UStreamChatMessageUtils::EmoteCount(const UStreamChatMessage* ChatMessage, const FName EmoteName)
{
	if (!ChatMessage->Emotes.Contains(EmoteName))
		return 0;

	return ChatMessage->Emotes[EmoteName].Count;
}

int32
UStreamChatMessageUtils::EmoteCountContaining(const UStreamChatMessage* ChatMessage, const FString& PartialEmoteName)
{
	int32 Count = 0;

	for (const auto& [EmoteName, Emote] : ChatMessage->Emotes)
	{
		if (Emote.Name.ToString().Contains(PartialEmoteName))
			Count += Emote.Count;
	}

	return Count;
}
