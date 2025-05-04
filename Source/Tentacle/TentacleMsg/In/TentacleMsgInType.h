// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

UENUM()
enum class ETentacleMsgInType : uint8
{
	CustomControls_ControlEvent,
	CustomControls_Initialize,
	CustomEvents_Event,
	Stream_ChatJoin,
	Stream_ChatMessage,
	Stream_Event,
	Unknown,
};

struct TENTACLE_API FETentacleMsgInType
{
	using EnumType = ETentacleMsgInType;

	static const inline auto CustomControls_ControlEvent = FName("CustomControls_ControlEvent");
	static const inline auto CustomControls_Initialize = FName("CustomControls_Initialize");
	static const inline auto CustomEvents_Event = FName("CustomEvents_Event");
	static const inline auto Stream_ChatJoin = FName("Stream_ChatJoin");
	static const inline auto Stream_ChatMessage = FName("Stream_ChatMessage");
	static const inline auto Stream_Event = FName("Stream_Event");

	static EnumType
	ToEnum(const FName& Name)
	{
		static TMap<FName, EnumType> Map = {
			{CustomControls_ControlEvent, EnumType::CustomControls_ControlEvent},
			{CustomControls_Initialize, EnumType::CustomControls_Initialize},
			{CustomEvents_Event, EnumType::CustomEvents_Event},
			{Stream_ChatJoin, EnumType::Stream_ChatJoin},
			{Stream_ChatMessage, EnumType::Stream_ChatMessage},
			{Stream_Event, EnumType::Stream_Event},
		};
		const auto FindResult = Map.Find(Name);
		return FindResult ? *FindResult : EnumType::Unknown;
	}

	static FName
	ToName(const EnumType Value)
	{
		static TMap<EnumType, FName> Map = {
			{EnumType::CustomControls_ControlEvent, CustomControls_ControlEvent},
			{EnumType::CustomControls_Initialize, CustomControls_Initialize},
			{EnumType::CustomEvents_Event, CustomEvents_Event},
			{EnumType::Stream_ChatJoin, Stream_ChatJoin},
			{EnumType::Stream_ChatMessage, Stream_ChatMessage},
			{EnumType::Stream_Event, Stream_Event},
		};
		return Map.FindRef(Value);
	}
};
