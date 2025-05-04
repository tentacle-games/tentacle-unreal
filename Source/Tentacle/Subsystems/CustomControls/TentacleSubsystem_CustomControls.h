// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent.h"
#include "TentacleSubsystem_CustomControls.generated.h"

UCLASS()
class TENTACLE_API UTentacleSubsystem_CustomControls : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FName /*CustomControlComponentId*/, class UCustomControlComponent*>
	CustomControls;

public:
	void
	HandleMsg_Initialize(const class UTentacleMsgIn* Msg);

	void
	HandleMsg_ControlEvent(const UTentacleMsgIn* Msg);

	void
	RegisterCustomControl(UCustomControlComponent* Control);

	void
	UnregisterCustomControl(UCustomControlComponent* Control);

	void
	SendControlState(const UCustomControlComponent* Control);

private:
	void
	SendMsg_RegisterControl(const UCustomControlComponent* Control) const;

	void
	SendMsg_UnregisterControl(const UCustomControlComponent* Control) const;
};
