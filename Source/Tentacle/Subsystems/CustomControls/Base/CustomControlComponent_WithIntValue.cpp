// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent_WithIntValue.h"

void
UCustomControlComponent_WithIntValue::HandleValueChangeEvent(const FJsonObjectPtr& Event)
{
	int64 NewValue = 0;
	jsonField(int64, NewValue, Event, "value");
	return ShouldValueChangeFromWeb(NewValue) ? ValueChangedFromWeb(NewValue) : SendControlState();
}

void
UCustomControlComponent_WithIntValue::SetValue_Implementation(int64 NewValue)
{
	_Value = NewValue;
	SendControlState();
}

void
UCustomControlComponent_WithIntValue::ValueChangedFromWeb_Implementation(int64 NewValue)
{
	const auto OldValue = _Value;
	_Value = NewValue;
	OnValueChangedFromWeb.Broadcast(NewValue, OldValue);
}

FJsonObjectPtr
UCustomControlComponent_WithIntValue::ToJson() const
{
	auto Json = Super::ToJson();
	Json->SetNumberField(TEXT("value"), _Value);
	return Json;
}
