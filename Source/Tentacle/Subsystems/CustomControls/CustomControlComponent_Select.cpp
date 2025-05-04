// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Subsystems/CustomControls/CustomControlComponent_Select.h"
#include "Tentacle/Tentacle.h"

UCustomControlComponent_Select::UCustomControlComponent_Select()
{
	Type = StaticType;
}

void
UCustomControlComponent_Select::SetOptions_Implementation(const TArray<FString>& NewOptions)
{
	Options = NewOptions;
	SendControlState();
}

void
UCustomControlComponent_Select::SetOptionsFromNames_Implementation(const TArray<FName>& NewOptions)
{
	Options.Empty();
	for (const auto Option : NewOptions)
		Options.Add(Option.ToString());

	SendControlState();
}

FJsonObjectPtr
UCustomControlComponent_Select::ToJson() const
{
	auto Json = Super::ToJson();
	Json->SetStringField(TEXT("placeholder"), Placeholder);
	Json->SetArrayField(TEXT("options"), UJson::Array(Options));
	return Json;
}
