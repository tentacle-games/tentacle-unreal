// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tentacle/Utilities/Json.h"
#include "CustomControlComponent.generated.h"

using FCustomControlComponentId = FName;

UCLASS(Abstract, Blueprintable)
class TENTACLE_API UCustomControlComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitialize);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClick);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseDown);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseUp);

	friend class UTentacleSubsystem_CustomControls;

protected:
	FCustomControlComponentId
	Id;

	FName
	Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom Control")
	FString
	_Label;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom Control")
	FString
	Group;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom Control")
	int32
	SortPriority;

public:
	UPROPERTY(BlueprintAssignable, Category="Custom Control")
	FOnInitialize
	OnInitialize;

	UPROPERTY(BlueprintAssignable, Category="Custom Control")
	FOnClick
	OnClick;

	UPROPERTY(BlueprintAssignable, Category="Custom Control")
	FOnMouseDown
	OnMouseDown;

	UPROPERTY(BlueprintAssignable, Category="Custom Control")
	FOnMouseUp
	OnMouseUp;

	UCustomControlComponent();

	virtual void
	BeginPlay() override;

	virtual void
	EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	Initialize();

	virtual void
	Initialize_Implementation() { OnInitialize.Broadcast(); }

	void
	SendControlState();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	ReceiveClick();

	virtual void
	ReceiveClick_Implementation() { OnClick.Broadcast(); }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	ReceiveMouseDown();

	virtual void
	ReceiveMouseDown_Implementation() { OnMouseDown.Broadcast(); }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Custom Control")
	void
	ReceiveMouseUp();

	virtual void
	ReceiveMouseUp_Implementation() { OnMouseUp.Broadcast(); }

public:
	FName
	GetId() const { return Id; }

	FName
	GetType() const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Custom Control")
	FString
	GetLabel() const;

	virtual FString
	GetLabel_Implementation() const { return _Label; }

	virtual FJsonObjectPtr
	ToJson() const;
};
