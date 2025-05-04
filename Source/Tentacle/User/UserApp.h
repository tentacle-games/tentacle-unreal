// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UserApp.generated.h"

USTRUCT()
struct TENTACLE_API FUserApp
{
	GENERATED_BODY()

	UPROPERTY()
	FName Id;

	UPROPERTY()
	FString Name;
};
