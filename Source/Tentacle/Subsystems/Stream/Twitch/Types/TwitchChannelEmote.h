// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "Tentacle/Utilities/Json.h"
#include "TwitchChannelEmote.generated.h"

UENUM(BlueprintType)
enum class ETwitchEmoteType : uint8
{
	Bitstier,
	Follower,
	Subscriptions,
	Unknown,
};

struct TENTACLE_API FETwitchEmoteType
{
	using EnumType = ETwitchEmoteType;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{TEXT("bitstier"), EnumType::Bitstier},
			{TEXT("follower"), EnumType::Follower},
			{TEXT("subscriptions"), EnumType::Subscriptions},
		};
		const auto FindResult = Map.Find(Value);
		return FindResult != nullptr ? *FindResult : EnumType::Unknown;
	}
};

UENUM(BlueprintType)
enum class ETwitchEmoteFormat : uint8
{
	Animated,
	Static,
	Unknown,
};

struct TENTACLE_API FETwitchEmoteFormat
{
	using EnumType = ETwitchEmoteFormat;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{TEXT("animated"), EnumType::Animated},
			{TEXT("static"), EnumType::Static},
		};
		const auto FindResult = Map.Find(Value);
		return FindResult != nullptr ? *FindResult : EnumType::Unknown;
	}
};

UENUM()
enum class ETwitchEmoteScale : uint8
{
	One,
	Two,
	Three,
	Unknown,
};

struct TENTACLE_API FETwitchEmoteScale
{
	using EnumType = ETwitchEmoteScale;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{TEXT("1.0"), EnumType::One},
			{TEXT("2.0"), EnumType::Two},
			{TEXT("3.0"), EnumType::Three},
		};
		const auto FindResult = Map.Find(Value);
		return FindResult != nullptr ? *FindResult : EnumType::Unknown;
	}
};

UENUM()
enum class ETwitchEmoteThemeMode : uint8
{
	Dark,
	Light,
	Unknown,
};

struct TENTACLE_API FETwitchEmoteThemeMode
{
	using EnumType = ETwitchEmoteThemeMode;

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{TEXT("dark"), EnumType::Dark},
			{TEXT("light"), EnumType::Light},
		};
		const auto FindResult = Map.Find(Value);
		return FindResult != nullptr ? *FindResult : EnumType::Unknown;
	}
};

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchEmoteImages
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString Url1x;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString Url2x;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString Url4x;
};

USTRUCT(BlueprintType)
struct TENTACLE_API FTwitchChannelEmote
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Id;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Name;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FTwitchEmoteImages
	Images;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	Tier;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	ETwitchEmoteType
	EmoteType = ETwitchEmoteType::Unknown;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	FString
	EmoteSetId;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	ETwitchEmoteFormat
	Format = ETwitchEmoteFormat::Unknown;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	ETwitchEmoteScale
	Scale = ETwitchEmoteScale::Unknown;

	UPROPERTY(BlueprintReadOnly, Category="Tentacle")
	ETwitchEmoteThemeMode
	ThemeMode = ETwitchEmoteThemeMode::Unknown;

	FTwitchChannelEmote() = default;

	explicit
	FTwitchChannelEmote(const TSharedPtr<FJsonObject>& Data)
	{
		jsonField(FString, Id, Data, "id");
		jsonField(FString, Name, Data, "name");
		jsonField(FString, Images.Url1x, Data, "images", "url_1x");
		jsonField(FString, Images.Url2x, Data, "images", "url_2x");
		jsonField(FString, Images.Url4x, Data, "images", "url_4x");
		jsonField(FString, Tier, Data, "tier");
		jsonFieldEnum(ETwitchEmoteType, EmoteType, Data, "emote_type");
		jsonField(FString, EmoteSetId, Data, "emote_set_id");
		jsonFieldEnum(ETwitchEmoteFormat, Format, Data, "format");
		jsonFieldEnum(ETwitchEmoteScale, Scale, Data, "scale");
		jsonFieldEnum(ETwitchEmoteThemeMode, ThemeMode, Data, "theme_mode");
	}
};
