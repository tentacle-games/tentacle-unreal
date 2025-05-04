// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Subsystems/CustomControls/Base/CustomControlComponent_WithStringValue.h"
#include "Tentacle/Tentacle.h"

void
UCustomControlComponent_WithStringValue::HandleValueChangeEvent(const FJsonObjectPtr& Event)
{
	auto NewValue = FString();
	jsonField(FString, NewValue, Event, "value");
	return ShouldValueChangeFromWeb(NewValue) ? ValueChangedFromWeb(NewValue) : SendControlState();
}

void
UCustomControlComponent_WithStringValue::SetValue_Implementation(const FString& NewValue)
{
	_Value = NewValue;
	SendControlState();
}

void
UCustomControlComponent_WithStringValue::ValueChangedFromWeb_Implementation(const FString& NewValue)
{
	const auto OldValue = _Value;
	_Value = NewValue;
	OnValueChangedFromWeb.Broadcast(NewValue, OldValue);
}

FJsonObjectPtr
UCustomControlComponent_WithStringValue::ToJson() const
{
	auto Json = Super::ToJson();
	Json->SetStringField(TEXT("value"), _Value);
	return Json;
}
