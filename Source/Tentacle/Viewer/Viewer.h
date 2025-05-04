// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once
#include "Tentacle/Utilities/Json.h"
#include "Tentacle/Viewer/ViewerKick.h"
#include "Tentacle/Viewer/ViewerProperty.h"
#include "Tentacle/Viewer/ViewerTwitch.h"
#include "Viewer.generated.h"

UCLASS(BlueprintType)
class TENTACLE_API UViewer : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPropertiesUpdated, const UViewer*, Viewer);

public:
	UPROPERTY(BlueprintReadOnly, Category="Viewer")
	bool
	bIsMock = false;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FName
	Id;

	UPROPERTY(BlueprintReadOnly, Category="Viewer")
	FViewerKick
	Kick;

	UPROPERTY(BlueprintReadWrite, Category="Viewer")
	FViewerTwitch
	Twitch;

	UPROPERTY(BlueprintReadOnly, Category="Viewer")
	TMap<FName, UViewerProperty*>
	Properties;

	UPROPERTY(BlueprintAssignable, Category="Viewer")
	FOnPropertiesUpdated
	OnPropertiesUpdated;

	UFUNCTION(BlueprintPure, Category="Viewer")
	FString
	GetUserName() const
	{
		if (Twitch.IsValid())
			return Twitch.Name;
		if (Kick.IsValid())
			return Kick.Username;
		return FString::Printf(TEXT("Viewer %s"), *Id.ToString());
	}

	UFUNCTION(BlueprintPure, Category="Viewer")
	FString
	GetDisplayName() const
	{
		if (Twitch.IsValid())
			return Twitch.DisplayName;
		if (Kick.IsValid())
			return Kick.Username;
		return FString::Printf(TEXT("Viewer %s"), *Id.ToString());
	}

	UFUNCTION(BlueprintPure, Category="Viewer")
	FLinearColor
	GetColor() const
	{
		if (Twitch.IsValid())
			return Twitch.Color;
		if (Kick.IsValid())
			return Kick.Color;
		return FLinearColor::White;
	}

	void
	SetFromJson(const FJsonObjectPtr& Data);

	void
	MergeFrom(const UViewer* OtherViewer);

	void
	MergeProperties(const FJsonObjectPtr& PropertiesToMerge);

	void
	MergeProperties(const TMap<FName, UViewerProperty*>& PropertiesToMerge);

	UFUNCTION(BlueprintPure, Category="Viewer")
	int32
	GetIntValue(FName UserAppId, FName Name) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	float
	GetFloatValue(FName UserAppId, FName Name) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	bool
	GetBoolValue(FName UserAppId, FName Name) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	FString
	GetStringValue(FName UserAppId, FName Name) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	UViewerProperty*
	GetProperty(FName UserAppId, FName Name, EViewerPropertyType Type) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	UViewerProperty_Int*
	GetIntProperty(FName UserAppId, FName Name) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	UViewerProperty_Float*
	GetFloatProperty(FName UserAppId, FName Name) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	UViewerProperty_Bool*
	GetBoolProperty(FName UserAppId, FName Name) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	UViewerProperty_String*
	GetStringProperty(FName UserAppId, FName Name) const;

	UFUNCTION(BlueprintPure, Category="Viewer")
	bool
	HasProperty(FName UserAppId, FName Name, EViewerPropertyType Type) const;

	UViewerProperty_Int*
	IncrementInt(FName UserAppId, FName Name, int32 Amount);

	UViewerProperty_Float*
	IncrementFloat(FName UserAppId, FName Name, float Amount);

protected:
	UViewerProperty_Int*
	Local_SetInt(FName UserAppId, FName Name, int32 Value);

	UViewerProperty_Float*
	Local_SetFloat(FName UserAppId, FName Name, float Value);

	UViewerProperty_Bool*
	Local_SetBool(FName UserAppId, FName Name, bool Value);

	UViewerProperty_String*
	Local_SetString(FName UserAppId, FName Name, const FString& Value);

	UViewerProperty_Int*
	Local_IncrementInt(FName UserAppId, FName Name, int32 Amount);

	UViewerProperty_Float*
	Local_IncrementFloat(FName UserAppId, FName Name, float Amount);

public:
	class AViewerController*
	GetViewerController() const;

	class AViewerPawn*
	GetViewerPawn() const;

	template <typename T>
	T*
	GetViewerPawn() const { return Cast<T>(GetViewerPawn()); }
};
