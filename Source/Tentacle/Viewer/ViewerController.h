// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ViewerController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TENTACLE_API AViewerController : public AAIController
{
	GENERATED_BODY()

public:
	AViewerController();

	UFUNCTION(BlueprintPure, Category="Viewer")
	class UViewer*
	GetViewer() const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	class AViewerPawn*
	GetViewerPawn() const;
};
