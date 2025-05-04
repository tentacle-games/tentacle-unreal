// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "Tentacle/Viewer/Viewer.h"
#include "Tentacle/Viewer/ViewerTwitch.h"
#include "ViewerFragment.generated.h"

USTRUCT()
struct TENTACLE_API FViewerFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY()
	FName
	Id;

	UPROPERTY()
	FViewerKick
	Kick;

	UPROPERTY()
	FViewerTwitch
	Twitch;

	FName
	GetId() const { return Id; }

	const FViewerKick&
	GetKick() const { return Kick; }

	const FViewerTwitch&
	GetTwitch() const { return Twitch; }

	void
	SetFromViewer(const UViewer* Viewer)
	{
		Id = Viewer->Id;
		Kick = Viewer->Kick;
		Twitch = Viewer->Twitch;
	}
};
