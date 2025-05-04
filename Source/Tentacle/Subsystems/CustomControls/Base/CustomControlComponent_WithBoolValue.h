// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomControlComponent.h"
#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent_WithValue.h"
#include "CustomControlComponent_WithBoolValue.generated.h"

UCLASS(Abstract, Blueprintable)
class TENTACLE_API UCustomControlComponent_WithBoolValue : public UCustomControlComponent, public ICustomControlComponent_WithValue
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValueChangedFromWeb, bool, NewValue, bool, OldValue);

	friend class UTentacleSubsystem_CustomControls;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom Control")
	bool
	_Value;

public:
	UPROPERTY(BlueprintAssignable, Category="Custom Control")
	FOnValueChangedFromWeb
	OnValueChangedFromWeb;

	UCustomControlComponent_WithBoolValue() { _Value = false; }

	virtual void
	HandleValueChangeEvent(const FJsonObjectPtr& Event) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Custom Control")
	bool
	GetValue() const;

	virtual bool
	GetValue_Implementation() const { return _Value; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	SetValue(bool NewValue);

	virtual void
	SetValue_Implementation(bool NewValue);

protected:
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Custom Control")
	bool
	ShouldValueChangeFromWeb(bool NewValue) const;

	virtual bool
	ShouldValueChangeFromWeb_Implementation(bool NewValue) const { return true; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	ValueChangedFromWeb(bool NewValue);

	virtual void
	ValueChangedFromWeb_Implementation(bool NewValue);

	virtual FJsonObjectPtr
	ToJson() const override;
};
