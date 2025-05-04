// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomControlComponent.h"
#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent_WithValue.h"
#include "CustomControlComponent_WithStringValue.generated.h"

UCLASS(Abstract, Blueprintable)
class TENTACLE_API UCustomControlComponent_WithStringValue : public UCustomControlComponent, public ICustomControlComponent_WithValue
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValueChangedFromWeb, const FString&, NewValue, const FString&, OldValue);

	friend class UTentacleSubsystem_CustomControls;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom Control")
	FString
	_Value;

public:
	UPROPERTY(BlueprintAssignable, Category="Tentacle|Custom Controls")
	FOnValueChangedFromWeb
	OnValueChangedFromWeb;

	UCustomControlComponent_WithStringValue() {}

	virtual void
	HandleValueChangeEvent(const FJsonObjectPtr& Event) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Tentacle|Custom Controls")
	FString
	GetValue() const;

	virtual FString
	GetValue_Implementation() const { return _Value; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Tentacle|Custom Controls")
	void
	SetValue(const FString& NewValue);

	virtual void
	SetValue_Implementation(const FString& NewValue);

protected:
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Tentacle|Custom Controls")
	bool
	ShouldValueChangeFromWeb(const FString& NewValue) const;

	virtual bool
	ShouldValueChangeFromWeb_Implementation(const FString& NewValue) const { return true; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Tentacle|Custom Controls")
	void
	ValueChangedFromWeb(const FString& NewValue);

	virtual void
	ValueChangedFromWeb_Implementation(const FString& NewValue);

	virtual FJsonObjectPtr
	ToJson() const override;
};
