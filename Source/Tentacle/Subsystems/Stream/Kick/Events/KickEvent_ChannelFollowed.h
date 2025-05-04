// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent.h"
#include "Tentacle/Subsystems/Stream/Kick/Types/KickUser.h"
#include "KickEvent_ChannelFollowed.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UKickEvent_ChannelFollowed : public UKickEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FKickUser
	Follower;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		FJsonObjectPtr FollowerJson;
		jsonField(FJsonObjectPtr, FollowerJson, Json, "follower");
		Follower.SetFromJson(FollowerJson);
	}
};
