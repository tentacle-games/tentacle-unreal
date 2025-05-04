// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/CustomControlComponent_WithIntValue.h"
#include "CustomControlComponent_Slider.generated.h"

UCLASS(Blueprintable, ClassGroup="Tentacle", DisplayName="Custom Control Slider", meta=(BlueprintSpawnableComponent))
class TENTACLE_API UCustomControlComponent_Slider : public UCustomControlComponent_WithIntValue
{
	GENERATED_BODY()

	friend class UTentacleSubsystem_CustomControls;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom Control")
	int64
	Min;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom Control")
	int64
	Max;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom Control")
	int64
	Step;

public:
	static const inline auto StaticType = FName("Slider");

	UCustomControlComponent_Slider();
};
