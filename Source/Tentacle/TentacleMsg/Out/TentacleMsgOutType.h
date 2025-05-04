// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

UENUM()
enum class ETentacleMsgOutType : uint8
{
	CustomControls_ControlState,
	CustomControls_Initialize,
	CustomControls_RegisterControl,
	CustomControls_UnregisterControl,
	Obs_Call,
	Unknown,
};

struct TENTACLE_API FETentacleMsgOutType
{
	using EnumType = ETentacleMsgOutType;

	static const inline auto CustomControls_ControlState = FName("CustomControls_ControlState");
	static const inline auto CustomControls_Initialize = FName("CustomControls_Initialize");
	static const inline auto CustomControls_RegisterControl = FName("CustomControls_RegisterControl");
	static const inline auto CustomControls_UnregisterControl = FName("CustomControls_UnregisterControl");
	static const inline auto Obs_Call = FName("Obs_Call");

	static EnumType
	ToEnum(const FName& Name)
	{
		static TMap<FName, EnumType> Map = {
			{CustomControls_ControlState, EnumType::CustomControls_ControlState},
			{CustomControls_Initialize, EnumType::CustomControls_Initialize},
			{CustomControls_RegisterControl, EnumType::CustomControls_RegisterControl},
			{CustomControls_UnregisterControl, EnumType::CustomControls_UnregisterControl},
			{Obs_Call, EnumType::Obs_Call},
		};
		const auto FindResult = Map.Find(Name);
		return FindResult ? *FindResult : EnumType::Unknown;
	}

	static FName
	ToName(const EnumType Value)
	{
		static TMap<EnumType, FName> Map = {
			{EnumType::CustomControls_ControlState, CustomControls_ControlState},
			{EnumType::CustomControls_Initialize, CustomControls_Initialize},
			{EnumType::CustomControls_RegisterControl, CustomControls_RegisterControl},
			{EnumType::CustomControls_UnregisterControl, CustomControls_UnregisterControl},
			{EnumType::Obs_Call, Obs_Call},
		};
		return Map.FindRef(Value);
	}
};
