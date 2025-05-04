// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/CustomControlComponent_WithStringValue.h"
#include "CustomControlComponent_Select.generated.h"

UCLASS(Blueprintable, ClassGroup="Tentacle", DisplayName="Custom Control Select", meta=(BlueprintSpawnableComponent))
class TENTACLE_API UCustomControlComponent_Select : public UCustomControlComponent_WithStringValue
{
	GENERATED_BODY()

	friend class UTentacleSubsystem_CustomControls;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom Control")
	FString
	Placeholder;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom Control")
	TArray<FString>
	Options;

public:
	static const inline auto StaticType = FName("Select");

	UCustomControlComponent_Select();

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Custom Control")
	FString
	GetPlaceholder() const;

	virtual FString
	GetPlaceholder_Implementation() const { return Placeholder; }

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Custom Control")
	TArray<FString>
	GetOptions() const;

	virtual TArray<FString>
	GetOptions_Implementation() const { return Options; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	SetOptions(const TArray<FString>& NewOptions);

	virtual void
	SetOptions_Implementation(const TArray<FString>& NewOptions);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	SetOptionsFromNames(const TArray<FName>& NewOptions);

	virtual void
	SetOptionsFromNames_Implementation(const TArray<FName>& NewOptions);

protected:
	virtual FJsonObjectPtr
	ToJson() const override;
};
