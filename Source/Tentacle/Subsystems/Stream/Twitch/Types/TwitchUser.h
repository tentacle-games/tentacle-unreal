// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "TwitchUserType.h"
#include "Dom/JsonObject.h"
#include "TwitchUser.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchUser
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	TMap<FName, FString>
	BadgeInfo;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	TMap<FName, FString>
	Badges;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FLinearColor
	Color = FLinearColor::White;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	DisplayName;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FName
	Id;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsArtist = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsBroadcaster = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsFounder = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsMod = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsSubscriber = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsVip = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FName
	Name;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	ETwitchUserType
	UserType = ETwitchUserType::Unset;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		FJsonObjectPtr BadgeInfoJson;
		jsonField(FJsonObjectPtr, BadgeInfoJson, Json, "badge_info");
		if (BadgeInfoJson.IsValid())
		{
			for (const auto& BadgeEntry : BadgeInfoJson->Values)
				BadgeInfo.Add(FName(BadgeEntry.Key), BadgeEntry.Value->AsString());
		}

		FJsonObjectPtr BadgesJson;
		jsonField(FJsonObjectPtr, BadgesJson, Json, "badges");
		if (BadgesJson.IsValid())
		{
			for (const auto& BadgeEntry : BadgesJson->Values)
				Badges.Add(FName(BadgeEntry.Key), BadgeEntry.Value->AsString());
		}

		jsonFieldOptional(FLinearColor, Color, Json, "color");
		jsonField(FString, DisplayName, Json, "display_name");
		jsonField(bool, IsArtist, Json, "is_artist");
		jsonField(bool, IsBroadcaster, Json, "is_broadcaster");
		jsonField(bool, IsFounder, Json, "is_founder");
		jsonField(bool, IsMod, Json, "is_mod");
		jsonField(bool, IsSubscriber, Json, "is_subscriber");
		jsonField(bool, IsVip, Json, "is_vip");
		jsonField(FName, Id, Json, "user_id");
		jsonField(FName, Name, Json, "user_name");
		jsonFieldEnumOptional(ETwitchUserType, UserType, Json, "user_type");
	}

	static FTwitchUser
	MakeRandom()
	{
		static auto Count = 0;
		Count++;

		FTwitchUser User;
		User.Color = FLinearColor::MakeRandomColor();
		User.DisplayName = FString::Format(TEXT("TestUser_{0}"), {Count});
		User.Id = FName(*User.DisplayName);
		User.IsArtist = false;
		User.IsBroadcaster = false;
		User.IsFounder = false;
		User.IsMod = false;
		User.IsSubscriber = false;
		User.IsVip = false;
		User.Name = FName(*User.DisplayName);
		User.UserType = ETwitchUserType::Unset;
		return User;
	}
};
