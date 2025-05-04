// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Utilities/Json.h"
#include "JsonObjectWrapper.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, bool& OutValue)
{
	return Field->TryGetBool(OutValue);
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, int32& OutValue)
{
	return Field->TryGetNumber(OutValue);
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, int64& OutValue)
{
	return Field->TryGetNumber(OutValue);
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, float& OutValue)
{
	return Field->TryGetNumber(OutValue);
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, double& OutValue)
{
	return Field->TryGetNumber(OutValue);
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, FString& OutValue)
{
	return Field->TryGetString(OutValue);
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, FJsonObjectPtr& OutValue)
{
	FJsonObjectPtr* JsonObject = nullptr;
	if (Field->TryGetObject(JsonObject))
	{
		OutValue = *JsonObject;
		return true;
	}

	return false;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, FName& OutValue)
{
	FString StringValue;
	if (Field->TryGetString(StringValue))
	{
		OutValue = FName(*StringValue);
		return true;
	}

	return false;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, FDateTime& OutValue)
{
	FString StringValue;
	if (Field->TryGetString(StringValue))
	{
		FDateTime::ParseIso8601(*StringValue, OutValue);
		return true;
	}

	return false;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, FLinearColor& OutValue)
{
	FString StringValue;
	if (Field->TryGetString(StringValue))
	{
		OutValue = FColor::FromHex(StringValue).ReinterpretAsLinear();
		return true;
	}

	return false;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<bool>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		bool BoolValue;
		if (JsonValue->TryGetBool(BoolValue))
			OutValue.Add(BoolValue);
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<int32>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		int32 IntValue;
		if (JsonValue->TryGetNumber(IntValue))
			OutValue.Add(IntValue);
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<int64>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		int64 IntValue;
		if (JsonValue->TryGetNumber(IntValue))
			OutValue.Add(IntValue);
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<float>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		float FloatValue;
		if (JsonValue->TryGetNumber(FloatValue))
			OutValue.Add(FloatValue);
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<double>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		double DoubleValue;
		if (JsonValue->TryGetNumber(DoubleValue))
			OutValue.Add(DoubleValue);
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<FString>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		FString StringValue;
		if (JsonValue->TryGetString(StringValue))
			OutValue.Add(StringValue);
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<FJsonObjectPtr>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		FJsonObjectPtr* JsonObject;
		if (JsonValue->TryGetObject(JsonObject))
			OutValue.Add(*JsonObject);
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<FName>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		FString String;
		if (JsonValue->TryGetString(String))
			OutValue.Add(FName(*String));
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<FDateTime>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		FString String;
		if (JsonValue->TryGetString(String))
		{
			FDateTime DateTime;
			FDateTime::ParseIso8601(*String, DateTime);
			OutValue.Add(DateTime);
		}
	}

	return true;
}

bool
UJson::TryGetArgumentType(const FJsonValuePtr& Field, TArray<FLinearColor>& OutValue)
{
	TArray<FJsonValuePtr>* ArrayJson;
	if (!Field->TryGetArray(ArrayJson))
		return false;

	OutValue.Empty();
	for (const auto& JsonValue : *ArrayJson)
	{
		FString String;
		if (JsonValue->TryGetString(String))
		{
			auto Color = FColor::FromHex(String).ReinterpretAsLinear();
			OutValue.Add(Color);
		}
	}

	return true;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<bool>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueBoolean>(Value));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<int32>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueNumber>(Value));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<int64>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueNumber>(Value));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<float>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueNumber>(Value));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<double>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueNumber>(Value));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<FString>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueString>(Value));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<FJsonObjectPtr>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueObject>(Value));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<FName>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueString>(Value.ToString()));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<FDateTime>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueString>(Value.ToIso8601()));
	return ArrayJson;
}

TArray<FJsonValuePtr>
UJson::Array(const TArray<FLinearColor>& Array)
{
	TArray<FJsonValuePtr> ArrayJson;
	for (const auto& Value : Array)
		ArrayJson.Add(MakeShared<FJsonValueString>(Value.ToFColor(true).ToHex()));
	return ArrayJson;
}

FJsonObjectPtr
UJson::Map(const TMap<FName, FString>& Map)
{
	FJsonObjectPtr Json = MakeShareable(new FJsonObject);
	for (const auto& Entry : Map)
		Json->SetStringField(Entry.Key.ToString(), Entry.Value);
	return Json;
}

FString
UJson::Stringify(const FJsonObjectPtr& JsonObject)
{
	FString OutputString;

	const auto Writer = TJsonWriterFactory<>::Create(&OutputString);
	const auto Success = FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	softAssertMsgR(Success, TEXT("Failed to stringify json object."), FString());

	return OutputString;
}

FString
UJson::Stringify(const TSharedRef<FJsonObject>& JsonObject)
{
	FString OutputString;

	const auto Writer = TJsonWriterFactory<>::Create(&OutputString);
	const auto Success = FJsonSerializer::Serialize(JsonObject, Writer);
	softAssertMsgR(Success, TEXT("Failed to stringify json object."), FString());

	return OutputString;
}

FJsonObjectPtr
UJson::Parse(const FString& JsonString)
{
	FJsonObjectWrapper JsonObjectWrapper;
	softAssertR(JsonObjectWrapper.JsonObjectFromString(JsonString), nullptr);
	return JsonObjectWrapper.JsonObject;
}
