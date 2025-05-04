// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/CustomControlComponent_WithBoolValue.h"
#include "CustomControlComponent_Switch.generated.h"

UCLASS(Blueprintable, ClassGroup="Tentacle", DisplayName="Custom Control Switch", meta=(BlueprintSpawnableComponent))
class TENTACLE_API UCustomControlComponent_Switch : public UCustomControlComponent_WithBoolValue
{
	GENERATED_BODY()

	friend class UTentacleSubsystem_CustomControls;

public:
	static const inline auto StaticType = FName("Switch");

	UCustomControlComponent_Switch();
};
