// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/TentacleMsg/Out/TentacleMsgOut.h"
#include "Tentacle/TentacleMsg/Out/TentacleMsgOutType.h"
#include "TentacleMsgOutFactory_Obs.generated.h"

UCLASS()
class TENTACLE_API UTentacleMsgOutFactory_Obs : public UObject
{
	GENERATED_BODY()

public:
	static UTentacleMsgOut*
	Call_SetSourceFilterEnabled(const FString& SourceName, const FString& FilterName, bool bEnabled)
	{
		const FJsonObjectPtr Data = MakeShareable(new FJsonObject);
		Data->SetStringField("sourceName", SourceName);
		Data->SetStringField("filterName", FilterName);
		Data->SetBoolField("filterEnabled", bEnabled);
		return Call(TEXT("SetSourceFilterEnabled"), Data);
	}

private:
	static UTentacleMsgOut*
	Call(const FString& RequestType, const FJsonObjectPtr& RequestData)
	{
		const auto Msg = NewObject<UTentacleMsgOut>();
		Msg->Type = FETentacleMsgOutType::Obs_Call;
		Msg->Data->SetStringField("requestType", RequestType);
		Msg->Data->SetObjectField("requestData", RequestData);
		return Msg;
	}
};
