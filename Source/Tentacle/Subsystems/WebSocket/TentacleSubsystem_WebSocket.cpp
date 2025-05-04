// © 2024 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleSubsystem_WebSocket.h"
#include "Tentacle/TentacleMsg/Out/TentacleMsgOut.h"
#include "WebSocket/TclWebSocketServer.h"

UTentacleSubsystem_WebSocket::UTentacleSubsystem_WebSocket()
{
	WebSocketServer = CreateDefaultSubobject<UTclWebSocketServer>(TEXT("WebSocketServer"));
}

void
UTentacleSubsystem_WebSocket::Start()
{
	addDynamicSafe(WebSocketServer->OnMsgReceived, UTentacleSubsystem_WebSocket::HandleMsg);
	WebSocketServer->Start();
}

void
UTentacleSubsystem_WebSocket::Stop()
{
	if (WebSocketServer)
		WebSocketServer->Stop();
}

void
UTentacleSubsystem_WebSocket::BeginDestroy()
{
	UObject::BeginDestroy();

	Stop();
}

void UTentacleSubsystem_WebSocket::Broadcast(const UTentacleMsgOut* Msg) const
{
	softAssertValid(WebSocketServer);

	const auto JsonString = UJson::Stringify(Msg->ToJson());
	UCommon::LogDebug(FString::Printf(TEXT("Sending message: %s"), *JsonString));
	WebSocketServer->Broadcast(JsonString);
}

void UTentacleSubsystem_WebSocket::HandleMsg(const FString& JsonString)
{
	UCommon::LogDebug(FString::Printf(TEXT("Received message: %s"), *JsonString));
	OnMsgReceived.Broadcast(JsonString);
}
