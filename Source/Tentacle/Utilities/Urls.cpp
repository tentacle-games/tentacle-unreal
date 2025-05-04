// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Urls.h"
#include "Tentacle/Settings/TentacleSettings.h"

FString
FTclUrls::Api()
{
	static const auto Local = FString::Printf(TEXT("http://%s:3000/api/"), *FTclHosts::Local);
	static const auto LiveDevelopment = FString::Printf(TEXT("https://%s/api/"), *FTclHosts::LiveDevelopment);
	static const auto LiveProduction = FString::Printf(TEXT("https://%s/api/"), *FTclHosts::LiveProduction);

	switch (UTentacleSettings::GetEnvironment())
	{
	case ETclEnvironment::LiveDevelopment:
		return LiveDevelopment;
	case ETclEnvironment::LiveProduction:
		return LiveProduction;
	case ETclEnvironment::Local:
	default:
		return Local;
	}
}

FString
FTclUrls::LogService()
{
	static const auto Local = FString::Printf(TEXT("ws://%s:5000/logger"), *FTclHosts::Local);
	static const auto LiveDevelopment = FString::Printf(TEXT("ws://%s/logger"), *FTclHosts::LiveDevelopment);
	static const auto LiveProduction = FString::Printf(TEXT("ws://%s/logger"), *FTclHosts::LiveProduction);

	switch (UTentacleSettings::GetEnvironment())
	{
	case ETclEnvironment::LiveDevelopment:
		return LiveDevelopment;
	case ETclEnvironment::LiveProduction:
		return LiveProduction;
	case ETclEnvironment::Local:
	default:
		return Local;
	}
}
