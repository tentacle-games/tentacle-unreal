// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Json.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StringUtils.generated.h"

USTRUCT(BlueprintType)
struct TENTACLE_API FStringPosition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="String", BlueprintReadWrite)
	int32
	Start = 0;

	UPROPERTY(EditAnywhere, Category="String", BlueprintReadWrite)
	int32
	End = 0;

	void
	SetFromJson(const FJsonObjectPtr& Json)
	{
		jsonField(int32, Start, Json, "start");
		jsonField(int32, End, Json, "end");
	}
};

UCLASS()
class TENTACLE_API UStringUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="String Utils")
	static int32
	CountOccurences(const FString& Haystack, const FString& Needle);

	UFUNCTION(BlueprintPure, Category="String Utils")
	static FString
	FindClosestMatch(const TArray<FString>& Options, const FString& Input);

	UFUNCTION(BlueprintPure, Category="String Utils")
	static FName
	FindClosestMatchName(const TArray<FName>& Options, const FName& Input);

	UFUNCTION(BlueprintPure, Category="String Utils")
	static int32
	LevenshteinDistance(const FString& Source, const FString& Target);
};
