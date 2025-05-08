// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchBroadcasterType.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchSubscription.h"
#include "Tentacle/Subsystems/Stream/Twitch/Types/TwitchUserType.h"
#include "Tentacle/Utilities/Json.h"
#include "UObject/Object.h"
#include "ViewerTwitch.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FViewerTwitch
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	ETwitchBroadcasterType
	BroadcasterType = ETwitchBroadcasterType::Unset;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FLinearColor
	Color;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FDateTime
	CreatedAt;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	Description;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	DisplayName;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FName
	Id;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	bool
	IsKnownBot = false;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	bool
	IsSubscriber = false;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	Name;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	OfflineImageUrl;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	ProfileImageUrl;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FTwitchSubscription
	Subscription;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	ETwitchUserType
	Type = ETwitchUserType::Unset;

	bool
	IsValid() const { return !Id.IsNone(); }

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		jsonField(FName, Id, Json, "id");
		jsonField(FString, Name, Json, "name");
		jsonField(FString, DisplayName, Json, "displayName");

		jsonFieldEnum(ETwitchBroadcasterType, BroadcasterType, Json, "broadcasterType");
		jsonFieldOptional(FLinearColor, Color, Json, "color"); // TODO: Generate random color on backend if not set.
		jsonField(FDateTime, CreatedAt, Json, "createdAt");
		jsonField(FString, Description, Json, "description");
		jsonField(FString, OfflineImageUrl, Json, "offlineImageUrl");
		jsonField(FString, ProfileImageUrl, Json, "profileImageUrl");

		FJsonObjectPtr SubscriptionJson;
		jsonFieldOptional(FJsonObjectPtr, SubscriptionJson, Json, "subscription");
		if (SubscriptionJson.IsValid())
		{
			IsSubscriber = true;
			Subscription.SetFromJson(SubscriptionJson);
		}

		jsonFieldEnum(ETwitchUserType, Type, Json, "type");
	}
};
