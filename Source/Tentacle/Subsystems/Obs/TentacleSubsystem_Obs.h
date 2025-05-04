// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TentacleSubsystem_Obs.generated.h"

UCLASS()
class TENTACLE_API UTentacleSubsystem_Obs : public UObject
{
	GENERATED_BODY()

public:
	void
	SetSourceFilterEnabled(const FString& SourceName, const FString& FilterName, bool bEnabled) const;
};
