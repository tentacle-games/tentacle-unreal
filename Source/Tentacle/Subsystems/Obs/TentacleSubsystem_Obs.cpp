// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleSubsystem_Obs.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Subsystems/WebSocket/TentacleSubsystem_WebSocket.h"
#include "Tentacle/TentacleMsg/Out/TentacleMsgOutFactory_Obs.h"

void
UTentacleSubsystem_Obs::SetSourceFilterEnabled(const FString& SourceName, const FString& FilterName, bool bEnabled) const
{
	const auto Msg = UTentacleMsgOutFactory_Obs::Call_SetSourceFilterEnabled(SourceName, FilterName, bEnabled);
	sendTentacleMsg(Msg);
}
