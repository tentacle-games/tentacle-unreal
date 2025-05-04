// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/StreamSharedTypes.h"
#include "Tentacle/Utilities/Json.h"
#include "StreamEvent.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UStreamEvent : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadonly, Category="Tentacle")
	FDateTime
	CreatedAt;

	UPROPERTY(BlueprintReadonly, Category="Tentacle")
	FString
	Id;

	UPROPERTY(BlueprintReadonly, Category="Tentacle")
	EStreamPlatform
	Platform;

	UPROPERTY(BlueprintReadonly, Category="Tentacle")
	FName
	ViewerId;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		jsonField(FDateTime, CreatedAt, Json, "$createdAt");
		jsonField(FString, Id, Json, "$id");
		jsonFieldEnum(EStreamPlatform, Platform, Json, "$platform");
		jsonFieldOptional(FName, ViewerId, Json, "$viewerId");
	}
};
