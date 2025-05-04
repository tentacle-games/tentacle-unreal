// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "TentacleSubsystem_Api.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Tentacle/Tentacle.h"
#include "Tentacle/Settings/TentacleSettings.h"
#include "Tentacle/User/UserApp.h"
#include "Tentacle/Utilities/OrderDirection.h"
#include "Tentacle/Utilities/Urls.h"
#include "Tentacle/Utilities/ViewerPropertyType.h"
#include "Tentacle/Viewer/Viewer.h"
#include "Tentacle/Viewer/ViewerProperty.h"

UTentacleSubsystem_Api::UTentacleSubsystem_Api()
{
	bIsShuttingDown = false;
}

void
UTentacleSubsystem_Api::BeginDestroy()
{
	UObject::BeginDestroy();

	bIsShuttingDown = true;
}

void
UTentacleSubsystem_Api::Twitch_Subathon_Subs(const TFunction<void(const FString& Error, int32 Count, int32 Goal, float GoalProgress)>& OnComplete)
{
	Get(
		TEXT("twitch/subathon/subs"),
		{},
		[this, OnComplete](const FString& Error, const FJsonObjectPtr& Data, const FHttpResponsePtr&, const FHttpRequestPtr&)
		{
			auto Count = 0;
			auto Goal = 0;
			auto GoalProgress = 0.0f;

			if (Error.IsEmpty() && Data.IsValid())
			{
				jsonField(int32, Count, Data, "count");
				jsonField(int32, Goal, Data, "goal");
				jsonField(float, GoalProgress, Data, "goalProgress");
			}

			if (OnComplete)
				OnComplete(Error, Count, Goal, GoalProgress);
		}
	);
}

void
UTentacleSubsystem_Api::Twitch_Subathon_GiftedSubs(const TFunction<void(const FString& Error, int32 Count, int32 Goal, float GoalProgress)>& OnComplete)
{
	Get(
		TEXT("twitch/subathon/gifted-subs"),
		{},
		[this, OnComplete](const FString& Error, const FJsonObjectPtr& Data, const FHttpResponsePtr&, const FHttpRequestPtr&)
		{
			auto Count = 0;
			auto Goal = 0;
			auto GoalProgress = 0.0f;

			if (Error.IsEmpty() && Data.IsValid())
			{
				jsonField(int32, Count, Data, "count");
				jsonField(int32, Goal, Data, "goal");
				jsonField(float, GoalProgress, Data, "goalProgress");
			}

			if (OnComplete)
				OnComplete(Error, Count, Goal, GoalProgress);
		}
	);
}

void
UTentacleSubsystem_Api::Twitch_Subathon_Donations(const TFunction<void(const FString& Error, float Dollars, float Goal, float GoalProgress)>& OnComplete)
{
	Get(
		TEXT("twitch/subathon/donations"),
		{},
		[this, OnComplete](const FString& Error, const FJsonObjectPtr& Data, const FHttpResponsePtr&, const FHttpRequestPtr&)
		{
			auto Dollars = 0.0f;
			auto Goal = 0.0f;
			auto GoalProgress = 0.0f;

			if (Error.IsEmpty() && Data.IsValid())
			{
				jsonField(float, Dollars, Data, "dollars");
				jsonField(float, Goal, Data, "goal");
				jsonField(float, GoalProgress, Data, "goalProgress");
			}

			if (OnComplete)
				OnComplete(Error, Dollars, Goal, GoalProgress);
		}
	);
}

void
UTentacleSubsystem_Api::User_Apps(const TFunction<void(const FString& Error, const TArray<FUserApp>& UserApps)>& OnComplete)
{
	Get(
		TEXT("user/apps"),
		{},
		[this, OnComplete](const FString& Error, const FJsonObjectPtr& Data, const FHttpResponsePtr&, const FHttpRequestPtr&)
		{
			auto UserApps = TArray<FUserApp>();

			if (Error.IsEmpty() && Data.IsValid())
			{
				jsonFieldVar(TArray<FJsonObjectPtr>, UserAppsJsonArray, Data, "userApps");
				for (const auto& UserAppJson : UserAppsJsonArray)
				{
					auto UserApp = FUserApp();
					jsonField(FName, UserApp.Id, UserAppJson, "id");
					jsonField(FString, UserApp.Name, UserAppJson, "name");
					UserApps.Add(UserApp);
				}
			}

			if (OnComplete)
				OnComplete(Error, UserApps);
		}
	);
}

void
UTentacleSubsystem_Api::ViewerProperty_Set(const UViewerProperty* Property, const TFunction<void(const FString& Error)>& OnComplete)
{
	const FJsonObjectPtr Body = MakeShareable(new FJsonObject);
	Body->SetObjectField("property", Property->ToJson());

	Post(
		TEXT("viewer-property/set"),
		{},
		Body,
		[OnComplete](const FString& Error, const FJsonObjectPtr&, const FHttpResponsePtr&, const FHttpRequestPtr&)
		{
			if (OnComplete)
				OnComplete(Error);
		}
	);
}

void
UTentacleSubsystem_Api::Viewers_GetByProperty(
	const FName& UserAppId,
	const FName& Name,
	EViewerPropertyType Type,
	EOrderDirection OrderDirection,
	int32 Take,
	const TFunction<void(const FString& Error, TArray<UViewer*>& Viewers)>& OnComplete
)
{
	Get(
		TEXT("viewers/get-by-property"),
		{
			{TEXT("orderDirection"), FEOrderDirection::ToName(OrderDirection).ToString()},
			{TEXT("propertyName"), Name.ToString()},
			{TEXT("propertyType"), FEViewerPropertyType::ToName(Type).ToString()},
			{TEXT("take"), FString::FromInt(Take)},
			{TEXT("userAppId"), UserAppId.ToString()},
		},
		[this, OnComplete](const FString& Error, const FJsonObjectPtr& Data, const FHttpResponsePtr&, const FHttpRequestPtr&)
		{
			auto Viewers = TArray<UViewer*>();

			if (Error.IsEmpty() && Data.IsValid())
			{
				jsonFieldVar(TArray<FJsonObjectPtr>, ViewersJsonArray, Data, "viewers")
				for (const auto& ViewerJson : ViewersJsonArray)
				{
					jsonFieldVar(FName, ViewerId, ViewerJson, "id");

					// TODO: Make this a method within Tentacle.
					const auto Tentacle = ATentacle::Get(this);
					softAssert(IsValid(Tentacle))
					auto Viewer = Tentacle->GetViewer(ViewerId);
					if (IsValid(Viewer))
					{
						jsonFieldVar(FJsonObjectPtr, ViewerProperties, ViewerJson, "properties");
						Viewer->MergeProperties(ViewerProperties);
					}
					else
					{
						Viewer = NewObject<UViewer>();
						Viewer->SetFromJson(ViewerJson);
						Viewer = Tentacle->UpsertViewer(Viewer).Get<0>();
					}

					Viewers.Add(Viewer);
				}
			}

			if (OnComplete)
				OnComplete(Error, Viewers);
		}
	);
}

HttpRequest
UTentacleSubsystem_Api::Post(
	const FString& Path,
	const TArray<TTuple<FString, FString>>& QueryParams,
	const FJsonObjectPtr& Body,
	const RequestCompleteCallback& OnComplete
)
{
	const auto NewRequest = CreateRequest(TEXT("POST"), Path, QueryParams);
	NewRequest->SetContentAsString(UJson::Stringify(Body));
	NewRequest->OnProcessRequestComplete().BindLambda(
		[OnComplete, this](const FHttpRequestPtr& Request, const FHttpResponsePtr& Response, bool bSuccess)
		{
			if (bIsShuttingDown)
				return;

			FJsonObjectPtr Data;
			FString Error;

			if (!TryGetData(Request, Response, bSuccess, Data, Error))
				UCommon::LogWarn(Error);

			OnComplete(Error, Data, Response, Request);
		}
	);
	NewRequest->ProcessRequest();
	return NewRequest;
}

HttpRequest
UTentacleSubsystem_Api::Get(
	const FString& Path,
	const TArray<TTuple<FString, FString>>& QueryParams,
	const RequestCompleteCallback& OnComplete
)
{
	const auto NewRequest = CreateRequest(TEXT("GET"), Path, QueryParams);
	NewRequest->OnProcessRequestComplete().BindLambda(
		[OnComplete, this](const FHttpRequestPtr& Request, const FHttpResponsePtr& Response, bool bSuccess)
		{
			if (bIsShuttingDown)
				return;

			FJsonObjectPtr Data;
			FString Error;
			if (!TryGetData(Request, Response, bSuccess, Data, Error))
				UCommon::LogWarn(Error);

			OnComplete(Error, Data, Response, Request);
		}
	);
	NewRequest->ProcessRequest();
	return NewRequest;
}

HttpRequest
UTentacleSubsystem_Api::CreateRequest(const FString& Method, const FString& Path, const TArray<TTuple<FString, FString>>& QueryParams)
{
	const auto Http = &FHttpModule::Get();
	const auto NewRequest = Http->CreateRequest();
	const auto Url = BuildUrl(Path, QueryParams);
	NewRequest->SetVerb(Method);
	NewRequest->SetURL(Url);
	NewRequest->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	NewRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	NewRequest->SetHeader(TEXT("Authorization"), BuildAuthorization());

	UCommon::LogDebug(FString::Printf(TEXT("%s %s"), *Method, *Url));

	return NewRequest;
}

bool
UTentacleSubsystem_Api::TryGetData(
	const FHttpRequestPtr& Request,
	const FHttpResponsePtr& Response,
	bool bSuccess,
	FJsonObjectPtr& OutData,
	FString& OutError
)
{
	if (!bSuccess || !Response.IsValid())
	{
		OutError = FString::Printf(TEXT("Request failed: %s"), *Request->GetURL());
		return false;
	}

	const auto ResponseCode = Response->GetResponseCode();
	if (!EHttpResponseCodes::IsOk(ResponseCode))
	{
		OutError = FString::Printf(TEXT("Request failed (status code %d): %s"), ResponseCode, *Request->GetURL());
		return false;
	}

	OutData = UJson::Parse(Response->GetContentAsString());
	if (!OutData.IsValid())
	{
		OutError = FString::Printf(TEXT("Request failed (invalid json): %s"), *Request->GetURL());
		return false;
	}

	UCommon::LogDebug(FString::Printf(TEXT("Request success (%s) %s"), *Request->GetURL(), *Response->GetContentAsString()));

	return true;
}

FString
UTentacleSubsystem_Api::BuildUrl(const FString& Path, const TArray<TTuple<FString, FString>>& QueryParams)
{
	auto Url = FTclUrls::Api() + Path;

	if (!QueryParams.IsEmpty())
	{
		Url += TEXT("?");

		auto QueryParamStrings = TArray<FString>();
		for (const auto& QueryParam : QueryParams)
			QueryParamStrings.Add(FString::Printf(TEXT("%ls=%ls"), *QueryParam.Get<0>(), *QueryParam.Get<1>()));

		Url += FString::Join(QueryParamStrings, TEXT("&"));
	}

	return Url;
}

FString
UTentacleSubsystem_Api::GetAccessToken()
{
	switch (UTentacleSettings::GetEnvironment())
	{
		case ETclEnvironment::LiveProduction:
			return UTentacleSettings::Get().AccessToken;
		case ETclEnvironment::Local:
		case ETclEnvironment::LiveDevelopment:
		default:
			return UTentacleSettings::Get().DevAccessToken;
	}
}

FString
UTentacleSubsystem_Api::BuildAuthorization()
{
	return FString::Printf(TEXT("Bearer %s"), *GetAccessToken());
}
