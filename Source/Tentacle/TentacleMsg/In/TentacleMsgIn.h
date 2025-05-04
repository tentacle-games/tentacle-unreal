// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "Tentacle/TentacleMsg/In/TentacleMsgInType.h"
#include "Tentacle/Utilities/Json.h"
#include "TentacleMsgIn.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTentacleMsgIn : public UObject
{
	GENERATED_BODY()

public:
	FString
	Id;

	ETentacleMsgInType
	Type;

	FJsonObjectPtr
	Data;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());
		jsonField(FString, Id, Json, "id");
		jsonFieldEnum(ETentacleMsgInType, Type, Json, "type");
		jsonFieldOptional(FJsonObjectPtr, Data, Json, "data");
	}
};
