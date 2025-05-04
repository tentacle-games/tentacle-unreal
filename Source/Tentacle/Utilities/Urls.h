// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Urls.generated.h"

UENUM()
enum class ETclEnvironment : uint8
{
	Local,
	LiveDevelopment,
	LiveProduction,
};

USTRUCT()
struct TENTACLE_API FTclHosts
{
	GENERATED_BODY()

	static inline FString
	Local = TEXT("localhost");

	static inline FString
	LiveDevelopment = TEXT("tentacle-dev.up.railway.app");

	static inline FString
	LiveProduction = TEXT("tentacle.up.railway.app");
};

USTRUCT()
struct TENTACLE_API FTclUrls
{
	GENERATED_BODY()

	static FString
	Api();

	static FString
	LogService();
};
