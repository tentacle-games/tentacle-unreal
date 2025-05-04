// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Common.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Settings/TentacleSettings.h"
#include "Tentacle/Subsystems/Telemetry/TentacleSubsystem_Telemetry.h"

DEFINE_LOG_CATEGORY(LogCommon)

ATentacle*
UCommon::GetTentacle()
{
	if (IsValid(GEngine->GameViewport))
	{
		const auto World = GEngine->GameViewport->GetWorld();
		if (IsValid(World))
			return ATentacle::Get(World);
	}
	return nullptr;
}

void
UCommon::LogDebug(const FString& Message)
{
	UE_LOG(LogCommon, Verbose, TEXT("%s"), *Message);

	const auto Tentacle = GetTentacle();
	if (IsValid(Tentacle) && UTentacleSettings::Get().bTelemetryEnabled)
		Tentacle->Telemetry->Debug(Message);
}

void
UCommon::LogInfo(const FString& Message)
{
	UE_LOG(LogCommon, Display, TEXT("%s"), *Message);

	const auto Tentacle = GetTentacle();
	if (IsValid(Tentacle) && UTentacleSettings::Get().bTelemetryEnabled)
		Tentacle->Telemetry->Info(Message);
}

void
UCommon::LogWarn(const FString& Message)
{
	UE_LOG(LogCommon, Warning, TEXT("%s"), *Message);

	const auto Tentacle = GetTentacle();
	if (IsValid(Tentacle) && UTentacleSettings::Get().bTelemetryEnabled)
		Tentacle->Telemetry->Warn(Message);
}

void
UCommon::LogError(const FString& Message)
{
	UE_LOG(LogCommon, Error, TEXT("%s"), *Message);

	const auto Tentacle = GetTentacle();
	if (IsValid(Tentacle) && UTentacleSettings::Get().bTelemetryEnabled)
		Tentacle->Telemetry->Error(Message);
}

void
UCommon::Debug(const FString& Message)
{
	LogDebug(Message);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::White, Message);
}

void
UCommon::Info(const FString& Message)
{
	LogInfo(Message);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Cyan, Message);
}

void
UCommon::Warn(const FString& Message)
{
	LogInfo(Message);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Yellow, Message);
}

void
UCommon::Error(const FString& Message)
{
	LogInfo(Message);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30.0f, FColor::Red, Message);
}

void
UCommon::HandleAssert(const FString& File, const int32 Line, const FString& Message)
{
	const auto ErrorMessage = FString::Format(TEXT("Assert failed: {0}, line {1}, {2}"), {FPaths::GetCleanFilename(File), Line, Message});
	Error(ErrorMessage);
}

void
UCommon::SendGameplayEventToActor(AActor* Actor, const FGameplayTag& EventTag)
{
	SendGameplayEventToActor(Actor, EventTag, FGameplayEventData());
}

void
UCommon::SendGameplayEventToActor(AActor* Actor, const FGameplayTag& EventTag, const FGameplayEventData& Payload)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventTag, Payload);
}

FString
UCommon::MakeGuid()
{
	return FGuid::NewGuid().ToString();
}

FString
UCommon::MakeId()
{
	static auto Id = 0;
	return FString::FromInt(Id++);
}

bool
UCommon::IsRunningInEditor()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}
