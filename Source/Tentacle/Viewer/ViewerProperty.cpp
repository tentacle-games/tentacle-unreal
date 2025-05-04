// © 2024 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Viewer/ViewerProperty.h"

FName UViewerProperty::GetId() const
{
	return Id(UserAppId, Name, Type);
}

FName UViewerProperty::GetUserAppId() const
{
	return UserAppId;
}

FName UViewerProperty::GetPropertyName() const
{
	return Name;
}

EViewerPropertyType UViewerProperty::GetPropertyType() const
{
	return Type;
}

bool UViewerProperty::IsType(EViewerPropertyType PropertyType) const
{
	return Type == PropertyType;
}

FJsonObjectPtr UViewerProperty::ToJson() const
{
	const FJsonObjectPtr PropertyJson = MakeShareable(new FJsonObject);
	PropertyJson->SetStringField("name", Name.ToString());
	PropertyJson->SetStringField("type", FEViewerPropertyType::ToName(Type).ToString());
	PropertyJson->SetStringField("userAppId", UserAppId.ToString());
	PropertyJson->SetStringField("viewerId", ViewerId.ToString());
	return PropertyJson;
}

void UViewerProperty::FromJson(const FJsonObjectPtr& Data)
{
	jsonField(FName, UserAppId, Data, "userAppId");
	jsonField(FName, Name, Data, "name");
	jsonFieldEnum(EViewerPropertyType, Type, Data, "type");
}

FName UViewerProperty::Id(const FName& UserAppId, const FName& Name, EViewerPropertyType Type)
{
	return FName(*FString::Printf(TEXT("%ls_%ls_%ls"), *UserAppId.ToString(), *Name.ToString(), *FEViewerPropertyType::ToName(Type).ToString()));
}

UViewerProperty_Int* UViewerProperty_Int::New(const FName& UserAppId, const FName& ViewerId, const FName& Name, const int32 Value)
{
	const auto Property = NewObject<UViewerProperty_Int>();
	Property->Name = Name;
	Property->Type = EViewerPropertyType::Int;
	Property->UserAppId = UserAppId;
	Property->Value = Value;
	Property->ViewerId = ViewerId;
	return Property;
}

int32 UViewerProperty_Int::GetValue() const
{
	return Value;
}

void UViewerProperty_Int::SetValue(int32 NewValue)
{
	Value = NewValue;
}

FJsonObjectPtr UViewerProperty_Int::ToJson() const
{
	const auto PropertyJson = Super::ToJson();
	PropertyJson->SetNumberField("value", Value);
	return PropertyJson;
}

void UViewerProperty_Int::FromJson(const FJsonObjectPtr& Data)
{
	Super::FromJson(Data);
	jsonField(int32, Value, Data, "value");
}

UViewerProperty_Float* UViewerProperty_Float::New(const FName& UserAppId, const FName& ViewerId, const FName& Name, const float Value)
{
	const auto Property = NewObject<UViewerProperty_Float>();
	Property->Name = Name;
	Property->Type = EViewerPropertyType::Float;
	Property->UserAppId = UserAppId;
	Property->Value = Value;
	Property->ViewerId = ViewerId;
	return Property;
}

float UViewerProperty_Float::GetValue() const
{
	return Value;
}

void UViewerProperty_Float::SetValue(float NewValue)
{
	Value = NewValue;
}

FJsonObjectPtr UViewerProperty_Float::ToJson() const
{
	const auto PropertyJson = Super::ToJson();
	PropertyJson->SetNumberField("value", Value);
	return PropertyJson;
}

void UViewerProperty_Float::FromJson(const FJsonObjectPtr& Data)
{
	Super::FromJson(Data);
	jsonField(float, Value, Data, "value");
}

UViewerProperty_Bool* UViewerProperty_Bool::New(const FName& UserAppId, const FName& ViewerId, const FName& Name, const bool Value)
{
	const auto Property = NewObject<UViewerProperty_Bool>();
	Property->Name = Name;
	Property->Type = EViewerPropertyType::Bool;
	Property->UserAppId = UserAppId;
	Property->Value = Value;
	Property->ViewerId = ViewerId;
	return Property;
}

bool UViewerProperty_Bool::GetValue() const
{
	return Value;
}

void UViewerProperty_Bool::SetValue(bool NewValue)
{
	Value = NewValue;
}

FJsonObjectPtr UViewerProperty_Bool::ToJson() const
{
	const auto PropertyJson = Super::ToJson();
	PropertyJson->SetBoolField("value", Value);
	return PropertyJson;
}

void UViewerProperty_Bool::FromJson(const FJsonObjectPtr& Data)
{
	Super::FromJson(Data);
	jsonField(bool, Value, Data, "value");
}

UViewerProperty_String* UViewerProperty_String::New(const FName& UserAppId, const FName& ViewerId, const FName& Name, const FString& Value)
{
	const auto Property = NewObject<UViewerProperty_String>();
	Property->Name = Name;
	Property->Type = EViewerPropertyType::String;
	Property->UserAppId = UserAppId;
	Property->Value = Value;
	Property->ViewerId = ViewerId;
	return Property;
}

FString UViewerProperty_String::GetValue() const
{
	return Value;
}

void UViewerProperty_String::SetValue(FString NewValue)
{
	Value = NewValue;
}

FJsonObjectPtr UViewerProperty_String::ToJson() const
{
	const auto PropertyJson = Super::ToJson();
	PropertyJson->SetStringField("value", Value);
	return PropertyJson;
}

void UViewerProperty_String::FromJson(const FJsonObjectPtr& Data)
{
	Super::FromJson(Data);
	jsonField(FString, Value, Data, "value");
}

UViewerProperty* UViewerPropertyUtils::NewFromJson(const FJsonObjectPtr& Data)
{
	jsonFieldEnumVar(EViewerPropertyType, Type, Data, "type");
	jsonFieldVar(FName, UserAppId, Data, "userAppId");
	jsonFieldVar(FName, ViewerId, Data, "viewerId");
	jsonFieldVar(FName, Name, Data, "name");

	switch (Type)
	{
	case EViewerPropertyType::Int:
		{
			int64 Value = 0;
			jsonField(int32, Value, Data, "value");
			return UViewerProperty_Int::New(UserAppId, ViewerId, Name, Value);
		}
	case EViewerPropertyType::Float:
		{
			double Value = 0;
			jsonField(float, Value, Data, "value");
			return UViewerProperty_Float::New(UserAppId, ViewerId, Name, Value);
		}
	case EViewerPropertyType::Bool:
		{
			auto Value = false;
			jsonField(bool, Value, Data, "value");
			return UViewerProperty_Bool::New(UserAppId, ViewerId, Name, Value);
		}
	case EViewerPropertyType::String:
		{
			FString Value;
			jsonField(FString, Value, Data, "value");
			return UViewerProperty_String::New(UserAppId, ViewerId, Name, Value);
		}
	default:
		softAssertMsgR(false, FString::Printf(TEXT("Unknown property type: %d"), Type), nullptr);
	}
}
