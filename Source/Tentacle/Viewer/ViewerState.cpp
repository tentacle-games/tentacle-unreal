// © 2023 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Viewer/ViewerState.h"
#include "Tentacle/Utilities/Common.h"
#include "Tentacle/Viewer/Viewer.h"

AViewerState::AViewerState()
{
	PrimaryActorTick.bCanEverTick = true;
	Viewer = nullptr;
}

FName AViewerState::GetUserId() const
{
	softAssertR(IsValid(Viewer), FName())
	return Viewer->Id;
}

FString AViewerState::GetDisplayName() const
{
	softAssertR(IsValid(Viewer), FString())
	return Viewer->Twitch.DisplayName;
}

FLinearColor AViewerState::GetColor() const
{
	softAssertR(IsValid(Viewer), FLinearColor())
	return Viewer->Twitch.Color;
}
