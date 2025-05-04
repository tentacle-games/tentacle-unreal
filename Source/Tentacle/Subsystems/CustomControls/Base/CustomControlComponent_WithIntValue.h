// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomControlComponent.h"
#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent_WithValue.h"
#include "CustomControlComponent_WithIntValue.generated.h"

UCLASS(Abstract, Blueprintable)
class TENTACLE_API UCustomControlComponent_WithIntValue : public UCustomControlComponent, public ICustomControlComponent_WithValue
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValueChangedFromWeb, int64, NewValue, int64, OldValue);

	friend class UTentacleSubsystem_CustomControls;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom Control")
	int64
	_Value;

public:
	UPROPERTY(BlueprintAssignable, Category="Custom Control")
	FOnValueChangedFromWeb
	OnValueChangedFromWeb;

	UCustomControlComponent_WithIntValue() { _Value = 0; }

	virtual void
	HandleValueChangeEvent(const FJsonObjectPtr& Event) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Custom Control")
	int64
	GetValue() const;

	virtual int64
	GetValue_Implementation() const { return _Value; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	SetValue(int64 NewValue);

	virtual void
	SetValue_Implementation(int64 NewValue);

protected:
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Custom Control")
	bool
	ShouldValueChangeFromWeb(int64 NewValue) const;

	virtual bool
	ShouldValueChangeFromWeb_Implementation(int64 NewValue) const { return true; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	ValueChangedFromWeb(int64 NewValue);

	virtual void
	ValueChangedFromWeb_Implementation(int64 NewValue);

	virtual FJsonObjectPtr
	ToJson() const override;
};
