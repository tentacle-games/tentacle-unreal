// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleSubsystem_Telemetry.h"
#include "Tentacle/Settings/TentacleSettings.h"
#include "Tentacle/Utilities/Common.h"
#include "Tentacle/Utilities/Json.h"
#include "WebSocket/TclWebSocketClient.h"

UTentacleSubsystem_Telemetry::UTentacleSubsystem_Telemetry()
{
	WebSocketClient = CreateDefaultSubobject<UTclWebSocketClient>(TEXT("WebSocketClient"));

	// Create reusable Json object and set shared values.
	LogMsgJson = MakeShareable(new FJsonObject);
	LogMsgJson->SetStringField("sourceName", TEXT("unreal"));
	LogMsgJson->SetStringField("sourceInstanceId", UCommon::MakeGuid());
}

void
UTentacleSubsystem_Telemetry::BeginDestroy()
{
	UObject::BeginDestroy();

	Stop();
}

void
UTentacleSubsystem_Telemetry::Start()
{
	WebSocketClient->Start(FTclUrls::LogService());
}

void
UTentacleSubsystem_Telemetry::Stop()
{
	if (IsValid(WebSocketClient))
		WebSocketClient->Stop();
}

void
UTentacleSubsystem_Telemetry::Debug(const FString& Msg) const
{
	SendLogMsg(LevelInfo, Msg);
}

void
UTentacleSubsystem_Telemetry::Info(const FString& Msg) const
{
	SendLogMsg(LevelInfo, Msg);
}

void
UTentacleSubsystem_Telemetry::Warn(const FString& Msg) const
{
	SendLogMsg(LevelWarn, Msg);
}

void
UTentacleSubsystem_Telemetry::Error(const FString& Msg) const
{
	SendLogMsg(LevelError, Msg);
}

void
UTentacleSubsystem_Telemetry::SendLogMsg(const FString& Level, const FString& Msg) const
{
	softAssertValid(WebSocketClient);
	LogMsgJson->SetStringField("level", Level);
	LogMsgJson->SetStringField("msg", Msg);
	WebSocketClient->Send(UJson::Stringify(LogMsgJson));
}
