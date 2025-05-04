// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Utilities/Json.h"
#include "TwitchSubscription.generated.h"

UENUM(BlueprintType)
enum class ETwitchSubscriptionTier : uint8
{
	Tier1,
	Tier2,
	Tier3,
	Unset
};

struct TENTACLE_API FETwitchSubscriptionTier
{
	using EnumType = ETwitchSubscriptionTier;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{TEXT("1000"), EnumType::Tier1},
			{TEXT("2000"), EnumType::Tier2},
			{TEXT("3000"), EnumType::Tier3},
		};
		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EnumType::Unset;
	}
};

USTRUCT(BlueprintType)
struct FTwitchSubscription
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FName
	GifterId;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	GifterName;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	GifterDisplayName;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	bool
	IsGift = false;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	ETwitchSubscriptionTier
	Tier = ETwitchSubscriptionTier::Unset;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		jsonFieldOptional(FName, GifterId, Json, "gifterId");
		jsonFieldOptional(FString, GifterName, Json, "gifterName");
		jsonFieldOptional(FString, GifterDisplayName, Json, "gifterDisplayName");
		jsonField(bool, IsGift, Json, "isGift");
		jsonFieldEnum(ETwitchSubscriptionTier, Tier, Json, "tier");
	}
};
