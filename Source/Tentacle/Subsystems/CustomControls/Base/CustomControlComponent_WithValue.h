// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomControlComponent_WithValue.generated.h"

UINTERFACE()
class UCustomControlComponent_WithValue : public UInterface
{
	GENERATED_BODY()
};

class ICustomControlComponent_WithValue
{
	GENERATED_BODY()

public:
	virtual void
	HandleValueChangeEvent(const FJsonObjectPtr& Event) = 0;
};
