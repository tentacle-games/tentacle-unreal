// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchReward.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchReward
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName
	Id;

	UPROPERTY(BlueprintReadOnly)
	FName
	Title;

	UPROPERTY(BlueprintReadOnly)
	int32
	Cost = 0;

	UPROPERTY(BlueprintReadOnly)
	FString
	Prompt;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());
		jsonField(FName, Id, Json, "id");
		jsonField(FName, Title, Json, "title");
		jsonField(int32, Cost, Json, "cost");
		jsonField(FString, Prompt, Json, "prompt");
	}
};

UENUM(BlueprintType)
enum class ETwitchRewardRedemptionStatus : uint8
{
	Unknown,
	Unfulfilled,
	Fulfilled,
	Canceled,
};

struct TENTACLE_API FETwitchRewardRedemptionStatusUtils
{
	using EnumType = ETwitchRewardRedemptionStatus;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> EnumLookup = {
			{TEXT("unfulfilled"), EnumType::Unfulfilled},
			{TEXT("fulfilled"), EnumType::Fulfilled},
			{TEXT("canceled"), EnumType::Canceled},
			{TEXT("unknown"), EnumType::Unknown},
		};
		const auto FindResult = EnumLookup.Find(Value);
		return FindResult ? *FindResult : EnumType::Unknown;
	}
};
