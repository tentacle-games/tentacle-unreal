// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "KickBadgeType.generated.h"

UENUM()
enum class EKickBadgeType : uint8
{
	Broadcaster,
	Founder,
	Moderator,
	Og,
	Sidekick,
	Staff,
	SubGifter,
	SubGifter100,
	SubGifter200,
	SubGifter25,
	SubGifter50,
	Subscriber,
	Trainwreckstv,
	Verified,
	Vip,
	Unknown,
};

struct TENTACLE_API FEKickBadgeType
{
	using EnumType = EKickBadgeType;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{TEXT("broadcaster"), EnumType::Broadcaster},
			{TEXT("founder"), EnumType::Founder},
			{TEXT("moderator"), EnumType::Moderator},
			{TEXT("og"), EnumType::Og},
			{TEXT("sidekick"), EnumType::Sidekick},
			{TEXT("staff"), EnumType::Staff},
			{TEXT("sub_gifter"), EnumType::SubGifter},
			{TEXT("sub_gifter100"), EnumType::SubGifter100},
			{TEXT("sub_gifter200"), EnumType::SubGifter200},
			{TEXT("sub_gifter25"), EnumType::SubGifter25},
			{TEXT("sub_gifter50"), EnumType::SubGifter50},
			{TEXT("subscriber"), EnumType::Subscriber},
			{TEXT("trainwreckstv"), EnumType::Trainwreckstv},
			{TEXT("verified"), EnumType::Verified},
			{TEXT("vip"), EnumType::Vip},
		};
		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EnumType::Unknown;
	}
};
