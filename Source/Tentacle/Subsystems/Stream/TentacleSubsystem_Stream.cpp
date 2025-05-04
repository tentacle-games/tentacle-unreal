// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleSubsystem_Stream.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Subsystems/Stream/Kick/ChatMessage/KickChatMessage.h"
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEventType.h"
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent_ChannelFollowed.h"
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent_ChannelSubscriptionGifts.h"
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent_ChannelSubscriptionNew.h"
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent_ChannelSubscriptionRenewal.h"
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent_LivestreamStatusUpdated.h"
#include "Tentacle/Subsystems/Stream/Twitch/ChatMessage/TwitchChatMessage.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEventType.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent_Cheer.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent_Follow.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent_Raid.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent_RedemptionAdd.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent_Subscription.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent_SubscriptionGift.h"
#include "Tentacle/TentacleMsg/In/TentacleMsgIn.h"
#include "Tentacle/Viewer/Viewer.h"

UTentacleSubsystem_Stream::UTentacleSubsystem_Stream()
{
	bIsRaidOngoing = false;
}

void
UTentacleSubsystem_Stream::EndRaid_Implementation()
{
	bIsRaidOngoing = false;
	OnTwitch_RaidEnded.Broadcast();
}

void
UTentacleSubsystem_Stream::HandleMsg_ChatJoin(const UTentacleMsgIn* Msg)
{
	// Do nothing for now.
}

void
UTentacleSubsystem_Stream::HandleMsg_ChatMessage(const UTentacleMsgIn* Msg)
{
	// Get the platform from the data.
	auto Platform = EStreamPlatform::Unknown;
	jsonFieldEnum(EStreamPlatform, Platform, Msg->Data, "chatMessage", "$platform");

	switch (Platform)
	{
	case EStreamPlatform::Kick:
		HandleMsg_ChatMessage_Kick(Msg);
		break;
	case EStreamPlatform::Twitch:
		HandleMsg_ChatMessage_Twitch(Msg);
		break;
	}
}

void
UTentacleSubsystem_Stream::HandleMsg_ChatMessage_Kick(const UTentacleMsgIn* Msg)
{
	FJsonObjectPtr ChatMessageJson;
	jsonField(FJsonObjectPtr, ChatMessageJson, Msg->Data, "chatMessage");

	const auto ChatMessage = NewObject<UKickChatMessage>();
	ChatMessage->SetFromJson(ChatMessageJson);

	if (IsChatMessageAlreadyHandled(ChatMessage->Id))
		return;

	const auto InstigatedBy = UpsertViewer(Msg);

	// Broadcast events.
	if (ChatMessage->Command.Name != NAME_None)
		OnKick_ChatCommand.Broadcast(ChatMessage, InstigatedBy);
	else
		OnKick_ChatMessage.Broadcast(ChatMessage, InstigatedBy);

	if (!ChatMessage->Emojis.IsEmpty())
		OnKick_ChatMessageWithEmojis.Broadcast(ChatMessage, InstigatedBy);

	if (!ChatMessage->Emotes.IsEmpty())
		OnKick_ChatMessageWithEmotes.Broadcast(ChatMessage, InstigatedBy);

	BroadcastPlatformChatMessageEvents(ChatMessage, InstigatedBy);
}

void
UTentacleSubsystem_Stream::HandleMsg_ChatMessage_Twitch(const UTentacleMsgIn* Msg)
{
	FJsonObjectPtr ChatMessageJson;
	jsonField(FJsonObjectPtr, ChatMessageJson, Msg->Data, "chatMessage");

	const auto ChatMessage = NewObject<UTwitchChatMessage>();
	ChatMessage->SetFromJson(ChatMessageJson);

	if (IsChatMessageAlreadyHandled(ChatMessage->Id))
		return;

	const auto InstigatedBy = UpsertViewer(Msg);

	// Broadcast events.
	if (ChatMessage->Command.Name != NAME_None)
		OnTwitch_ChatCommand.Broadcast(ChatMessage, InstigatedBy);
	else
		OnTwitch_ChatMessage.Broadcast(ChatMessage, InstigatedBy);

	if (!ChatMessage->Emojis.IsEmpty())
		OnTwitch_ChatMessageWithEmojis.Broadcast(ChatMessage, InstigatedBy);

	if (!ChatMessage->Emotes.IsEmpty())
		OnTwitch_ChatMessageWithEmotes.Broadcast(ChatMessage, InstigatedBy);

	BroadcastPlatformChatMessageEvents(ChatMessage, InstigatedBy);
}

void
UTentacleSubsystem_Stream::HandleMsg_Event(const UTentacleMsgIn* Msg)
{
	// Get the platform from the data.
	auto Platform = EStreamPlatform::Unknown;
	jsonFieldEnum(EStreamPlatform, Platform, Msg->Data, "$platform");

	switch (Platform)
	{
	case EStreamPlatform::Kick:
		return HandleMsg_Event_Kick(Msg);
	case EStreamPlatform::Twitch:
		return HandleMsg_Event_Twitch(Msg);
	}
}

void
UTentacleSubsystem_Stream::HandleMsg_Event_Kick(const UTentacleMsgIn* Msg)
{
	FJsonObjectPtr EventJson;
	jsonField(FJsonObjectPtr, EventJson, Msg->Data, "event");

	// Get the event type from the data.
	auto EventType = EKickEventType::Unknown;
	jsonFieldEnum(EKickEventType, EventType, EventJson, "$type");

	const auto InstigatedBy = UpsertViewer(Msg);

	const UStreamEvent* PlatformEvent = nullptr;
	switch (EventType)
	{
	case EKickEventType::ChannelFollowed: {
		const auto KickEvent = NewObject<UKickEvent_ChannelFollowed>();
		KickEvent->SetFromJson(EventJson);
		OnKick_ChannelFollowed.Broadcast(KickEvent, InstigatedBy);
		PlatformEvent = KickEvent;
		break;
	}
	case EKickEventType::ChannelSubscriptionGifts: {
		const auto KickEvent = NewObject<UKickEvent_ChannelSubscriptionGifts>();
		KickEvent->SetFromJson(EventJson);
		OnKick_ChannelSubscriptionGifts.Broadcast(KickEvent, InstigatedBy);
		PlatformEvent = KickEvent;
		break;
	}
	case EKickEventType::ChannelSubscriptionNew: {
		const auto KickEvent = NewObject<UKickEvent_ChannelSubscriptionNew>();
		KickEvent->SetFromJson(EventJson);
		OnKick_ChannelSubscriptionNew.Broadcast(KickEvent, InstigatedBy);
		PlatformEvent = KickEvent;
		break;
	}
	case EKickEventType::ChannelSubscriptionRenewal: {
		const auto KickEvent = NewObject<UKickEvent_ChannelSubscriptionRenewal>();
		KickEvent->SetFromJson(EventJson);
		OnKick_ChannelSubscriptionRenewal.Broadcast(KickEvent, InstigatedBy);
		PlatformEvent = KickEvent;
		break;
	}
	case EKickEventType::LivestreamStatusUpdated: {
		const auto KickEvent = NewObject<UKickEvent_LivestreamStatusUpdated>();
		KickEvent->SetFromJson(EventJson);
		OnKick_LivestreamStatusUpdated.Broadcast(KickEvent, InstigatedBy);
		PlatformEvent = KickEvent;
		break;
	}
	}

	if (IsValid(PlatformEvent))
		OnEvent.Broadcast(PlatformEvent, InstigatedBy);
}

void
UTentacleSubsystem_Stream::HandleMsg_Event_Twitch(const UTentacleMsgIn* Msg)
{
	// Get the event type from the data.
	auto EventType = ETwitchEventType::Unknown;
	jsonFieldEnum(ETwitchEventType, EventType, Msg->Data, "event", "$type");

	const auto InstigatedBy = UpsertViewer(Msg);

	const UStreamEvent* PlatformEvent = nullptr;
	switch (EventType)
	{
	case ETwitchEventType::ChannelCheer: {
		const auto TwitchEvent = NewObject<UTwitchEvent_Cheer>();
		TwitchEvent->SetFromJson(Msg->Data);
		OnTwitch_Cheer.Broadcast(TwitchEvent, InstigatedBy);
		PlatformEvent = TwitchEvent;
		break;
	}
	case ETwitchEventType::ChannelFollow: {
		const auto TwitchEvent = NewObject<UTwitchEvent_Follow>();
		TwitchEvent->SetFromJson(Msg->Data);
		OnTwitch_Follow.Broadcast(TwitchEvent, InstigatedBy);
		PlatformEvent = TwitchEvent;
		break;
	}
	case ETwitchEventType::ChannelRaid: {
		bIsRaidOngoing = true;
		const auto TwitchEvent = NewObject<UTwitchEvent_Raid>();
		TwitchEvent->SetFromJson(Msg->Data);
		OnTwitch_Raid.Broadcast(TwitchEvent, InstigatedBy);
		PlatformEvent = TwitchEvent;
		break;
	}
	case ETwitchEventType::ChannelChannelPointsCustomRewardRedemptionAdd: {
		const auto TwitchEvent = NewObject<UTwitchEvent_RedemptionAdd>();
		TwitchEvent->SetFromJson(Msg->Data);
		OnTwitch_RedemptionAdd.Broadcast(TwitchEvent, InstigatedBy);
		PlatformEvent = TwitchEvent;
		break;
	}
	case ETwitchEventType::ChannelSubscribe: {
		const auto TwitchEvent = NewObject<UTwitchEvent_Subscription>();
		TwitchEvent->SetFromJson(Msg->Data);
		OnTwitch_Subscription.Broadcast(TwitchEvent, InstigatedBy);
		PlatformEvent = TwitchEvent;
		break;
	}
	case ETwitchEventType::ChannelSubscriptionGift: {
		const auto TwitchEvent = NewObject<UTwitchEvent_SubscriptionGift>();
		TwitchEvent->SetFromJson(Msg->Data);
		OnTwitch_SubscriptionGift.Broadcast(TwitchEvent, InstigatedBy);
		PlatformEvent = TwitchEvent;
		break;
	}
	default: {
		// Unhandled event.
		const auto Tentacle = ATentacle::Get(this);
		softAssertValid(Tentacle);
		if (Tentacle->bDebugLog)
			warnF("Unhandled Twitch event: %s", *UEnum::GetValueAsString(EventType));
	}
	}

	if (IsValid(PlatformEvent))
		OnEvent.Broadcast(PlatformEvent, InstigatedBy);
}

void
UTentacleSubsystem_Stream::AddHandledChatMsgId(const FString& ChatMsgId)
{
	HandledChatMsgIds.Add(ChatMsgId);
	HandledChatMsgIdRemovalQueue.Enqueue(ChatMsgId);

	if (HandledChatMsgIds.Num() > 100)
	{
		FString OldestChatMsgId;
		HandledChatMsgIdRemovalQueue.Dequeue(OldestChatMsgId);
		HandledChatMsgIds.Remove(OldestChatMsgId);
	}
}

void
UTentacleSubsystem_Stream::AddHandledEventId(const FString& EventId)
{
	HandledEventIds.Add(EventId);
	HandledEventIdRemovalQueue.Enqueue(EventId);

	if (HandledEventIds.Num() > 100)
	{
		FString OldestEventId;
		HandledEventIdRemovalQueue.Dequeue(OldestEventId);
		HandledEventIds.Remove(OldestEventId);
	}
}

void
UTentacleSubsystem_Stream::BroadcastPlatformChatMessageEvents(const class UStreamChatMessage* ChatMessage, AViewerPawn* InstigatedBy)
{
	if (ChatMessage->Command.Name != NAME_None)
		OnChatCommand.Broadcast(ChatMessage, InstigatedBy);
	else
		OnChatMessage.Broadcast(ChatMessage, InstigatedBy);

	if (!ChatMessage->Emojis.IsEmpty())
		OnChatMessageWithEmojis.Broadcast(ChatMessage, InstigatedBy);

	if (!ChatMessage->Emotes.IsEmpty())
		OnChatMessageWithEmotes.Broadcast(ChatMessage, InstigatedBy);
}

bool
UTentacleSubsystem_Stream::IsEventAlreadyHandled(const FString& EventId) const
{
	return HandledEventIds.Contains(EventId);
}

bool
UTentacleSubsystem_Stream::IsChatMessageAlreadyHandled(const FString& ChatMsgId) const
{
	return HandledChatMsgIds.Contains(ChatMsgId);
}

AViewerPawn*
UTentacleSubsystem_Stream::UpsertViewer(const UTentacleMsgIn* Msg) const
{
	// Get the viewer and upsert it if it exists.
	auto ViewerJson = FJsonObjectPtr();
	jsonFieldOptional(FJsonObjectPtr, ViewerJson, Msg->Data, "viewer");
	if (!ViewerJson.IsValid())
		return {};

	const auto Viewer = NewObject<UViewer>();
	Viewer->SetFromJson(ViewerJson);

	const auto Tentacle = ATentacle::Get(this);
	softAssertValidR(Tentacle, {});
	return Tentacle->UpsertViewer(Viewer).Get<1>();
}
