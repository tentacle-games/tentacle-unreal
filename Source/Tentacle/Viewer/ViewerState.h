// © 2023 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ViewerState.generated.h"

class UViewer;

UCLASS(BlueprintType)
class TENTACLE_API AViewerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player State|Viewer")
	UViewer* Viewer;

	AViewerState();

	UFUNCTION(BlueprintPure, Category="Player State|Viewer")
	FName GetUserId() const;

	UFUNCTION(BlueprintPure, Category="Player State|Viewer")
	FString GetDisplayName() const;

	UFUNCTION(BlueprintPure, Category="Player State|Viewer")
	FLinearColor GetColor() const;
};
