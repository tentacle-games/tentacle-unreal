// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tentacle/Utilities/Json.h"
#include "CustomEvent.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UCustomEvent : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle|Custom Events")
	FName
	Name;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle|Custom Events")
	class UViewer*
	Viewer = nullptr;

	void
	SetFromJson(const FJsonObjectPtr& Json);
};
