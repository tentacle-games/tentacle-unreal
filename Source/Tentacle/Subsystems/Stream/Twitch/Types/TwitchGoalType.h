#pragma once

#include "TwitchGoalType.generated.h"

UENUM(BlueprintType)
enum class ETwitchGoalType : uint8
{
	Follow,
	Subscription,
	SubscriptionCount,
	NewSubscription,
	NewSubscriptionCount,
	Unknown,
};

struct TENTACLE_API FETwitchGoalType
{
	static ETwitchGoalType ToEnum(const FName& Value)
	{
		static TMap<FName, ETwitchGoalType> Map = {
			{TEXT("follow"), ETwitchGoalType::Follow},
			{TEXT("subscription"), ETwitchGoalType::Subscription},
			{TEXT("subscription_count"), ETwitchGoalType::SubscriptionCount},
			{TEXT("new_subscription"), ETwitchGoalType::NewSubscription},
			{TEXT("new_subscription_count"), ETwitchGoalType::NewSubscriptionCount},
		};

		const auto FindResult = Map.Find(Value);
		return FindResult != nullptr ? *FindResult : ETwitchGoalType::Unknown;
	}
};
