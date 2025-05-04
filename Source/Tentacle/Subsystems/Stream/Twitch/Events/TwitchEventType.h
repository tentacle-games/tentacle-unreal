// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchEventType.generated.h"

UENUM(BlueprintType)
enum class ETwitchEventType : uint8
{
	ChannelBan,
	ChannelCheer,
	ChannelFollow,
	ChannelGoalBegin,
	ChannelGoalEnd,
	ChannelGoalProgress,
	ChannelHypeTrainBegin,
	ChannelHypeTrainEnd,
	ChannelHypeTrainProgress,
	ChannelPollBegin,
	ChannelPollEnd,
	ChannelPollProgress,
	ChannelRaid,
	ChannelChannelPointsCustomRewardRedemptionAdd,
	ChannelShieldModeBegin,
	ChannelShieldModeEnd,
	ChannelShoutoutCreate,
	ChannelShoutoutReceive,
	ChannelSubscribe,
	ChannelSubscriptionGift,
	ChannelSubscriptionMessage,
	ChannelUnban,
	Unknown,
};

struct TENTACLE_API FETwitchEventType
{
	using EnumType = ETwitchEventType;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{TEXT("channel.ban"), EnumType::ChannelBan},
			{TEXT("channel.cheer"), EnumType::ChannelCheer},
			{TEXT("channel.follow"), EnumType::ChannelFollow},
			{TEXT("channel.goal.begin"), EnumType::ChannelGoalBegin},
			{TEXT("channel.goal.end"), EnumType::ChannelGoalEnd},
			{TEXT("channel.goal.progress"), EnumType::ChannelGoalProgress},
			{TEXT("channel.hype_train.begin"), EnumType::ChannelHypeTrainBegin},
			{TEXT("channel.hype_train.end"), EnumType::ChannelHypeTrainEnd},
			{TEXT("channel.hype_train.progress"), EnumType::ChannelHypeTrainProgress},
			{TEXT("channel.poll.begin"), EnumType::ChannelPollBegin},
			{TEXT("channel.poll.end"), EnumType::ChannelPollEnd},
			{TEXT("channel.poll.progress"), EnumType::ChannelPollProgress},
			{TEXT("channel.raid"), EnumType::ChannelRaid},
			{TEXT("channel.channel_points_custom_reward_redemption.add"), EnumType::ChannelChannelPointsCustomRewardRedemptionAdd},
			{TEXT("channel.shield_mode.begin"), EnumType::ChannelShieldModeBegin},
			{TEXT("channel.shield_mode.end"), EnumType::ChannelShieldModeEnd},
			{TEXT("channel.shoutout.create"), EnumType::ChannelShoutoutCreate},
			{TEXT("channel.shoutout.receive"), EnumType::ChannelShoutoutReceive},
			{TEXT("channel.subscribe"), EnumType::ChannelSubscribe},
			{TEXT("channel.subscription.gift"), EnumType::ChannelSubscriptionGift},
			{TEXT("channel.subscription.message"), EnumType::ChannelSubscriptionMessage},
			{TEXT("channel.unban"), EnumType::ChannelUnban},
		};
		const EnumType* FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EnumType::Unknown;
	}
};
