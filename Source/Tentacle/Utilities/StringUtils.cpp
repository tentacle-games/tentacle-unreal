// © 2023 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle/Utilities/StringUtils.h"

int32 UStringUtils::CountOccurences(const FString& Haystack, const FString& Needle)
{
	auto Count = 0;
	auto StartPosition = 0;

	while (true)
	{
		const auto FoundPosition = Haystack.Find(Needle, ESearchCase::IgnoreCase, ESearchDir::FromStart, StartPosition);
		if (FoundPosition == INDEX_NONE)
			break;

		Count++;
		StartPosition = FoundPosition + Needle.Len();
	}

	return Count;
}

FString UStringUtils::FindClosestMatch(const TArray<FString>& Options, const FString& Input)
{
	auto ClosestMatch = FString();
	auto MinDistance = TNumericLimits<int32>::Max();

	for (const auto& Option : Options)
	{
		const auto Distance = LevenshteinDistance(Input, Option);
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestMatch = Option;
		}
	}

	return ClosestMatch;
}

FName UStringUtils::FindClosestMatchName(const TArray<FName>& Options, const FName& Input)
{
	auto OptionsStrings = TArray<FString>();
	for (const auto& Option : Options)
		OptionsStrings.Add(Option.ToString());

	return FName(FindClosestMatch(OptionsStrings, Input.ToString()));
}

int32 UStringUtils::LevenshteinDistance(const FString& Source, const FString& Target)
{
	const auto SourceLength = Source.Len();
	const auto TargetLength = Target.Len();

	// Create a DP table with (SourceLength + 1) rows and (TargetLength + 1) columns
	auto DP = TArray<TArray<int32>>();
	DP.SetNum(SourceLength + 1);

	// Initialize the first column of each row
	for (auto i = 0; i <= SourceLength; ++i)
	{
		DP[i].SetNum(TargetLength + 1);
		DP[i][0] = i; // Cost of transforming the first i characters of Source to an empty string
	}

	// Initialize the first row of each column
	for (auto j = 0; j <= TargetLength; ++j)
		DP[0][j] = j; // Cost of transforming an empty string to the first j characters of Target

	// Fill the DP table
	for (auto i = 1; i <= SourceLength; ++i)
	{
		for (auto j = 1; j <= TargetLength; ++j)
		{
			// Cost of substitution (0 if the characters are the same, 1 if they are different)
			const auto Cost = (Source[i - 1] == Target[j - 1]) ? 0 : 1;
			DP[i][j] = FMath::Min3(
				DP[i - 1][j] + 1,		// Deletion
				DP[i][j - 1] + 1,		// Insertion
				DP[i - 1][j - 1] + Cost // Substitution
			);
		}
	}

	// The last cell of the table contains the Levenshtein distance
	return DP[SourceLength][TargetLength];
}
