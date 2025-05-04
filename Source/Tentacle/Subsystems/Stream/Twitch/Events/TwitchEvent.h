// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "Tentacle/Subsystems/Stream/StreamEvent.h"
#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEventType.h"
#include "Tentacle/Utilities/Json.h"
#include "TwitchEvent.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchEvent : public UStreamEvent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	ETwitchEventType
	Type = ETwitchEventType::Unknown;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		jsonFieldEnum(ETwitchEventType, Type, Json, "$type");
	}
};
