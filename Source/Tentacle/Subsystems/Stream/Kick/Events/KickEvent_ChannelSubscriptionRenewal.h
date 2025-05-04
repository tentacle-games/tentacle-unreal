// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent.h"
#include "Tentacle/Subsystems/Stream/Kick/Types/KickUser.h"
#include "KickEvent_ChannelSubscriptionRenewal.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UKickEvent_ChannelSubscriptionRenewal : public UKickEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FKickUser
	Subscriber;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	Duration = 0;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		FJsonObjectPtr SubscriberJson;
		jsonField(FJsonObjectPtr, SubscriberJson, Json, "subscriber");
		Subscriber.SetFromJson(SubscriberJson);

		jsonField(int32, Duration, Json, "duration");
	}
};
