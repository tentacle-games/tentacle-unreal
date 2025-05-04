// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tentacle/Utilities/Json.h"
#include "Tentacle/Utilities/ViewerPropertyType.h"
#include "ViewerProperty.generated.h"

enum class EViewerPropertyType : uint8;

UCLASS(BlueprintType, Abstract)
class TENTACLE_API UViewerProperty : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName Name;

	UPROPERTY()
	EViewerPropertyType Type = EViewerPropertyType::Unset;

	UPROPERTY()
	FName UserAppId;

	UPROPERTY()
	FName ViewerId;

	UFUNCTION(Category="ViewerProperty", BlueprintPure)
	FName GetId() const;

	UFUNCTION(Category="ViewerProperty", BlueprintPure)
	FName GetUserAppId() const;

	UFUNCTION(Category="ViewerProperty", BlueprintPure)
	FName GetPropertyName() const;

	UFUNCTION(Category="ViewerProperty", BlueprintPure)
	EViewerPropertyType GetPropertyType() const;

	UFUNCTION(Category="ViewerProperty", BlueprintPure)
	bool IsType(EViewerPropertyType PropertyType) const;

	virtual FJsonObjectPtr ToJson() const;
	virtual void FromJson(const FJsonObjectPtr& Data);
	static FName Id(const FName& UserAppId, const FName& Name, EViewerPropertyType Type);
};

UCLASS(BlueprintType)
class TENTACLE_API UViewerProperty_Int : public UViewerProperty
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	int32 Value;

public:
	static UViewerProperty_Int* New(const FName& UserAppId, const FName& ViewerId, const FName& Name, const int32 Value);
	int32 GetValue() const;
	void SetValue(int32 NewValue);
	virtual FJsonObjectPtr ToJson() const override;
	virtual void FromJson(const FJsonObjectPtr& Data) override;
};

UCLASS(BlueprintType)
class TENTACLE_API UViewerProperty_Float : public UViewerProperty
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	float Value;

public:
	static UViewerProperty_Float* New(const FName& UserAppId, const FName& ViewerId, const FName& Name, const float Value);
	float GetValue() const;
	void SetValue(float NewValue);
	virtual FJsonObjectPtr ToJson() const override;
	virtual void FromJson(const FJsonObjectPtr& Data) override;
};

UCLASS(BlueprintType)
class TENTACLE_API UViewerProperty_Bool : public UViewerProperty
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	bool Value;

public:
	static UViewerProperty_Bool* New(const FName& UserAppId, const FName& ViewerId, const FName& Name, const bool Value);
	bool GetValue() const;
	void SetValue(bool NewValue);
	virtual FJsonObjectPtr ToJson() const override;
	virtual void FromJson(const FJsonObjectPtr& Data) override;
};

UCLASS(BlueprintType)
class TENTACLE_API UViewerProperty_String : public UViewerProperty
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FString Value;

public:
	static UViewerProperty_String* New(const FName& UserAppId, const FName& ViewerId, const FName& Name, const FString& Value);
	FString GetValue() const;
	void SetValue(FString NewValue);
	virtual FJsonObjectPtr ToJson() const override;
	virtual void FromJson(const FJsonObjectPtr& Data) override;
};

UCLASS()
class TENTACLE_API UViewerPropertyUtils : public UObject
{
	GENERATED_BODY()

public:
	static UViewerProperty* NewFromJson(const FJsonObjectPtr& Data);
};
