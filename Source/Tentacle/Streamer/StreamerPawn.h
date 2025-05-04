// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tentacle/Viewer/ViewerKick.h"
#include "Tentacle/Viewer/ViewerPawn.h"
#include "Tentacle/Viewer/ViewerTwitch.h"
#include "StreamerPawn.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TENTACLE_API AStreamerPawn : public AViewerPawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Streamer Pawn")
	FViewerKick
	KickInfo;

	UPROPERTY(EditAnywhere, Category="Streamer Pawn")
	FViewerTwitch
	TwitchInfo;

	AStreamerPawn();

	virtual void BeginPlay() override;
};
