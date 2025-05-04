// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Dom/JsonObject.h"
#include "Tentacle/Utilities/Json.h"
#include "TwitchPoll.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchPollChoice
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Id;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Title;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	BitsVotes = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	ChannelPointsVotes = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	Votes = 0;

	FTwitchPollChoice() = default;

	explicit
	FTwitchPollChoice(const FJsonObjectPtr& Data)
	{
		jsonField(FString, Id, Data, "id");
		jsonField(FString, Title, Data, "title");
		jsonFieldOptional(int32, BitsVotes, Data, "bits_votes");
		jsonFieldOptional(int32, ChannelPointsVotes, Data, "channel_points_votes");
		jsonFieldOptional(int32, Votes, Data, "votes");
	}
};

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchPoll
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Title;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	TArray<FTwitchPollChoice>
	Choices;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsBitsVotingEnabled = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	BitsPerVote = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsChannelPointsVotingEnabled = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	ChannelPointsPerVote = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FDateTime
	StartedAt;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FDateTime
	EndsAt;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Id;

	FTwitchPoll() = default;

	explicit
	FTwitchPoll(const FJsonObjectPtr& Data)
	{
		jsonField(FString, Id, Data, "id");
		jsonField(FString, Title, Data, "title");

		TArray<FJsonObjectPtr> ChoicesJson;
		jsonField(TArray<FJsonObjectPtr>, ChoicesJson, Data, "choices");
		for (const auto& ChoiceJson : ChoicesJson)
			Choices.Add(FTwitchPollChoice(ChoiceJson));

		jsonField(bool, IsBitsVotingEnabled, Data, "bits_voting", "is_enabled");
		jsonField(int32, BitsPerVote, Data, "bits_voting", "amount_per_vote");
		jsonField(bool, IsChannelPointsVotingEnabled, Data, "channel_points_voting", "is_enabled");
		jsonField(int32, ChannelPointsPerVote, Data, "channel_points_voting", "amount_per_vote");
		jsonField(FDateTime, StartedAt, Data, "started_at");
		jsonField(FDateTime, EndsAt, Data, "ends_at");
	}
};
