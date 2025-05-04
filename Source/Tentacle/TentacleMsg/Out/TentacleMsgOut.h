// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "Tentacle/Utilities/Json.h"
#include "TentacleMsgOut.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTentacleMsgOut : public UObject
{
	GENERATED_BODY()

public:
	FString
	Id;

	FName
	Type;

	FJsonObjectPtr
	Data;

	UTentacleMsgOut()
	{
		Id = UCommon::MakeGuid();
		Data = MakeShareable(new FJsonObject);
	}

	FJsonObjectPtr
	ToJson() const
	{
		const FJsonObjectPtr Json = MakeShareable(new FJsonObject);
		Json->SetStringField("id", Id);
		Json->SetStringField("type", Type.ToString());
		Json->SetObjectField("data", Data);
		return Json;
	}
};
