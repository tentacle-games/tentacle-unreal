// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "Tentacle/Subsystems/Stream/StreamEvent.h"
#include "Tentacle/Subsystems/Stream/Kick/Events/KickEventType.h"
#include "Tentacle/Utilities/Json.h"
#include "KickEvent.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UKickEvent : public UStreamEvent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	EKickEventType
	Type = EKickEventType::Unknown;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		jsonFieldEnum(EKickEventType, Type, Json, "$type");
	}
};
