// © 2024 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTentacle, Log, All)

class FTentacleModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static FTentacleModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FTentacleModule>("Tentacle");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Tentacle");
	}

private:
	void HandlePostEngineInit();
};
