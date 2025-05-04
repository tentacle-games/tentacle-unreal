// © 2024 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleModule.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "Modules/ModuleManager.h"
#include "Settings/TentacleSettings.h"
#endif

#define LOCTEXT_NAMESPACE "FTentacleModule"

DEFINE_LOG_CATEGORY(LogTentacle)

void FTentacleModule::StartupModule()
{
	UE_LOG(LogTentacle, Log, TEXT("StartupModule"));

	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FTentacleModule::HandlePostEngineInit);
}

void FTentacleModule::ShutdownModule()
{
	UE_LOG(LogTentacle, Log, TEXT("ShutdownModule"));

	FCoreDelegates::OnPostEngineInit.RemoveAll(this);

#if WITH_EDITOR
	// Remove custom settings
	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Tentacle");

		if (const auto PropertyModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor"))
			PropertyModule->UnregisterCustomClassLayout(UTentacleSettings::StaticClass()->GetFName());
	}
#endif
}

void FTentacleModule::HandlePostEngineInit()
{
	UE_LOG(LogTentacle, Log, TEXT("OnPostEngineInit"));

#if WITH_EDITOR
	// Register custom settings to appear in the project settings
	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project", "Plugins", "Tentacle",
			LOCTEXT("TentacleCommentsName", "Tentacle"),
			LOCTEXT("TentacleNameDesc", "Configure the Tentacle plugin"),
			GetMutableDefault<UTentacleSettings>()
		);
	}
#endif
}

IMPLEMENT_MODULE(FTentacleModule, Tentacle)
