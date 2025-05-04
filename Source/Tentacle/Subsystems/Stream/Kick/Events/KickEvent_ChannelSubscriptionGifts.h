// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent.h"
#include "Tentacle/Subsystems/Stream/Kick/Types/KickUser.h"
#include "KickEvent_ChannelSubscriptionGifts.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UKickEvent_ChannelSubscriptionGifts : public UKickEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FKickUser
	Gifter;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TArray<FKickUser>
	Giftees;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		FJsonObjectPtr GifterJson;
		jsonField(FJsonObjectPtr, GifterJson, Json, "gifter");
		Gifter.SetFromJson(GifterJson);

		TArray<FJsonObjectPtr> GifteesJson;
		jsonField(TArray<FJsonObjectPtr>, GifteesJson, Json, "giftees");
		for (const auto& GifteeJson : GifteesJson)
		{
			FKickUser Giftee;
			Giftee.SetFromJson(GifteeJson);
			Giftees.Add(Giftee);
		}
	}
};
