// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "TentacleSubsystem_CustomEvents.generated.h"

UCLASS()
class TENTACLE_API UTentacleSubsystem_CustomEvents : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEvent, const UCustomEvent*, Event, AViewerPawn*, InstigatedBy);

public:
	UPROPERTY(BlueprintAssignable, Category="Tentacle")
	FOnEvent
	OnEvent;

	void
	HandleMsg_Event(const class UTentacleMsgIn* Msg);
};
