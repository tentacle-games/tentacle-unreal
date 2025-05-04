// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Tentacle/Utilities/Json.h"
#include "TwitchCustomRewardDefine.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchCustomRewardDefine
{
	GENERATED_BODY()

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Id;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Title;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	Cost = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Prompt;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	Image;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	BackgroundColor;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsEnabled = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsUserInputRequired = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsMaxPerStreamEnabled = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	MaxPerStream = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsMaxPerUserPerStreamEnabled = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	MaxPerUserPerStream = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsGlobalCooldownEnabled = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	int32
	GlobalCooldownSeconds = 0;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsPaused = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	IsInStock = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	DefaultImageUrl1x;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	DefaultImageUrl2x;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	DefaultImageUrl4x;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	bool
	ShouldRedemptionsSkipRequestQueue = false;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	RedemptionsRedeemedCurrentStream;

	UPROPERTY(Category="Tentacle", BlueprintReadOnly)
	FString
	CooldownExpiresAt;

	FTwitchCustomRewardDefine() = default;

	explicit
	FTwitchCustomRewardDefine(const TSharedPtr<FJsonObject>& Data)
	{
		jsonField(FString, Id, Data, "id");
		jsonField(FString, Title, Data, "title");
		jsonField(int32, Cost, Data, "cost");
		jsonField(FString, Prompt, Data, "prompt");
		jsonField(FString, Image, Data, "image");
		jsonField(FString, BackgroundColor, Data, "background_color");
		jsonField(bool, IsEnabled, Data, "is_enabled");
		jsonField(bool, IsUserInputRequired, Data, "is_user_input_required");
		jsonField(bool, IsMaxPerStreamEnabled, Data, "max_per_stream_setting", "is_enabled");
		jsonField(int32, MaxPerStream, Data, "max_per_stream_setting", "max_per_stream");
		jsonField(bool, IsMaxPerUserPerStreamEnabled, Data, "max_per_user_per_stream_setting", "is_enabled");
		jsonField(int32, MaxPerUserPerStream, Data, "max_per_user_per_stream_setting", "max_per_user_per_stream");
		jsonField(bool, IsGlobalCooldownEnabled, Data, "global_cooldown_setting", "is_enabled");
		jsonField(int32, GlobalCooldownSeconds, Data, "global_cooldown_setting", "global_cooldown_seconds");
		jsonField(bool, IsPaused, Data, "is_paused");
		jsonField(bool, IsInStock, Data, "is_in_stock");
		jsonField(FString, DefaultImageUrl1x, Data, "default_image", "url_1x");
		jsonField(FString, DefaultImageUrl2x, Data, "default_image", "url_2x");
		jsonField(FString, DefaultImageUrl4x, Data, "default_image", "url_4x");
		jsonField(bool, ShouldRedemptionsSkipRequestQueue, Data, "should_redemptions_skip_request_queue");
		jsonField(FString, RedemptionsRedeemedCurrentStream, Data, "redemptions_redeemed_current_stream");
		jsonField(FString, CooldownExpiresAt, Data, "cooldown_expires_at");
	}
};
