// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "Tentacle.h"
#include "Tentacle/Settings/TentacleSettings.h"
#include "Tentacle/Streamer/StreamerPawn.h"
#include "Tentacle/Subsystems/Api/TentacleSubsystem_Api.h"
#include "Tentacle/Subsystems/CustomControls/TentacleSubsystem_CustomControls.h"
#include "Tentacle/Subsystems/CustomEvents/TentacleSubsystem_CustomEvents.h"
#include "Tentacle/Subsystems/Obs/TentacleSubsystem_Obs.h"
#include "Tentacle/Subsystems/Stream/TentacleSubsystem_Stream.h"
#include "Tentacle/Subsystems/Telemetry/TentacleSubsystem_Telemetry.h"
#include "Tentacle/Subsystems/WebSocket/TentacleSubsystem_WebSocket.h"
#include "Tentacle/TentacleMsg/In/TentacleMsgIn.h"
#include "Tentacle/Utilities/Common.h"
#include "Tentacle/Viewer/Viewer.h"
#include "Tentacle/Viewer/ViewerController.h"
#include "Tentacle/Viewer/ViewerState.h"

ATentacle::ATentacle()
{
	PrimaryActorTick.bCanEverTick = false;

	bDebugLog = false;

	Api = CreateDefaultSubobject<UTentacleSubsystem_Api>("Api");
	CustomControls = CreateDefaultSubobject<UTentacleSubsystem_CustomControls>("CustomControls");
	CustomEvents = CreateDefaultSubobject<UTentacleSubsystem_CustomEvents>("CustomEvents");
	Obs = CreateDefaultSubobject<UTentacleSubsystem_Obs>("Obs");
	Stream = CreateDefaultSubobject<UTentacleSubsystem_Stream>("Stream");
	Telemetry = CreateDefaultSubobject<UTentacleSubsystem_Telemetry>("Telemetry");
	WebSocket = CreateDefaultSubobject<UTentacleSubsystem_WebSocket>("WebSocket");
}

void
ATentacle::BeginPlay()
{
	Super::BeginPlay();

	addDynamicSafe(WebSocket->OnMsgReceived, ATentacle::HandleMsg);

	Telemetry->Start();
	WebSocket->Start();
}

void
ATentacle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Telemetry->Stop();
	WebSocket->Stop();
}

UViewer*
ATentacle::GetViewer(const FName& ViewerId) const
{
	return Viewers.FindRef(ViewerId);
}

AViewerController*
ATentacle::GetViewerController(const FName& ViewerId) const
{
	return ViewerControllers.FindRef(ViewerId);
}

AViewerPawn*
ATentacle::GetViewerPawn(const FName& ViewerId) const
{
	const auto ViewerController = GetViewerController(ViewerId);
	return IsValid(ViewerController) ? ViewerController->GetPawn<AViewerPawn>() : nullptr;
}

TTuple<UViewer*, AViewerPawn*>
ATentacle::UpsertViewer(UViewer* Viewer)
{
	softAssertR(IsValid(Viewer), {})

	// Get the viewer. If it doesn't exist, create it.
	auto OutViewer = GetViewer(Viewer->Id);
	if (IsValid(OutViewer))
		OutViewer->MergeFrom(Viewer); // Merge properties.
	else
	{
		OutViewer = Viewer;

		if (OutViewer->Twitch.Id == UTentacleSettings::Get().StreamerTwitchId)
			OutViewer->bIsMock = true;

		Viewers.Add(OutViewer->Id, OutViewer);
		ViewersByTwitchId.Add(OutViewer->Twitch.Id, OutViewer);
	}

	// Get the viewer pawn. If it doesn't exist, spawn it.
	auto OutViewerPawn = GetViewerPawn(OutViewer->Id);
	if (!IsValid(OutViewerPawn))
	{
		// Spawn viewer controller and pawn.
		const auto ViewerController = UCommon::SpawnActor<AViewerController>(this);
		OutViewerPawn = UCommon::SpawnActor<AViewerPawn>(this);
		ViewerController->Possess(OutViewerPawn);

		// Set viewer state.
		const auto ViewerState = ViewerController->GetPlayerState<AViewerState>();
		softAssertR(IsValid(ViewerState), MakeTuple(nullptr, nullptr))
		ViewerState->Viewer = OutViewer;

		// Add to cache.
		ViewerControllers.Add(OutViewer->Id, ViewerController);
		ViewerControllersByTwitchId.Add(OutViewer->Twitch.Id, ViewerController);

#if WITH_EDITOR
		ViewerController->SetActorLabel(FString::Format(TEXT("{0}_Controller"), {OutViewer->GetDisplayName()}));
		OutViewerPawn->SetActorLabel(FString::Format(TEXT("{0}_Pawn"), {OutViewer->GetDisplayName()}));
#endif
	}

	return MakeTuple(OutViewer, OutViewerPawn);
}

void
ATentacle::DestroyViewer(const FName& ViewerId)
{
	const auto ViewerPawn = GetViewerPawn(ViewerId);
	const auto ViewerController = GetViewerController(ViewerId);

	if (IsValid(ViewerPawn))
		ViewerPawn->Destroy();

	if (IsValid(ViewerController))
		ViewerController->Destroy();

	Viewers.Remove(ViewerId);
	ViewerControllers.Remove(ViewerId);
}

void
ATentacle::DestroyAllViewers()
{
	auto ViewerIds = TArray<FName>();
	Viewers.GetKeys(ViewerIds);

	for (const auto& ViewerId : ViewerIds)
		DestroyViewer(ViewerId);
}

void
ATentacle::HandleMsg(const FString& JsonString)
{
	// Parse string into json.
	const auto Json = UJson::Parse(JsonString);
	softAssert(Json.IsValid());

	const auto Msg = NewObject<UTentacleMsgIn>();
	Msg->SetFromJson(Json);

	switch (Msg->Type)
	{
	case ETentacleMsgInType::CustomControls_ControlEvent:
		return CustomControls->HandleMsg_ControlEvent(Msg);
	case ETentacleMsgInType::CustomControls_Initialize:
		return CustomControls->HandleMsg_Initialize(Msg);

	case ETentacleMsgInType::CustomEvents_Event:
		return CustomEvents->HandleMsg_Event(Msg);

	case ETentacleMsgInType::Stream_ChatJoin:
		return Stream->HandleMsg_ChatJoin(Msg);
	case ETentacleMsgInType::Stream_ChatMessage:
		return Stream->HandleMsg_ChatMessage(Msg);
	case ETentacleMsgInType::Stream_Event:
		return Stream->HandleMsg_Event(Msg);

	default:
		warnF("Received unknown TentacleMsgInType: %s", *FETentacleMsgInType::ToName(Msg->Type).ToString());
	}
}
