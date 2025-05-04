// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StreamerController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TENTACLE_API AStreamerController : public APlayerController
{
	GENERATED_BODY()

public:
	AStreamerController();
};
