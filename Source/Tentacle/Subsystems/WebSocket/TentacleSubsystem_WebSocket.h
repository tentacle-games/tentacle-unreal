// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TentacleSubsystem_WebSocket.generated.h"

UCLASS()
class TENTACLE_API UTentacleSubsystem_WebSocket : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMsgReceived, const FString&, JsonString);

	UPROPERTY()
	class UTclWebSocketServer*
	WebSocketServer;

public:
	FOnMsgReceived
	OnMsgReceived;

	UTentacleSubsystem_WebSocket();

	void
	Start();

	void
	Stop();

	virtual void
	BeginDestroy() override;

	void
	Broadcast(const class UTentacleMsgOut* Msg) const;

protected:
	UFUNCTION()
	void
	HandleMsg(const FString& JsonString);
};
