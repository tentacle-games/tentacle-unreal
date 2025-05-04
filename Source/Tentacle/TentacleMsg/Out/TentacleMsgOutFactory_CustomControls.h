// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent.h"
#include "Tentacle/TentacleMsg/Out/TentacleMsgOut.h"
#include "Tentacle/TentacleMsg/Out/TentacleMsgOutType.h"
#include "TentacleMsgOutFactory_CustomControls.generated.h"

UCLASS()
class TENTACLE_API UTentacleMsgOutFactory_CustomControls : public UObject
{
	GENERATED_BODY()

public:
	static UTentacleMsgOut*
	ControlState(const UCustomControlComponent* Control)
	{
		const auto Msg = NewObject<UTentacleMsgOut>();
		Msg->Type = FETentacleMsgOutType::CustomControls_ControlState;
		Msg->Data->SetObjectField("control", Control->ToJson());
		return Msg;
	}

	static UTentacleMsgOut*
	Initialize()
	{
		const auto Msg = NewObject<UTentacleMsgOut>();
		Msg->Type = FETentacleMsgOutType::CustomControls_Initialize;
		return Msg;
	}

	static UTentacleMsgOut*
	RegisterControl(const UCustomControlComponent* Control)
	{
		const auto Msg = NewObject<UTentacleMsgOut>();
		Msg->Type = FETentacleMsgOutType::CustomControls_RegisterControl;
		Msg->Data->SetObjectField("control", Control->ToJson());
		return Msg;
	}

	static UTentacleMsgOut*
	UnregisterControl(const UCustomControlComponent* Control)
	{
		const auto Msg = NewObject<UTentacleMsgOut>();
		Msg->Type = FETentacleMsgOutType::CustomControls_UnregisterControl;
		Msg->Data->SetObjectField("control", Control->ToJson());
		return Msg;
	}
};
