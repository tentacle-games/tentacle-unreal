// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "ViewerPropertyType.generated.h"

UENUM(BlueprintType)
enum class EViewerPropertyType : uint8
{
	Int,
	Float,
	Bool,
	String,
	Unset,
};

struct TENTACLE_API FEViewerPropertyType
{
	using EnumType = EViewerPropertyType;

	static const inline auto Int = FName(TEXT("int"));
	static const inline auto Float = FName(TEXT("float"));
	static const inline auto Bool = FName(TEXT("bool"));
	static const inline auto String = FName(TEXT("string"));

	static FName
	ToName(const EnumType Value)
	{
		static TMap<EnumType, FName> Map = {
			{EnumType::Int, Int},
			{EnumType::Float, Float},
			{EnumType::Bool, Bool},
			{EnumType::String, String},
		};

		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : "";
	}

	static EnumType
	ToEnum(const FName& Value)
	{
		static TMap<FName, EnumType> Map = {
			{Int, EnumType::Int},
			{Float, EnumType::Float},
			{Bool, EnumType::Bool},
			{String, EnumType::String},
		};

		const auto FindResult = Map.Find(Value);
		return FindResult ? *FindResult : EnumType::Unset;
	}
};
