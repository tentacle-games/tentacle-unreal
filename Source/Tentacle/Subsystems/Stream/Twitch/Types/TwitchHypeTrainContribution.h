// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchHypeTrainContributionType.h"
#include "TwitchUserBasic.h"
#include "Dom/JsonObject.h"
#include "Tentacle/Utilities/Json.h"
#include "TwitchHypeTrainContribution.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchHypeTrainContribution
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FTwitchUserBasic
	User;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	ETwitchHypeTrainContributionType
	Type = ETwitchHypeTrainContributionType::Bits;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	Total = 0;

	FTwitchHypeTrainContribution() = default;

	explicit
	FTwitchHypeTrainContribution(const TSharedPtr<FJsonObject>& Data)
	{
		jsonField(FName, User.Id, Data, "user_id");
		jsonField(FName, User.Name, Data, "user_login");
		jsonField(FString, User.DisplayName, Data, "user_name");
		jsonFieldEnum(ETwitchHypeTrainContributionType, Type, Data, "type");
		jsonField(int32, Total, Data, "total");
	}
};
