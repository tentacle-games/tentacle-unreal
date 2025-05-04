// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ViewerPawn.generated.h"

class UViewer;

UCLASS(Blueprintable)
class TENTACLE_API AViewerPawn : public APawn
{
	GENERATED_BODY()

public:
	AViewerPawn();

	UFUNCTION(BlueprintPure, Category="Viewer Pawn")
	UViewer*
	GetViewer() const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	FString
	GetDisplayName() const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	FLinearColor
	GetColor() const;

	UFUNCTION(BlueprintPure, Category="Viewer Pawn")
	bool
	IsStreamer() const;
};
