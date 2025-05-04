// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tentacle/Utilities/Urls.h"
#include "UObject/Object.h"
#include "TentacleSettings.generated.h"

UCLASS(Config=GameUserSettings, DefaultConfig)
class TENTACLE_API UTentacleSettings : public UObject
{
	GENERATED_BODY()

	UPROPERTY(Config, EditAnywhere, Category="General", DisplayName="Environment (Editor only)")
	ETclEnvironment
	Environment;

public:
	UPROPERTY(Config, EditAnywhere, Category="Authentication")
	FString
	AccessToken;

	UPROPERTY(Config, EditAnywhere, Category="Authentication")
	FString
	DevAccessToken;

	UPROPERTY(Config, EditAnywhere, Category="Tentacle")
	FString
	StreamerTwitchId;

	UPROPERTY(Config, EditAnywhere, Category="Telemetry")
	bool
	bTelemetryEnabled;

	static ETclEnvironment
	GetEnvironment();

	static FORCEINLINE const UTentacleSettings&
	Get()
	{
		return *GetDefault<UTentacleSettings>();
	}
};
