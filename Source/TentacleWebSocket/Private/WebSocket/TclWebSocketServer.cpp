// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#include "WebSocket/TclWebSocketServer.h"
#include "WebSocket/TclWebSocketServerRunnable.h"

DEFINE_LOG_CATEGORY(LogWebSocketServer);

UTclWebSocketServer::~UTclWebSocketServer()
{
	Stop();
}

void UTclWebSocketServer::Start(int32 Port)
{
	if (Runnable || Thread)
	{
		UE_LOG(LogWebSocketServer, Error, TEXT("Server already running"))
		return;
	}

	UE_LOG(LogWebSocketServer, Display, TEXT("Starting server (ws://localhost:%d)"), Port)

	Runnable = new FWebSocketServerRunnable(Port);
	Runnable->OnMsgReceived.BindLambda([this](const FString Msg) {
		FFunctionGraphTask::CreateAndDispatchWhenReady([Msg, this]
		{
			OnMsgReceived.Broadcast(Msg);
		}, TStatId(), nullptr, ENamedThreads::GameThread);
	});

	Thread = FRunnableThread::Create(Runnable, TEXT("WebSocketServer"));
}

void UTclWebSocketServer::Stop()
{
	if (!Runnable)
		return;

	UE_LOG(LogWebSocketServer, Display, TEXT("Stopping server"))

	Runnable->Stop();
	Thread->Kill();

	delete Thread;
	Thread = nullptr;

	delete Runnable;
	Runnable = nullptr;
}

void UTclWebSocketServer::Broadcast(const FString& Msg)
{
	if (Runnable)
		Runnable->Broadcast(Msg);
}
