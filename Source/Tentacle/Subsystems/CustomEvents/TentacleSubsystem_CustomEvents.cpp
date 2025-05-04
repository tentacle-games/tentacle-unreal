// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleSubsystem_CustomEvents.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Subsystems/CustomEvents/CustomEvent.h"
#include "Tentacle/TentacleMsg/In/TentacleMsgIn.h"
#include "Tentacle/Viewer/Viewer.h"

void
UTentacleSubsystem_CustomEvents::HandleMsg_Event(const UTentacleMsgIn* Msg)
{
	const auto CustomEvent = NewObject<UCustomEvent>();
	CustomEvent->SetFromJson(Msg->Data);

	AViewerPawn* InstigatedBy = nullptr;
	if (IsValid(CustomEvent->Viewer))
	{
		const auto Tentacle = ATentacle::Get(this);
		softAssertValid(Tentacle);
		InstigatedBy = Tentacle->UpsertViewer(CustomEvent->Viewer).Value;
	}

	OnEvent.Broadcast(CustomEvent, InstigatedBy);
}
