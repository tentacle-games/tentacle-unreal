// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleSettings.h"
#include "Tentacle/Utilities/Common.h"

ETclEnvironment
UTentacleSettings::GetEnvironment()
{
	if (!UCommon::IsRunningInEditor())
		return ETclEnvironment::LiveProduction;

	switch (Get().Environment)
	{
		case ETclEnvironment::LiveDevelopment:
			return ETclEnvironment::LiveDevelopment;
		case ETclEnvironment::LiveProduction:
			return ETclEnvironment::LiveProduction;
		case ETclEnvironment::Local:
		default:
			return ETclEnvironment::Local;
	}
}
