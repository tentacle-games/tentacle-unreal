// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Tentacle/Utilities/Common.h"
#include "Json.generated.h"

using FJsonObjectPtr = TSharedPtr<FJsonObject>;
using FJsonValuePtr = TSharedPtr<FJsonValue>;

template <typename tKey, typename tValue>
using JsonMapCallback = TFunction<TTuple<FString, FJsonValuePtr>(const tKey&, const tValue&)>;

template <typename T>
concept IsValidType = std::disjunction_v<
	std::is_same<T, bool>,
	std::is_same<T, int32>,
	std::is_same<T, int64>,
	std::is_same<T, float>,
	std::is_same<T, double>,
	std::is_same<T, FString>,
	std::is_same<T, FJsonObjectPtr>,
	std::is_same<T, FName>,
	std::is_same<T, FDateTime>,
	std::is_same<T, FLinearColor>,
	std::is_same<T, TArray<bool>>,
	std::is_same<T, TArray<int32>>,
	std::is_same<T, TArray<int64>>,
	std::is_same<T, TArray<float>>,
	std::is_same<T, TArray<double>>,
	std::is_same<T, TArray<FString>>,
	std::is_same<T, TArray<FJsonObjectPtr>>,
	std::is_same<T, TArray<FName>>,
	std::is_same<T, TArray<FDateTime>>,
	std::is_same<T, TArray<FLinearColor>>
>;

UCLASS()
class TENTACLE_API UJson : public UObject
{
	GENERATED_BODY()

public:
	template <typename T>
		requires IsValidType<T>
	static TResult<T>
	ValueNested(const FJsonObjectPtr& Data, const TArray<FString>& Path)
	{
		softAssertR(Path.Num() > 0, FErr("Path is empty"))
		const auto FieldIndex = Path.Num() - 1;
		const auto FieldName = Path[FieldIndex];

		auto CurrentObject = FJsonObjectPtr(Data);
		for (auto i = 0; i < Path.Num(); ++i)
		{
			if (i == FieldIndex)
				return Value<T>(CurrentObject, Path[i]);

			const auto NextObjectFieldName = Path[i];
			const auto NextObjectField = CurrentObject->TryGetField(NextObjectFieldName);
			if (!NextObjectField.IsValid())
				return FErr(FString::Printf(TEXT("Field '%s' not found"), *NextObjectFieldName));

			const FJsonObjectPtr* NextObject;
			if (!NextObjectField->TryGetObject(NextObject))
				return FErr(FString::Printf(TEXT("Field '%s' is not an object"), *NextObjectFieldName));

			CurrentObject = *NextObject;
		}

		return FErr("This line should not be reachable.");
	}

	template <typename T>
		requires IsValidType<T>
	static TResult<T>
	Value(const FJsonObjectPtr& Data, const FString& FieldName)
	{
		const auto Field = Data->TryGetField(FieldName);
		if (!Field.IsValid())
			return FErr(FString::Printf(TEXT("Field '%s' not found"), *FieldName));

		T Value;
		if (!TryGetArgumentType(Field, Value))
			return FErr(FString::Printf(TEXT("Field '%s' type is invalid"), *FieldName));

		return Value;
	}

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, bool& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, int32& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, int64& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, float& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, double& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, FString& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, FJsonObjectPtr& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, FName& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, FDateTime& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, FLinearColor& OutValue);

	// TODO: Reconsider how we handle arrays. We should probably only get an array of FJsonValuePtrs.
	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<bool>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<int32>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<int64>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<float>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<double>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<FString>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<FJsonObjectPtr>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<FName>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<FDateTime>& OutValue);

	static bool
	TryGetArgumentType(const FJsonValuePtr& Field, TArray<FLinearColor>& OutValue);

	static TArray<FJsonValuePtr>
	Array(const TArray<bool>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<int32>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<int64>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<float>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<double>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<FString>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<FJsonObjectPtr>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<FName>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<FDateTime>& Array);

	static TArray<FJsonValuePtr>
	Array(const TArray<FLinearColor>& Array);

	static FJsonObjectPtr
	Map(const TMap<FName, FString>& Map);

	template <typename MapType, typename CallbackType>
	static auto
	MapValues(const MapType& Map, CallbackType Callback) -> FJsonObjectPtr
	{
		using KeyType = typename MapType::KeyType;
		using ValueType = typename MapType::ValueType;
		using ReturnType = std::invoke_result_t<CallbackType, const KeyType&, const ValueType&>;
		static_assert(std::is_same_v<ReturnType, TTuple<FString, FJsonValuePtr>>, "Callback function must return TTuple<FString, FJsonValuePtr>");

		FJsonObjectPtr Json = MakeShareable(new FJsonObject);
		for (const auto& [Key, Value] : Map)
		{
			const auto [JsonKey, JsonValue] = Callback(Key, Value);
			Json->SetField(JsonKey, JsonValue);
		}

		return Json;
	}

	template <typename MapType, typename CallbackType>
	static auto
	MapObjects(const MapType& Map, CallbackType Callback) -> FJsonObjectPtr
	{
		using KeyType = typename MapType::KeyType;
		using ValueType = typename MapType::ValueType;
		using ReturnType = std::invoke_result_t<CallbackType, const KeyType&, const ValueType&>;
		static_assert(std::is_same_v<ReturnType, TTuple<FString, FJsonObjectPtr>>, "Callback function must return TTuple<FString, FJsonObjectPtr>");

		FJsonObjectPtr Json = MakeShareable(new FJsonObject);
		for (const auto& [Key, Value] : Map)
		{
			const auto [JsonKey, JsonObject] = Callback(Key, Value);
			Json->SetField(JsonKey, MakeShareable(new FJsonValueObject(JsonObject)));
		}
		return Json;
	}

	static FString
	Stringify(const FJsonObjectPtr& JsonObject);

	static FString
	Stringify(const TSharedRef<FJsonObject>& JsonObject);

	static FJsonObjectPtr
	Parse(const FString& JsonString);


	template<typename StructType>
	bool ToJsonString(const StructType& InStruct, FString& OutJson, int32 Indent = 0)
	{
		return FJsonObjectConverter::UStructToJsonObjectString(
			StructType::StaticStruct(),
			&InStruct,
			OutJson,
			Indent,
			EPropertyPortFlags::PPF_None
		);
	}

	template<typename StructType>
	bool FromJsonString(const FString& InJson, StructType& OutStruct)
	{
		return FJsonObjectConverter::JsonObjectStringToUStruct(
			InJson,
			&OutStruct,
			EPropertyPortFlags::PPF_None,
			0
		);
	}
};

#define _var(Prefix) _varConcat(Prefix, __LINE__)
#define _varConcat(a, b) _varConcatInner(a, b)
#define _varConcatInner(a, b) a ## b

// Safe getters for Json fields that will log the line number of the error.
// __VA_ARGS__ is a comma-separated path to the field.
#define jsonField(Type, OutValue, Data, ...) \
	const TResult<Type> _var(Result) = UJson::ValueNested<Type>(Data, {__VA_ARGS__}); \
	thruAssertMsg(_var(Result).IsOk(), _var(Result).GetErr().Message); \
	if (_var(Result).IsOk()) \
		OutValue = _var(Result).GetOkValue();

#define jsonFieldVar(Type, OutValue, Data, ...) \
	Type OutValue; \
	jsonField(Type, OutValue, Data, __VA_ARGS__)

#define jsonFieldOptional(Type, OutValue, Data, ...) \
	const TResult<Type> _var(Result) = UJson::ValueNested<Type>(Data, {__VA_ARGS__}); \
	if (_var(Result).IsOk()) \
		OutValue = _var(Result).GetOkValue();

#define jsonFieldOptionalVar(Type, OutValue, Data, ...) \
	Type OutValue; \
	jsonFieldOptional(Type, OutValue, Data, __VA_ARGS__)

// Enum
#define jsonFieldEnum(EnumType, OutValue, Data, ...) \
	FName _var(Value); \
	jsonField(FName, _var(Value), Data, __VA_ARGS__); \
	OutValue = F##EnumType::ToEnum(_var(Value));

#define jsonFieldEnumVar(EnumType, OutValue, Data, ...) \
	EnumType OutValue; \
	jsonFieldEnum(EnumType, OutValue, Data, __VA_ARGS__)

#define jsonFieldEnumOptional(EnumType, OutValue, Data, ...) \
	FName _var(Value); \
	jsonFieldOptional(FName, _var(Value), Data, __VA_ARGS__); \
	if (_var(Value) != NAME_None) \
		OutValue = F##EnumType::ToEnum(_var(Value));

#define jsonFieldEnumOptionalVar(EnumType, OutValue, Data, ...) \
	EnumType OutValue; \
	jsonFieldEnumOptional(EnumType, OutValue, Data, __VA_ARGS__)
