// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "KickEventType.generated.h"

UENUM(BlueprintType)
enum class EKickEventType : uint8
{
	ChannelFollowed,
	ChannelSubscriptionRenewal,
	ChannelSubscriptionGifts,
	ChannelSubscriptionNew,
	LivestreamStatusUpdated,
	Unknown,
};

struct TENTACLE_API FEKickEventType
{
	using EnumType = EKickEventType;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{TEXT("channel.followed"), EnumType::ChannelFollowed},
			{TEXT("channel.subscription.renewal"), EnumType::ChannelSubscriptionRenewal},
			{TEXT("channel.subscription.gifts"), EnumType::ChannelSubscriptionGifts},
			{TEXT("channel.subscription.new"), EnumType::ChannelSubscriptionNew},
			{TEXT("livestream.status.updated"), EnumType::LivestreamStatusUpdated},
		};
		const EnumType* FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EnumType::Unknown;
	}
};
