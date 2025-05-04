// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Subsystems/Stream/Kick/KickBadge.h"
#include "KickUser.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FKickIdentity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	TArray<FKickBadge>
	Badges;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FLinearColor
	UsernameColor;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		TArray<FJsonObjectPtr> BadgesJson;
		jsonField(TArray<FJsonObjectPtr>, BadgesJson, Json, "badges");
		for (const auto& BadgeJson : BadgesJson)
		{
			FKickBadge Badge;
			Badge.SetFromJson(BadgeJson);
			Badges.Add(Badge);
		}

		jsonField(FLinearColor, UsernameColor, Json, "username_color");
	}
};

USTRUCT(BlueprintType)
struct TENTACLE_API FKickUser
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	ChannelSlug;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	bool
	IsAnonymous = false;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	bool
	IsVerified = false;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FKickIdentity
	Identity;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	ProfilePicture;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	int32
	UserId;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Username;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		jsonField(FString, ChannelSlug, Json, "channel_slug");
		jsonField(bool, IsAnonymous, Json, "is_anonymous");
		jsonField(bool, IsVerified, Json, "is_verified");

		FJsonObjectPtr IdentityJson;
		jsonField(FJsonObjectPtr, IdentityJson, Json, "identity");
		Identity.SetFromJson(IdentityJson);

		jsonField(FString, ProfilePicture, Json, "profile_picture");
		jsonField(int32, UserId, Json, "user_id");
		jsonField(FString, Username, Json, "username");
	}
};
