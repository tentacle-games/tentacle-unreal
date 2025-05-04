// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent_WithBoolValue.h"

void
UCustomControlComponent_WithBoolValue::HandleValueChangeEvent(const FJsonObjectPtr& Event)
{
	auto NewValue = false;
	jsonField(bool, NewValue, Event, "value");
	return ShouldValueChangeFromWeb(NewValue)
		? ValueChangedFromWeb(NewValue)
		: SendControlState();
}

void
UCustomControlComponent_WithBoolValue::SetValue_Implementation(bool NewValue)
{
	_Value = NewValue;
	SendControlState();
}

void
UCustomControlComponent_WithBoolValue::ValueChangedFromWeb_Implementation(bool NewValue)
{
	const auto OldValue = _Value;
	_Value = NewValue;
	OnValueChangedFromWeb.Broadcast(NewValue, OldValue);
}

FJsonObjectPtr
UCustomControlComponent_WithBoolValue::ToJson() const
{
	auto Json = Super::ToJson();
	Json->SetBoolField(TEXT("value"), _Value);
	return Json;
}
