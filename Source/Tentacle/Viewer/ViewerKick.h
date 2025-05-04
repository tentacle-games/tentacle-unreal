// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "Tentacle/Subsystems/Stream/Kick/KickBadge.h"
#include "Tentacle/Utilities/Json.h"
#include "ViewerKick.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FViewerKick
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	TArray<FKickBadge>
	Badges;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	ChannelSlug;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FLinearColor
	Color;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	int32
	Id = -1;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	bool
	IsAnonymous = false;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	bool
	IsVerified = false;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	ProfilePicture;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FString
	Username;

	bool
	IsValid() const { return Id >= 0; }

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		TArray<FJsonObjectPtr> BadgesJson;
		jsonFieldOptional(TArray<FJsonObjectPtr>, BadgesJson, Json, "badges");
		for (const auto& BadgeJson : BadgesJson)
		{
			FKickBadge Badge;
			Badge.SetFromJson(BadgeJson);
			Badges.Add(Badge);
		}

		jsonFieldOptional(FString, ChannelSlug, Json, "channelSlug");
		jsonFieldOptional(FLinearColor, Color, Json, "color");
		jsonField(int32, Id, Json, "id");
		jsonField(bool, IsAnonymous, Json, "isAnonymous");
		jsonField(bool, IsVerified, Json, "isVerified");
		jsonFieldOptional(FString, ProfilePicture, Json, "profilePicture");
		jsonField(FString, Username, Json, "username");
	}
};
