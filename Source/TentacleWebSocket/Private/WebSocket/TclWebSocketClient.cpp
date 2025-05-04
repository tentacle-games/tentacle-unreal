// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "WebSocket/TclWebSocketClient.h"
#include "WebSocket/TclWebSocketClientRunnable.h"

DEFINE_LOG_CATEGORY(LogWebSocketClient);

void
UTclWebSocketClient::Start(const FString& Uri)
{
	if (Runnable || Thread)
	{
		UE_LOG(LogWebSocketClient, Warning, TEXT("Client already running"))
		return;
	}

	UE_LOG(LogWebSocketClient, Display, TEXT("Starting client (%s)"), *Uri)

	Runnable = new FWebSocketClientRunnable(Uri);
	Runnable->OnMsgReceived.BindLambda(
		[this](const FString Msg)
		{
			OnMsgReceived.Broadcast(Msg);
		}
	);

	Thread = FRunnableThread::Create(Runnable, TEXT("WebSocketClient"));

	// GetWorld()->GetTimerManager().SetTimer(
	// 	KeepAliveTimerHandle,
	// 	[this]
	// 	{
	// 		// Runnable->
	// 	},
	// 	1.f,
	// 	true
	// );
}

void
UTclWebSocketClient::Stop()
{
	if (!Runnable || !Thread)
	{
		UE_LOG(LogWebSocketClient, Warning, TEXT("Client already stopped"))
		return;
	}

	UE_LOG(LogWebSocketClient, Display, TEXT("Stopping client"))

	Runnable->Stop();
	Thread->Kill();

	delete Thread;
	Thread = nullptr;

	delete Runnable;
	Runnable = nullptr;

	// GetWorld()->GetTimerManager().ClearTimer(KeepAliveTimerHandle);
}

void
UTclWebSocketClient::Send(const FString& Msg)
{
	if (Runnable)
		Runnable->Send(Msg);
}
