// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleSubsystem_CustomControls.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent.h"
#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent_WithValue.h"
#include "Tentacle/Subsystems/CustomControls/Base/CustomControlEvent.h"
#include "Tentacle/Subsystems/WebSocket/TentacleSubsystem_WebSocket.h"
#include "Tentacle/TentacleMsg/In/TentacleMsgIn.h"
#include "Tentacle/TentacleMsg/Out/TentacleMsgOutFactory_CustomControls.h"

void
UTentacleSubsystem_CustomControls::HandleMsg_Initialize(const UTentacleMsgIn* Msg)
{
	for (const auto& [ControlId, Control] : CustomControls)
		SendMsg_RegisterControl(Control);
}

void
UTentacleSubsystem_CustomControls::HandleMsg_ControlEvent(const UTentacleMsgIn* Msg)
{
	auto Event = FJsonObjectPtr();
	jsonField(FJsonObjectPtr, Event, Msg->Data, "event");

	auto ControlId = FName();
	jsonField(FName, ControlId, Event, "controlId");

	auto Type = ECustomControlEventType::Unknown;
	jsonFieldEnum(ECustomControlEventType, Type, Event, "type");

	const auto Control = CustomControls.FindRef(ControlId);
	softAssertMsgF(IsValid(Control), "Control component with id %s not found", *ControlId.ToString());

	switch (Type)
	{
	case ECustomControlEventType::Click:
		return Control->ReceiveClick();
	case ECustomControlEventType::MouseDown:
		return Control->ReceiveMouseDown();
	case ECustomControlEventType::MouseUp:
		return Control->ReceiveMouseUp();
	case ECustomControlEventType::ValueChange: {
		const auto CustomControlWithValue = Cast<ICustomControlComponent_WithValue>(Control);
		softAssertMsgF(CustomControlWithValue, "Control with label '%s' does not support ValueChange events", *Control->GetLabel());
		return CustomControlWithValue->HandleValueChangeEvent(Event);
	}
	default:
		softAssertMsgF(false, "Unhandled custom control event type '%s'", *FECustomControlEventType::ToName(Type).ToString());
	}
}

void
UTentacleSubsystem_CustomControls::RegisterCustomControl(UCustomControlComponent* Control)
{
	CustomControls.Add(Control->Id, Control);
	SendMsg_RegisterControl(Control);
}

void
UTentacleSubsystem_CustomControls::UnregisterCustomControl(UCustomControlComponent* Control)
{
	CustomControls.Remove(Control->Id);
	SendMsg_UnregisterControl(Control);
}

void
UTentacleSubsystem_CustomControls::SendControlState(const UCustomControlComponent* Control)
{
	const auto Msg = UTentacleMsgOutFactory_CustomControls::ControlState(Control);
	sendTentacleMsg(Msg);
}

void
UTentacleSubsystem_CustomControls::SendMsg_RegisterControl(const UCustomControlComponent* Control) const
{
	const auto Msg = UTentacleMsgOutFactory_CustomControls::RegisterControl(Control);
	sendTentacleMsg(Msg);
}

void
UTentacleSubsystem_CustomControls::SendMsg_UnregisterControl(const UCustomControlComponent* Control) const
{
	const auto Msg = UTentacleMsgOutFactory_CustomControls::UnregisterControl(Control);
	sendTentacleMsg(Msg);
}
