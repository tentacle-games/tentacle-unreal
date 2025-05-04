// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "CustomControlComponent.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Subsystems/CustomControls/TentacleSubsystem_CustomControls.h"
#include "Tentacle/Subsystems/WebSocket/TentacleSubsystem_WebSocket.h"

UCustomControlComponent::UCustomControlComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Id = FName(UCommon::MakeGuid());
	SortPriority = 0;
}

void
UCustomControlComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]
	{
		// Register custom control.
		const auto Tentacle = ATentacle::Get(this);
		softAssertValid(Tentacle);
		Tentacle->CustomControls->RegisterCustomControl(this);
	});
}

void
UCustomControlComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Unregister custom control.
	const auto Tentacle = ATentacle::Get(this);
	softAssertValid(Tentacle);
	Tentacle->CustomControls->UnregisterCustomControl(this);
}

void
UCustomControlComponent::SendControlState()
{
	const auto Tentacle = ATentacle::Get(this);
	softAssertValid(Tentacle);
	Tentacle->CustomControls->SendControlState(this);
}

FName
UCustomControlComponent::GetType() const
{
	softAssertMsgR(!Type.IsNone(), "Custom control type is not defined", FName());
	return Type;
}

FJsonObjectPtr
UCustomControlComponent::ToJson() const
{
	FJsonObjectPtr Json = MakeShared<FJsonObject>();
	Json->SetStringField(TEXT("id"), Id.ToString());
	Json->SetStringField(TEXT("type"), Type.ToString());
	Json->SetStringField(TEXT("label"), _Label);
	Json->SetStringField(TEXT("group"), Group);
	Json->SetNumberField(TEXT("sortPriority"), SortPriority);
	return Json;
}
