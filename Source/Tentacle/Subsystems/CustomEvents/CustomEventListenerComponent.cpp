// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Subsystems/CustomEvents/CustomEventListenerComponent.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Subsystems/CustomEvents/TentacleSubsystem_CustomEvents.h"
#include "Tentacle/Utilities/Common.h"

UCustomEventListenerComponent::UCustomEventListenerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void
UCustomEventListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto Tentacle = ATentacle::Get(this);
	softAssert(IsValid(Tentacle))
	addDynamicSafe(Tentacle->CustomEvents->OnEvent, UCustomEventListenerComponent::HandleEvent);
}

void
UCustomEventListenerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	const auto Tentacle = ATentacle::Get(this);
	if (IsValid(Tentacle))
		removeDynamicSafe(Tentacle->CustomEvents->OnEvent, UCustomEventListenerComponent::HandleEvent);
}

void
UCustomEventListenerComponent::HandleEvent(const UCustomEvent* CustomEvent, AViewerPawn* ViewerPawn)
{
	if (CustomEvent->Name == CustomEventName)
		OnTriggered.Broadcast(CustomEvent, ViewerPawn);
}
