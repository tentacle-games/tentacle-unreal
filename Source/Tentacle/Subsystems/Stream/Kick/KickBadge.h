// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/Kick/Types/KickBadgeType.h"
#include "Tentacle/Utilities/Json.h"
#include "KickBadge.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FKickBadge
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Text;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	EKickBadgeType
	Type;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	Count = 0;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		jsonField(FString, Text, Json, "text");
		jsonFieldEnum(EKickBadgeType, Type, Json, "type");
		jsonFieldOptional(int32, Count, Json, "count");
	}
};
