// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Utilities/StringUtils.h"
#include "StreamSharedTypes.generated.h"

//
// StreamPlatform
//

UENUM()
enum class EStreamPlatform : uint8
{
	Unknown,
	Twitch,
	Kick,
};

struct TENTACLE_API FEStreamPlatform
{
	using EnumType = EStreamPlatform;

	static const inline auto Kick = FName(TEXT("Kick"));
	static const inline auto Twitch = FName(TEXT("Twitch"));

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{Kick, EnumType::Kick},
			{Twitch, EnumType::Twitch},
		};
		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EnumType::Unknown;
	}

	static FName
	ToName(const EnumType Value)
	{
		static TMap<EnumType, FName> Map = {
			{EnumType::Kick, Kick},
			{EnumType::Twitch, Twitch},
		};
		return Map.FindRef(Value);
	}
};

//
// ChatMessageEmoji
//

USTRUCT(BlueprintType)
struct TENTACLE_API FChatMessageEmoji
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName
	Code;

	UPROPERTY(BlueprintReadOnly)
	FName
	Name;

	UPROPERTY(BlueprintReadOnly)
	int32
	Count = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<FStringPosition>
	Positions;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		softAssert(Json.IsValid());

		jsonField(FName, Code, Json, "code");
		jsonField(FName, Name, Json, "name");
		jsonField(int32, Count, Json, "count");

		FJsonObjectPtr PositionsJson;
		jsonField(FJsonObjectPtr, PositionsJson, Json, "positions");

	}
};

//
// ChatMessageEmote
//

USTRUCT(BlueprintType)
struct TENTACLE_API FChatMessageEmote
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName
	Id;

	UPROPERTY(BlueprintReadOnly)
	FName
	Name;

	UPROPERTY(BlueprintReadOnly)
	int32
	Count = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<FStringPosition>
	Positions;
};

//
// ChatCommand
//

template <typename T>
concept is_numeric = std::is_same_v<T, int32> || std::is_same_v<T, int64> || std::is_same_v<T, float> || std::is_same_v<T, double>;

USTRUCT(BlueprintType)
struct TENTACLE_API FChatCommand
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Args;

	UPROPERTY(BlueprintReadOnly)
	FName Name;

	bool
	IsArgNumeric(const int32 Index) const
	{
		return Args.IsValidIndex(Index) && Args[Index].IsNumeric();
	}

	template <typename T> requires is_numeric<T>
	bool
	TryGetArg(const int32 Index, T& OutX) const
	{
		if (!IsArgNumeric(Index))
			return false;

		if constexpr (std::is_same_v<T, int32>)
			OutX = FCString::Atoi(*Args[Index]);
		else if constexpr (std::is_same_v<T, int64>)
			OutX = FCString::Atoi64(*Args[Index]);
		else if constexpr (std::is_same_v<T, float>)
			OutX = FCString::Atof(*Args[Index]);
		else if constexpr (std::is_same_v<T, double>)
			OutX = FCString::Atod(*Args[Index]);

		return true;
	}

	template <typename T> requires is_numeric<T>
	bool
	TryGetArgs(const int32 Count, TArray<T>& Values) const
	{
		Values.Init(0, Count);

		for (auto i = 0; i < Count; ++i)
		{
			T Value;
			if (!TryGetArg(i, Value))
				return false;

			Values[i] = Value;
		}

		return true;
	}
};
