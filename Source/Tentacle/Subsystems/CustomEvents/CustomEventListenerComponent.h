// (c) 2024 Deadsun & Backside4Charter. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tentacle/Subsystems/CustomEvents/CustomEvent.h"
#include "Tentacle/Viewer/ViewerPawn.h"
#include "CustomEventListenerComponent.generated.h"

UCLASS(ClassGroup="Tentacle", DisplayName="Custom Event Listener", meta=(BlueprintSpawnableComponent))
class TENTACLE_API UCustomEventListenerComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTriggered, const UCustomEvent*, Event, AViewerPawn*, ViewerPawn);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom Events")
	FName
	CustomEventName;

	UPROPERTY(BlueprintAssignable, Category="Custom Events")
	FOnTriggered
	OnTriggered;

	UCustomEventListenerComponent();

protected:
	virtual void
	BeginPlay() override;

	virtual void
	EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void
	HandleEvent(const UCustomEvent* CustomEvent, AViewerPawn* ViewerPawn);
};
