// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Viewer/ViewerController.h"
#include "Tentacle/Utilities/Common.h"
#include "Tentacle/Viewer/Viewer.h"
#include "Tentacle/Viewer/ViewerState.h"

AViewerController::AViewerController()
{
	bWantsPlayerState = true;
}

UViewer*
AViewerController::GetViewer() const
{
	const AViewerState* ViewerState = GetPlayerState<AViewerState>();
	softAssertR(IsValid(ViewerState), nullptr)
	return ViewerState->Viewer;
}

class AViewerPawn*
AViewerController::GetViewerPawn() const
{
	return GetPawn<AViewerPawn>();
}
