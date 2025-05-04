// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "HttpFwd.h"
#include "Components/ActorComponent.h"
#include "Tentacle/Utilities/Json.h"
#include "TentacleSubsystem_Api.generated.h"

enum class EOrderDirection : uint8;
enum class EViewerPropertyType : uint8;

using RequestCompleteCallback = TFunction<void(
	const FString& Error,
	const FJsonObjectPtr& Data,
	const FHttpResponsePtr& Response,
	const FHttpRequestPtr& Request
)>;
using HttpRequest = TSharedRef<IHttpRequest>;

UCLASS()
class TENTACLE_API UTentacleSubsystem_Api : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE_FourParams(FTwitchSubathonSubsCompleteDelegate, const FString&, Error, int32, Count, int32, Goal, float, GoalProgress);
	DECLARE_DYNAMIC_DELEGATE_FourParams(FTwitchSubathonGiftedSubsCompleteDelegate, const FString&, Error, int32, Count, int32, Goal, float, GoalProgress);
	DECLARE_DYNAMIC_DELEGATE_FourParams(FTwitchSubathonDonationsCompleteDelegate, const FString&, Error, float, Dollars, float, Goal, float, GoalProgress);

	bool
	bIsShuttingDown;

public:
	UTentacleSubsystem_Api();

	virtual void
	BeginDestroy() override;

	// TODO: For ViewerProperty_Set requests we should debounce and aggregate the viewers/values for batching.

	UFUNCTION(BlueprintCallable, Category="Tentacle API")
	void
	BP_Twitch_Subathon_Subs(FTwitchSubathonSubsCompleteDelegate OnComplete)
	{
		Twitch_Subathon_Subs(
			[OnComplete](const FString& Error, int32 Count, int32 Goal, float GoalProgress)
			{
				OnComplete.ExecuteIfBound(Error, Count, Goal, GoalProgress);
			}
		);
	}

	UFUNCTION(BlueprintCallable, Category="Tentacle API")
	void
	BP_Twitch_Subathon_GiftedSubs(FTwitchSubathonGiftedSubsCompleteDelegate OnComplete)
	{
		Twitch_Subathon_GiftedSubs(
			[OnComplete](const FString& Error, int32 Count, int32 Goal, float GoalProgress)
			{
				OnComplete.ExecuteIfBound(Error, Count, Goal, GoalProgress);
			}
		);
	}

	UFUNCTION(BlueprintCallable, Category="Tentacle API")
	void
	BP_Twitch_Subathon_Donations(FTwitchSubathonDonationsCompleteDelegate OnComplete)
	{
		Twitch_Subathon_Donations(
			[OnComplete](const FString& Error, float Dollars, float Goal, float GoalProgress)
			{
				OnComplete.ExecuteIfBound(Error, Dollars, Goal, GoalProgress);
			}
		);
	}

	void
	Twitch_Subathon_Subs(const TFunction<void(const FString& Error, int32 Count, int32 Goal, float GoalProgress)>& OnComplete);

	void
	Twitch_Subathon_GiftedSubs(const TFunction<void(const FString& Error, int32 Count, int32 Goal, float GoalProgress)>& OnComplete);

	void
	Twitch_Subathon_Donations(const TFunction<void(const FString& Error, float Total, float Goal, float GoalProgress)>& OnComplete);

	void
	User_Apps(const TFunction<void(const FString& Error, const TArray<struct FUserApp>& UserApps)>& OnComplete);

	void
	ViewerProperty_Set(const class UViewerProperty* Property, const TFunction<void(const FString& Error)>& OnComplete = {});

	void
	Viewers_GetByProperty(
		const FName& UserAppId,
		const FName& Name,
		EViewerPropertyType Type,
		EOrderDirection OrderDirection,
		int32 Take,
		const TFunction<void(const FString& Error, TArray<UViewer*>& Viewers)>& OnComplete
	);

protected:
	HttpRequest
	Post(
		const FString& Path,
		const TArray<TTuple<FString, FString>>& QueryParams,
		const FJsonObjectPtr& Body,
		const RequestCompleteCallback& OnComplete
	);

	HttpRequest
	Get(
		const FString& Path,
		const TArray<TTuple<FString, FString>>& QueryParams,
		const RequestCompleteCallback& OnComplete
	);

	HttpRequest
	CreateRequest(const FString& Method, const FString& Path, const TArray<TTuple<FString, FString>>& QueryParams);

	static bool
	TryGetData(const FHttpRequestPtr& Request, const FHttpResponsePtr& Response, bool bSuccess, FJsonObjectPtr& OutData, FString& OutError);

	static FString
	BuildUrl(const FString& Path, const TArray<TTuple<FString, FString>>& QueryParams);

	static FString
	GetAccessToken();

	static FString
	BuildAuthorization();
};
