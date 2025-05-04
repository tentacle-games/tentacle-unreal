// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Viewer/ViewerPawn.h"
#include "Tentacle/Utilities/Common.h"
#include "Tentacle/Viewer/Viewer.h"
#include "Tentacle/Viewer/ViewerState.h"

AViewerPawn::AViewerPawn() {}

UViewer*
AViewerPawn::GetViewer() const
{
	const auto ViewerState = GetPlayerState<AViewerState>();
	softAssertR(IsValid(ViewerState), nullptr)
	return ViewerState->Viewer;
}

FString
AViewerPawn::GetDisplayName() const
{
	const UViewer* Viewer = GetViewer();
	softAssertR(IsValid(Viewer), FString())

	return Viewer->GetDisplayName();
}

FLinearColor
AViewerPawn::GetColor() const
{
	const UViewer* Viewer = GetViewer();
	softAssertR(IsValid(Viewer), FLinearColor())

	return Viewer->GetColor();
}

bool
AViewerPawn::IsStreamer() const
{
	const UViewer* Viewer = GetViewer();
	softAssertR(IsValid(Viewer), false)

	return Viewer->bIsMock;
}
