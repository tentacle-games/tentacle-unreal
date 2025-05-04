// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomControlEvent.generated.h"

UENUM()
enum class ECustomControlEventType : uint8
{
	Click,
	MouseDown,
	MouseUp,
	ValueChange,
	Unknown,
};

struct TENTACLE_API FECustomControlEventType
{
	using EnumType = ECustomControlEventType;

	static const inline auto Click = FName("Click");
	static const inline auto MouseDown = FName("MouseDown");
	static const inline auto MouseUp = FName("MouseUp");
	static const inline auto ValueChange = FName("ValueChange");

	static EnumType
	ToEnum(const FName& Name)
	{
		static TMap<FName, EnumType> Map = {
			{Click, EnumType::Click},
			{MouseDown, EnumType::MouseDown},
			{MouseUp, EnumType::MouseUp},
			{ValueChange, EnumType::ValueChange},
		};
		const EnumType* FindResult = Map.Find(Name);
		return FindResult ? *FindResult : EnumType::Unknown;
	}

	static FName
	ToName(const EnumType Value)
	{
		static TMap<EnumType, FName> Map = {
			{EnumType::Click, Click},
			{EnumType::MouseDown, MouseDown},
			{EnumType::MouseUp, MouseUp},
			{EnumType::ValueChange, ValueChange},
		};
		const FName* FindResult = Map.Find(Value);
		return FindResult ? *FindResult : "";
	}
};
