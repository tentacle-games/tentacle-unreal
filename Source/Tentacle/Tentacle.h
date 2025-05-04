// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tentacle/Utilities/Common.h"
#include "Tentacle.generated.h"

UCLASS()
class TENTACLE_API ATentacle : public AActor
{
	GENERATED_BODY()

	friend class UTentacleTestUtils;

public:
	SINGLETON_ACTOR(ATentacle);

	UFUNCTION(BlueprintPure, Category="Tentacle", DisplayName="Get Tentacle", meta=(WorldContext="WorldContext", CompactNodeTitle="Tentacle"))
	static ATentacle*
	BP_Get(const UObject* WorldContext) { return Get(WorldContext); }

protected:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TMap<FName /*ViewerData.Id*/, UViewer*>
	Viewers;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TMap<FName /*ViewerData.Twitch.UserId*/, UViewer*>
	ViewersByTwitchId;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TMap<FName /*ViewerData.Id*/, class AViewerController*>
	ViewerControllers;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TMap<FName /*ViewerData.Twitch.UserId*/, AViewerController*>
	ViewerControllersByTwitchId;

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	class UTentacleSubsystem_Api*
	Api;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	class UTentacleSubsystem_CustomControls*
	CustomControls;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	class UTentacleSubsystem_CustomEvents*
	CustomEvents;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	class UTentacleSubsystem_Obs*
	Obs;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	class UTentacleSubsystem_Stream*
	Stream;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	class UTentacleSubsystem_Telemetry*
	Telemetry;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	class UTentacleSubsystem_WebSocket*
	WebSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tentacle")
	bool
	bDebugLog;

	ATentacle();

	virtual void
	BeginPlay() override;

	virtual void
	EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintPure, Category="Tentacle")
	UViewer*
	GetViewer(const FName& ViewerId) const;

	UFUNCTION(BlueprintPure, Category="Tentacle")
	AViewerController*
	GetViewerController(const FName& ViewerId) const;

	UFUNCTION(BlueprintPure, Category="Tentacle")
	class AViewerPawn*
	GetViewerPawn(const FName& ViewerId) const;

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	void
	DestroyViewer(const FName& ViewerId);

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	void
	DestroyAllViewers();

	TTuple<UViewer*, AViewerPawn*>
	UpsertViewer(UViewer* Viewer);

protected:
	UFUNCTION()
	void
	HandleMsg(const FString& JsonString);
};

#define sendTentacleMsg(Msg) \
	const auto _Tentacle = ATentacle::Get(this); \
	softAssertValid(_Tentacle); \
	softAssertValid(_Tentacle->WebSocket); \
	_Tentacle->WebSocket->Broadcast(Msg);
