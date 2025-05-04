#pragma once

#include "Dom/JsonObject.h"
#include "TwitchUserBasic.h"
#include "Tentacle/Utilities/Json.h"
#include "TwitchChatParentMessage.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchChatParentMessage
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString Id;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString Text;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FTwitchUserBasic User;

	FTwitchChatParentMessage() = default;

	explicit FTwitchChatParentMessage(const TSharedPtr<FJsonObject>& Data)
	{
		jsonField(FString, Id, Data, "id");
		jsonField(FString, Text, Data, "text");
		jsonField(FName, User.Id, Data, "user_id");
		jsonField(FName, User.Name, Data, "user_name");
		jsonField(FString, User.DisplayName, Data, "user_display_name");
	}
};
