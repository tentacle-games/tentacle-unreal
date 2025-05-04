// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/CustomControlComponent.h"
#include "CustomControlComponent_Button.generated.h"

UCLASS(Blueprintable, ClassGroup="Tentacle", DisplayName="Custom Control Button", meta=(BlueprintSpawnableComponent))
class TENTACLE_API UCustomControlComponent_Button : public UCustomControlComponent
{
	GENERATED_BODY()

	friend class UTentacleSubsystem_CustomControls;

public:
	static const inline auto StaticType = FName("Button");

	UCustomControlComponent_Button();
};
