// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TclWebSocketClient.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketClient, Verbose, All);

UCLASS()
class TENTACLEWEBSOCKET_API UTclWebSocketClient : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketClient_OnMsgReceivedDelegate, const FString&, Msg);

	class FWebSocketClientRunnable*
	Runnable;

	FRunnableThread*
	Thread;

	FTimerHandle
	KeepAliveTimerHandle;

public:
	UPROPERTY()
	FWebSocketClient_OnMsgReceivedDelegate
	OnMsgReceived;

	void
	Start(const FString& Uri);

	void
	Stop();

	void
	Send(const FString& Msg);
};
