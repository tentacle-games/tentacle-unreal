// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/StreamChatMessage.h"
#include "Tentacle/Subsystems/Stream/Kick/Types/KickUser.h"
#include "KickChatMessage.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UKickChatMessage : public UStreamChatMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FKickUser
	Sender;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);

		FJsonObjectPtr SenderJson;
		jsonField(FJsonObjectPtr, SenderJson, Json, "sender");
		Sender.SetFromJson(SenderJson);
	}
};
