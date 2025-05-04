// © 2023 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Viewer/Viewer.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Subsystems/Api/TentacleSubsystem_Api.h"
#include "Tentacle/Utilities/Common.h"
#include "Tentacle/Viewer/ViewerController.h"
#include "Tentacle/Viewer/ViewerPawn.h"
#include "Tentacle/Viewer/ViewerProperty.h"

void UViewer::SetFromJson(const FJsonObjectPtr& Data)
{
	softAssert(Data.IsValid());

	jsonField(FName, Id, Data, "id");

	FJsonObjectPtr KickJson;
	jsonFieldOptional(FJsonObjectPtr, KickJson, Data, "kick");
	if (KickJson.IsValid())
		Kick.SetFromJson(KickJson);

	FJsonObjectPtr TwitchJson;
	jsonFieldOptional(FJsonObjectPtr, TwitchJson, Data, "twitch");
	if (TwitchJson.IsValid())
		Twitch.SetFromJson(TwitchJson);

	FJsonObjectPtr PropertiesJson;
	jsonFieldOptional(FJsonObjectPtr, PropertiesJson, Data, "properties");
	if (PropertiesJson.IsValid())
		MergeProperties(PropertiesJson);
}

void UViewer::MergeFrom(const UViewer* OtherViewer)
{
	softAssert(OtherViewer);
	Id = OtherViewer->Id;
	Twitch = OtherViewer->Twitch;
	MergeProperties(OtherViewer->Properties);
}

void UViewer::MergeProperties(const FJsonObjectPtr& PropertiesToMerge)
{
	if (!PropertiesToMerge.IsValid())
		return;

	const auto Values = PropertiesToMerge->Values;
	if (Values.Num() == 0)
		return;

	for (const auto& PropertyEntry : Values)
	{
		auto PropertyJson = PropertyEntry.Value->AsObject();
		auto Property = UViewerPropertyUtils::NewFromJson(PropertyJson);
		Properties.Add(Property->GetId(), Property);
	}

	OnPropertiesUpdated.Broadcast(this);
}

void UViewer::MergeProperties(const TMap<FName, UViewerProperty*>& PropertiesToMerge)
{
	if (PropertiesToMerge.Num() == 0)
		return;

	Properties.Append(PropertiesToMerge);
	OnPropertiesUpdated.Broadcast(this);
}

int32 UViewer::GetIntValue(const FName UserAppId, const FName Name) const
{
	const auto Property = GetIntProperty(UserAppId, Name);
	return IsValid(Property) ? Property->GetValue() : 0;
}

float UViewer::GetFloatValue(const FName UserAppId, const FName Name) const
{
	const auto Property = GetFloatProperty(UserAppId, Name);
	return IsValid(Property) ? Property->GetValue() : 0;
}

bool UViewer::GetBoolValue(const FName UserAppId, const FName Name) const
{
	const auto Property = GetBoolProperty(UserAppId, Name);
	return IsValid(Property) ? Property->GetValue() : false;
}

FString UViewer::GetStringValue(const FName UserAppId, const FName Name) const
{
	const auto Property = GetStringProperty(UserAppId, Name);
	return IsValid(Property) ? Property->GetValue() : "";
}

UViewerProperty* UViewer::GetProperty(const FName UserAppId, const FName Name, EViewerPropertyType Type) const
{
	return Properties.FindRef(UViewerProperty::Id(UserAppId, Name, Type));
}

UViewerProperty_Int* UViewer::GetIntProperty(const FName UserAppId, const FName Name) const
{
	const auto Property = GetProperty(UserAppId, Name, EViewerPropertyType::Int);
	if (!IsValid(Property))
		return nullptr;

	const auto PropertyInt = Cast<UViewerProperty_Int>(Property);
	softAssertMsgR(IsValid(Property), *FString::Format(TEXT("Property {0} is not of type int"), { Name.ToString() }), nullptr);
	return PropertyInt;
}

UViewerProperty_Float* UViewer::GetFloatProperty(const FName UserAppId, const FName Name) const
{
	const auto Property = GetProperty(UserAppId, Name, EViewerPropertyType::Float);
	if (!IsValid(Property))
		return nullptr;

	const auto PropertyFloat = Cast<UViewerProperty_Float>(Property);
	softAssertMsgR(IsValid(Property), *FString::Format(TEXT("Property {0} is not of type float"), { Name.ToString() }), nullptr);
	return PropertyFloat;
}

UViewerProperty_Bool* UViewer::GetBoolProperty(const FName UserAppId, const FName Name) const
{
	const auto Property = GetProperty(UserAppId, Name, EViewerPropertyType::Bool);
	if (!IsValid(Property))
		return nullptr;

	const auto PropertyBool = Cast<UViewerProperty_Bool>(Property);
	softAssertMsgR(IsValid(Property), *FString::Format(TEXT("Property {0} is not of type bool"), { Name.ToString() }), nullptr);
	return PropertyBool;
}

UViewerProperty_String* UViewer::GetStringProperty(const FName UserAppId, const FName Name) const
{
	const auto Property = GetProperty(UserAppId, Name, EViewerPropertyType::String);
	if (!IsValid(Property))
		return nullptr;

	const auto PropertyString = Cast<UViewerProperty_String>(Property);
	softAssertMsgR(IsValid(Property), *FString::Format(TEXT("Property {0} is not of type string"), { Name.ToString() }), nullptr);
	return PropertyString;
}

bool UViewer::HasProperty(const FName UserAppId, const FName Name, EViewerPropertyType Type) const
{
	return Properties.Contains(UViewerProperty::Id(UserAppId, Name, Type));
}

UViewerProperty_Int* UViewer::Local_SetInt(const FName UserAppId, const FName Name, int32 Value)
{
	auto Property = GetIntProperty(UserAppId, Name);
	if (!IsValid(Property))
	{
		Property = UViewerProperty_Int::New(UserAppId, Id, Name, Value);
		Properties.Add(Property->GetId(), Property);
	}

	Property->SetValue(Value);
	OnPropertiesUpdated.Broadcast(this);

	return Property;
}

UViewerProperty_Float* UViewer::Local_SetFloat(const FName UserAppId, const FName Name, float Value)
{
	auto Property = GetFloatProperty(UserAppId, Name);
	if (!IsValid(Property))
	{
		Property = UViewerProperty_Float::New(UserAppId, Id, Name, Value);
		Properties.Add(Property->GetId(), Property);
	}

	Property->SetValue(Value);
	OnPropertiesUpdated.Broadcast(this);

	return Property;
}

UViewerProperty_Bool* UViewer::Local_SetBool(const FName UserAppId, const FName Name, bool Value)
{
	auto Property = GetBoolProperty(UserAppId, Name);
	if (!IsValid(Property))
	{
		Property = UViewerProperty_Bool::New(UserAppId, Id, Name, Value);
		Properties.Add(Property->GetId(), Property);
	}

	Property->SetValue(Value);
	OnPropertiesUpdated.Broadcast(this);

	return Property;
}

UViewerProperty_String* UViewer::Local_SetString(const FName UserAppId, const FName Name, const FString& Value)
{
	auto Property = GetStringProperty(UserAppId, Name);
	if (!IsValid(Property))
	{
		Property = UViewerProperty_String::New(UserAppId, Id, Name, Value);
		Properties.Add(Property->GetId(), Property);
	}

	Property->SetValue(Value);
	OnPropertiesUpdated.Broadcast(this);

	return Property;
}

UViewerProperty_Int* UViewer::Local_IncrementInt(const FName UserAppId, const FName Name, int32 Amount)
{
	auto Property = GetIntProperty(UserAppId, Name);
	if (!IsValid(Property))
	{
		Property = UViewerProperty_Int::New(UserAppId, Id, Name, 0);
		Properties.Add(Property->GetId(), Property);
	}

	Property->SetValue(Property->GetValue() + Amount);
	OnPropertiesUpdated.Broadcast(this);

	return Property;
}

UViewerProperty_Float* UViewer::Local_IncrementFloat(const FName UserAppId, const FName Name, float Amount)
{
	auto Property = GetFloatProperty(UserAppId, Name);
	if (!IsValid(Property))
	{
		Property = UViewerProperty_Float::New(UserAppId, Id, Name, 0);
		Properties.Add(Property->GetId(), Property);
	}

	Property->SetValue(Property->GetValue() + Amount);
	OnPropertiesUpdated.Broadcast(this);

	return Property;
}

UViewerProperty_Int* UViewer::IncrementInt(const FName UserAppId, const FName Name, int32 Amount)
{
	const auto Property = Local_IncrementInt(UserAppId, Name, Amount);
	ATentacle::Get(this)->Api->ViewerProperty_Set(Property);
	return Property;
}

UViewerProperty_Float* UViewer::IncrementFloat(const FName UserAppId, const FName Name, float Amount)
{
	const auto Property = Local_IncrementFloat(UserAppId, Name, Amount);
	ATentacle::Get(this)->Api->ViewerProperty_Set(Property);
	return Property;
}

AViewerController* UViewer::GetViewerController() const
{
	const auto ViewerController = ATentacle::Get(this)->GetViewerController(Id);
	softAssertMsgR(IsValid(ViewerController), *FString::Format(TEXT("ViewerController for {0} not found"), { Id.ToString() }), nullptr);
	return ViewerController;
}

AViewerPawn* UViewer::GetViewerPawn() const
{
	const auto ViewerPawn = ATentacle::Get(this)->GetViewerPawn(Id);
	softAssertMsgR(IsValid(ViewerPawn), *FString::Format(TEXT("ViewerPawn for {0} not found"), { Id.ToString() }), nullptr);
	return ViewerPawn;
}
