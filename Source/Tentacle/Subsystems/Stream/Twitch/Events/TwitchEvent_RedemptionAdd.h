// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Tentacle/Subsystems/Stream/Twitch/Events/TwitchEvent.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchReward.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchUserBasic.h"
#include "Tentacle/Utilities/Json.h"
#include "TwitchEvent_RedemptionAdd.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UTwitchEvent_RedemptionAdd : public UTwitchEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FName
	UserId;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FName
	UserName;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	UserDisplayName;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FDateTime
	RedeemedAt;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FTwitchReward
	Reward;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	ETwitchRewardRedemptionStatus
	Status = ETwitchRewardRedemptionStatus::Unknown;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FTwitchUserBasic
	User;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	UserInput;

	virtual void
	SetFromJson(const FJsonObjectPtr& Json) override
	{
		softAssert(Json.IsValid());
		Super::SetFromJson(Json);
		jsonField(FDateTime, RedeemedAt, Json, "redeemed_at");
		FJsonObjectPtr RewardJson;
		jsonField(FJsonObjectPtr, RewardJson, Json, "reward");
		Reward.SetFromJson(RewardJson);
		jsonFieldEnum(ETwitchRewardRedemptionStatusUtils, Status, Json, "status");
		jsonField(FName, UserId, Json, "user_id");
		jsonField(FName, UserName, Json, "user_login");
		jsonField(FString, UserDisplayName, Json, "user_name");
		jsonField(FString, UserInput, Json, "user_input");

		// Trim whitespace from reward prompt.
		Reward.Prompt.TrimStartAndEndInline();
	}

	bool
	HasReward(const FName RewardName) const
	{
		return Reward.Title == RewardName;
	}
};
