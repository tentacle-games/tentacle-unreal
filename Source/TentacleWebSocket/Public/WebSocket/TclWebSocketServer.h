// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TclWebSocketServer.generated.h"

class FWebSocketServerRunnable;

DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketServer, Verbose, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketServer_OnMsgReceivedDelegate, const FString&, Msg);

UCLASS()
class TENTACLEWEBSOCKET_API UTclWebSocketServer : public UObject
{
	GENERATED_BODY()

	FWebSocketServerRunnable* Runnable;
	FRunnableThread* Thread;

public:
	UPROPERTY()
	FWebSocketServer_OnMsgReceivedDelegate OnMsgReceived;

	virtual ~UTclWebSocketServer() override;

	void Start(int32 Port = 7321);
	void Stop();
	void Broadcast(const FString& Msg);
};
