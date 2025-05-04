// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "CustomEvent.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Viewer/Viewer.h"

void
UCustomEvent::SetFromJson(const FJsonObjectPtr& Json)
{
	softAssert(Json.IsValid());

	jsonField(FName, Name, Json, "name");

	FJsonObjectPtr ViewerJson;
	jsonFieldOptional(FJsonObjectPtr, ViewerJson, Json, "viewer");
	if (ViewerJson.IsValid())
	{
		Viewer = NewObject<UViewer>();
		Viewer->SetFromJson(ViewerJson);
	}
}
