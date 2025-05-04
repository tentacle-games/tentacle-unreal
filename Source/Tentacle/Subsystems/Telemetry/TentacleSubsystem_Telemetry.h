// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TentacleSubsystem_Telemetry.generated.h"

UCLASS()
class TENTACLE_API UTentacleSubsystem_Telemetry : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	class UTclWebSocketClient*
	WebSocketClient;

	TSharedPtr<FJsonObject>
	LogMsgJson;

	FString
	LevelDebug = FString("debug");

	FString
	LevelInfo = FString("info");

	FString
	LevelWarn = FString("warn");

	FString
	LevelError = FString("error");

public:
	UTentacleSubsystem_Telemetry();

	virtual void
	BeginDestroy() override;

	void
	Start();

	void
	Stop();

	void
	Debug(const FString& Msg) const;

	void
	Info(const FString& Msg) const;

	void
	Warn(const FString& Msg) const;

	void
	Error(const FString& Msg) const;

protected:
	void
	SendLogMsg(const FString& Level, const FString& Msg) const;
};
