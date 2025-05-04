// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEvent.h"
#include "KickEvent_LivestreamStatusUpdated.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UKickEvent_LivestreamStatusUpdated : public UKickEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	bool
	IsLive = false;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Title;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FDateTime
	StartedAt;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FDateTime
	EndedAt;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		jsonField(bool, IsLive, Json, "is_live");
		jsonField(FString, Title, Json, "title");
		jsonField(FDateTime, StartedAt, Json, "started_at");
		jsonField(FDateTime, EndedAt, Json, "ended_at");
	}
};
