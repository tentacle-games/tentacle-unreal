// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TentacleSubsystem_Stream.generated.h"

UCLASS()
class TENTACLE_API UTentacleSubsystem_Stream : public UObject
{
	GENERATED_BODY()

	friend class UTentacleTestUtils;

	// General events.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChatCommand, const UStreamChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatJoin, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChatMessage, const UStreamChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChatMessageWithEmojis, const UStreamChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChatMessageWithEmotes, const UStreamChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEvent, const UStreamEvent*, Event, AViewerPawn*, InstigatedBy);

	// Kick events.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_ChatCommand, const UKickChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKick_ChatJoin, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_ChatMessage, const UKickChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_ChatMessageWithEmojis, const UKickChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_ChatMessageWithEmotes, const UKickChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_ChannelFollowed, const UKickEvent_ChannelFollowed*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_ChannelSubscriptionGifts, const UKickEvent_ChannelSubscriptionGifts*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_ChannelSubscriptionNew, const UKickEvent_ChannelSubscriptionNew*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_ChannelSubscriptionRenewal, const UKickEvent_ChannelSubscriptionRenewal*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKick_LivestreamStatusUpdated, const UKickEvent_LivestreamStatusUpdated*, Event, AViewerPawn*, InstigatedBy);

	// Twitch events.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_ChatCommand, const UTwitchChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTwitch_ChatJoin, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_ChatMessage, const UTwitchChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_ChatMessageWithEmojis, const UTwitchChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_ChatMessageWithEmotes, const UTwitchChatMessage*, ChatMessage, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_Cheer, const UTwitchEvent_Cheer*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_Follow, const UTwitchEvent_Follow*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_Raid, const UTwitchEvent_Raid*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTwitch_RaidEnded);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_RedemptionAdd, const UTwitchEvent_RedemptionAdd*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_Subscription, const UTwitchEvent_Subscription*, Event, AViewerPawn*, InstigatedBy);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwitch_SubscriptionGift, const UTwitchEvent_SubscriptionGift*, Event, AViewerPawn*, InstigatedBy);

protected:
	bool
	bIsRaidOngoing;

	TSet<FString>
	HandledChatMsgIds;

	TQueue<FString>
	HandledChatMsgIdRemovalQueue;

	TSet<FString>
	HandledEventIds;

	TQueue<FString>
	HandledEventIdRemovalQueue;

public:
	//
	// General
	//
	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnChatCommand
	OnChatCommand;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnChatJoin
	OnChatJoin;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnChatMessage
	OnChatMessage;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnChatMessageWithEmojis
	OnChatMessageWithEmojis;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnChatMessageWithEmotes
	OnChatMessageWithEmotes;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnEvent
	OnEvent;

	//
	// Kick
	//
	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChatCommand
	OnKick_ChatCommand;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChatJoin
	OnKick_ChatJoin;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChatMessage
	OnKick_ChatMessage;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChatMessageWithEmojis
	OnKick_ChatMessageWithEmojis;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChatMessageWithEmotes
	OnKick_ChatMessageWithEmotes;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChannelFollowed
	OnKick_ChannelFollowed;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChannelSubscriptionRenewal
	OnKick_ChannelSubscriptionRenewal;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChannelSubscriptionGifts
	OnKick_ChannelSubscriptionGifts;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_ChannelSubscriptionNew
	OnKick_ChannelSubscriptionNew;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnKick_LivestreamStatusUpdated
	OnKick_LivestreamStatusUpdated;

	//
	// Twitch
	//
	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_ChatCommand
	OnTwitch_ChatCommand;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_ChatJoin
	OnTwitch_ChatJoin;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_ChatMessage
	OnTwitch_ChatMessage;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_ChatMessageWithEmojis
	OnTwitch_ChatMessageWithEmojis;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_ChatMessageWithEmotes
	OnTwitch_ChatMessageWithEmotes;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_Cheer
	OnTwitch_Cheer;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_Follow
	OnTwitch_Follow;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_Raid
	OnTwitch_Raid;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_RedemptionAdd
	OnTwitch_RedemptionAdd;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_RaidEnded
	OnTwitch_RaidEnded;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_Subscription
	OnTwitch_Subscription;

	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnTwitch_SubscriptionGift
	OnTwitch_SubscriptionGift;

	UTentacleSubsystem_Stream();

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	bool
	IsRaidOngoing() const { return bIsRaidOngoing; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Tentacle")
	void
	EndRaid();

	void
	HandleMsg_ChatJoin(const class UTentacleMsgIn* Msg);

	void
	HandleMsg_ChatMessage(const class UTentacleMsgIn* Msg);

private:
	void
	HandleMsg_ChatMessage_Kick(const UTentacleMsgIn* Msg);

	void
	HandleMsg_ChatMessage_Twitch(const UTentacleMsgIn* Msg);

public:
	void
	HandleMsg_Event(const UTentacleMsgIn* Msg);

private:
	void
	HandleMsg_Event_Kick(const UTentacleMsgIn* Msg);

	void
	HandleMsg_Event_Twitch(const UTentacleMsgIn* Msg);

	void
	AddHandledChatMsgId(const FString& ChatMsgId);

	void
	AddHandledEventId(const FString& EventId);

	void
	BroadcastPlatformChatMessageEvents(const class UStreamChatMessage* ChatMessage, AViewerPawn* InstigatedBy);

	bool
	IsEventAlreadyHandled(const FString& EventId) const;

	bool
	IsChatMessageAlreadyHandled(const FString& ChatMsgId) const;

	class AViewerPawn*
	UpsertViewer(const UTentacleMsgIn* Msg) const;
};
