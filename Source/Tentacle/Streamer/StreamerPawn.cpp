// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#include "Tentacle/Streamer/StreamerPawn.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Viewer/Viewer.h"
#include "Tentacle/Viewer/ViewerState.h"

AStreamerPawn::AStreamerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	KickInfo = FViewerKick();
	TwitchInfo = FViewerTwitch();
}

void AStreamerPawn::BeginPlay()
{
	Super::BeginPlay();

	const auto Tentacle = ATentacle::Get(this);

	// Create a viewer state for the streamer and add it to Tentacle.
	const auto ViewerState = UCommon::SpawnActor<AViewerState>(this);
	ViewerState->Viewer = NewObject<UViewer>();
	ViewerState->Viewer->bIsMock = true;
	ViewerState->Viewer->Id = FName("streamer");
	ViewerState->Viewer->Kick = KickInfo;
	ViewerState->Viewer->Twitch = TwitchInfo;
	SetPlayerState(ViewerState);

	Tentacle->UpsertViewer(ViewerState->Viewer);
}
