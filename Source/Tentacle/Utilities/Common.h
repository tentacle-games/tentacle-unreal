// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Common.generated.h"

class ATentacle;
class UViewer;
struct FGameplayEventData;
struct FGameplayTag;
struct FTwitchUser;

DECLARE_LOG_CATEGORY_EXTERN(LogCommon, Display, All)

UCLASS()
class TENTACLE_API UCommon : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	inline static const auto SpawnedTag = FName("TentacleSpawned");

	template <typename T>
		requires TIsDerivedFrom<T, UActorComponent>::IsDerived
	static auto
	AddComponent(AActor* Actor) -> T*
	{
		return Cast<T>(Actor->AddComponentByClass(T::StaticClass(), false, FTransform(), false));
	}

	template <typename T>
		requires TIsDerivedFrom<T, AActor>::IsDerived
	static T*
	GetActorOfClass(const UObject* WorldContext)
	{
		return Cast<T>(UGameplayStatics::GetActorOfClass(WorldContext, T::StaticClass()));
	}

	template <typename T, class AllocatorType>
		requires TIsDerivedFrom<T, AActor>::IsDerived
	static void
	GetAllActorsOfClass(const UObject* WorldContext, TArray<T*, AllocatorType>& OutActors)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(WorldContext, T::StaticClass(), Actors);

		for (auto Actor : Actors)
			OutActors.Add(Cast<T>(Actor));
	}

	template <typename T>
		requires TIsDerivedFrom<T, AActor>::IsDerived
	static T*
	GetActorOfClassWithTag(const UObject* WorldContext, FName Tag)
	{
		auto Actors = TArray<AActor*>();
		UGameplayStatics::GetAllActorsOfClassWithTag(WorldContext, T::StaticClass(), Tag, Actors);
		return Actors.Num() > 0 ? Cast<T>(Actors[0]) : nullptr;
	}

	static void
	GetAllSpawnedActors(const UObject* WorldContext, TArray<AActor*>& OutActors)
	{
		UGameplayStatics::GetAllActorsWithTag(WorldContext, SpawnedTag, OutActors);
	}

	template <typename T>
		requires TIsDerivedFrom<T, AActor>::IsDerived
	static T*
	SpawnActor(const UObject* WorldContext, const FActorSpawnParameters& SpawnParameters)
	{
		T* Actor = SpawnActor<T>(WorldContext, T::StaticClass(), FTransform(), SpawnParameters);
		Actor->Tags.Add(SpawnedTag);
		return Actor;
	}

	template <typename T>
		requires TIsDerivedFrom<T, AActor>::IsDerived
	static T*
	SpawnActor(const UObject* WorldContext, UClass* Class, const FActorSpawnParameters& SpawnParameters)
	{
		return SpawnActor<T>(WorldContext, Class, FTransform(), SpawnParameters);
	}

	template <typename T>
		requires TIsDerivedFrom<T, AActor>::IsDerived
	static T*
	SpawnActor(
		const UObject* WorldContext,
		const FTransform& Transform = FTransform(),
		const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()
	)
	{
		return SpawnActor<T>(WorldContext, T::StaticClass(), Transform, SpawnParameters);
	}

	template <typename T>
		requires TIsDerivedFrom<T, AActor>::IsDerived
	static T*
	SpawnActor(
		const UObject* WorldContext,
		UClass* Class,
		const FTransform& Transform = FTransform(),
		const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()
	)
	{
		const auto World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert);
		T* Actor = World->SpawnActor<T>(Class, Transform, SpawnParameters);
		Actor->Tags.Add(SpawnedTag);
		return Actor;
	}

	static ATentacle*
	GetTentacle();

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	static void
	LogDebug(const FString& Message);

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	static void
	LogInfo(const FString& Message);

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	static void
	LogWarn(const FString& Message);

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	static void
	LogError(const FString& Message);

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	static void
	Debug(const FString& Message);

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	static void
	Info(const FString& Message);

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	static void
	Warn(const FString& Message);

	UFUNCTION(BlueprintCallable, Category="Tentacle")
	static void
	Error(const FString& Message);

	static void
	HandleAssert(const FString& File, const int32 Line, const FString& Message);

	static void
	SendGameplayEventToActor(AActor* Actor, const struct FGameplayTag& EventTag);

	static void
	SendGameplayEventToActor(AActor* Actor, const FGameplayTag& EventTag, const struct FGameplayEventData& Payload);

	UFUNCTION(BlueprintPure, Category="Common")
	static FString
	MakeGuid();

	UFUNCTION(BlueprintPure, Category="Common")
	static FString
	MakeId();

	UFUNCTION(BlueprintPure, Category="Common")
	static bool
	IsRunningInEditor();
};

#define logDebug(Msg) \
	UCommon::LogDebug(TEXT(Msg))

#define logDebugF(MsgTemplate, ...) \
	UCommon::LogDebug(FString::Printf(TEXT(MsgTemplate), __VA_ARGS__))

#define logInfo(Msg) \
	UCommon::LogInfo(TEXT(Msg))

#define logInfoF(MsgTemplate, ...) \
	UCommon::LogInfo(FString::Printf(TEXT(MsgTemplate), __VA_ARGS__))

#define logWarn(Msg) \
	UCommon::LogWarn(TEXT(Msg))

#define logWarnF(MsgTemplate, ...) \
	UCommon::LogWarn(FString::Printf(TEXT(MsgTemplate), __VA_ARGS__))

#define logError(Msg) \
	UCommon::LogError(TEXT(Msg))

#define logErrorF(MsgTemplate, ...) \
	UCommon::LogError(FString::Printf(TEXT(MsgTemplate), __VA_ARGS__))

#define debug(Msg) \
	UCommon::Debug(TEXT(Msg))

#define debugF(MsgTemplate, ...) \
	UCommon::Debug(FString::Printf(TEXT(MsgTemplate), __VA_ARGS__))

#define info(Msg) \
	UCommon::Info(TEXT(Msg))

#define infoF(MsgTemplate, ...) \
	UCommon::Info(FString::Printf(TEXT(MsgTemplate), __VA_ARGS__))

#define warn(Msg) \
	UCommon::Warn(TEXT(Msg))

#define warnF(MsgTemplate, ...) \
	UCommon::Warn(FString::Printf(TEXT(MsgTemplate), __VA_ARGS__))

#define error(Msg) \
	UCommon::Error(TEXT(Msg))

#define errorF(MsgTemplate, ...) \
	UCommon::Error(FString::Printf(TEXT(MsgTemplate), __VA_ARGS__))

#define failFormat(OutError, MsgTemplate, ...) \
	{ \
	    OutError = FString::Printf(TEXT(MsgTemplate), __VA_ARGS__); \
	    return false; \
	}

struct FEmpty {};

struct FErr
{
	FString Message;

	explicit
	FErr(const FString& Message) :
		Message(Message) {}
};

template <typename OkValueType = FEmpty>
struct TOk
{
	OkValueType Value;

	TOk() = default;

	explicit
	TOk(const OkValueType& Ok) : Value(Ok) {}
};

template <typename OkValueType = FEmpty>
class TResult
{
	using OkType = TOk<OkValueType>;

protected:
	TVariant<OkType, FErr> Variant;

	TResult() = default;

public:
	TResult(const OkValueType& OkValue) :
		Variant(TInPlaceType<OkType>(), TOk(OkValue)) {}

	TResult(const OkType& Ok) :
		Variant(TInPlaceType<OkType>(), Ok) {}

	TResult(OkType&& Ok) :
		Variant(TInPlaceType<OkType>(), MoveTemp(Ok)) {}

	TResult(const FErr& Err) :
		Variant(TInPlaceType<FErr>(), Err) {}

	TResult(FErr&& Err) :
		Variant(TInPlaceType<FErr>(), MoveTemp(Err)) {}

	TResult(const TResult& Other) = default;

	TResult(TResult&& Other) = default;

	TResult&
	operator=(const TResult& Other)
	{
		if (&Other != this)
			Variant = Other.Variant;

		return *this;
	}

	TResult&
	operator=(TResult&& Other) noexcept
	{
		if (&Other != this)
			Variant = MoveTemp(Other.Variant);

		return *this;
	}

	TResult&
	operator=(const OkType& OkValue)
	{
		Variant.template Emplace<OkType>(OkValue);
		return *this;
	}

	TResult&
	operator=(const FErr& ErrValue)
	{
		Variant.template Emplace<FErr>(ErrValue);
		return *this;
	}

	virtual ~TResult() = default;

	bool
	IsOk() const { return Variant.template IsType<OkType>(); }

	bool
	IsErr() const { return Variant.template IsType<FErr>(); }

	const OkValueType&
	GetOkValue() const
	{
		checkf(
			IsOk(),
			TEXT("It is an error to call GetOkValue() on a TResult that does not hold an ok value. Please either check IsOk() or use TryGetOkValue")
		);
		return Variant.template Get<OkType>().Value;
	}

	OkValueType&
	GetOkValue()
	{
		checkf(
			IsOk(),
			TEXT("It is an error to call GetOkValue() on a TResult that does not hold an ok value. Please either check IsOk() or use TryGetOkValue")
		);
		return Variant.template Get<OkType>().Value;
	}

	const FErr&
	GetErr() const
	{
		checkf(
			IsErr(),
			TEXT("It is an error to call GeFErr() on a TResult that does not hold an error value. Please either check IsErr() or use TryGeFErrValue")
		);
		return Variant.template Get<FErr>();
	}

	FErr&
	GetErr()
	{
		checkf(
			IsErr(),
			TEXT("It is an error to call GeFErr() on a TResult that does not hold an error value. Please either check IsErr() or use TryGeFErrValue")
		);
		return Variant.template Get<FErr>();
	}

	const OkValueType&
	GetOkValueOrDefault(const OkValueType& DefaultValue) const { return IsOk() ? GetOkValue() : DefaultValue; }
};

#define ifErrLog(Result) \
	if (Result.IsErr()) \
		UCommon::Error(Result.GetErr().Message);

#define ifErrReturn(Result) \
	if (Result.IsErr()) \
		return Result.GetErr(); // This needs to return the err to avoid TResult type mismatches.

USTRUCT(BlueprintType)
struct FResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bOk;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString Message;

	FResult() :
		bOk(true) {}

	FResult(const TResult<FEmpty>& Result)
	{
		bOk = Result.IsOk();
		Message = Result.IsErr() ? Result.GetErr().Message : TEXT("");
	}
};

#define DECLARE_SPAWN(Class) \
	static Class* Spawn( \
		const UObject* WorldContext, \
		const FTransform& Transform = FTransform(), \
		const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters() \
	) \
	{ \
		const auto World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert); \
		return World->SpawnActor<Class>(StaticClass(), Transform, SpawnParameters); \
	} \
	\
	static Class* Spawn( \
		const UObject* WorldContext, \
		const FTransform& Transform, \
		APawn* InstigatedBy \
	) \
	{ \
		auto SpawnParameters = FActorSpawnParameters(); \
		SpawnParameters.Instigator = InstigatedBy; \
		return Spawn(WorldContext, Transform, SpawnParameters); \
	}

#define DECLARE_SPAWN_OneParam(Class, Type1, Name1) \
	static Class* Spawn( \
		const UObject* WorldContext, \
		Type1 Name1, \
		const FTransform& Transform = FTransform(), \
		const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters() \
	) \
	{ \
		const auto World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert); \
		const auto Actor = World->SpawnActorDeferred<Class>(StaticClass(), Transform, SpawnParameters.Owner, SpawnParameters.Instigator, SpawnParameters.SpawnCollisionHandlingOverride, SpawnParameters.TransformScaleMethod); \
		Actor->Name1 = Name1; \
		Actor->FinishSpawning(Transform); \
		return Actor; \
	} \
	\
	static Class* Spawn( \
		const UObject* WorldContext, \
		Type1 Name1, \
		const FTransform& Transform, \
		APawn* InstigatedBy \
	) \
	{ \
		auto SpawnParameters = FActorSpawnParameters(); \
		SpawnParameters.Instigator = InstigatedBy; \
		return Spawn(WorldContext, Name1, Transform, SpawnParameters); \
	}

#define DECLARE_SPAWN_TwoParams(Class, Type1, Name1, Type2, Name2) \
	static Class* Spawn( \
		const UObject* WorldContext, \
		Type1 Name1, \
		Type2 Name2, \
		const FTransform& Transform = FTransform(), \
		const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters() \
	) \
	{ \
		const auto World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert); \
		const auto Actor = World->SpawnActorDeferred<Class>(StaticClass(), Transform, SpawnParameters.Owner, SpawnParameters.Instigator, SpawnParameters.SpawnCollisionHandlingOverride, SpawnParameters.TransformScaleMethod); \
		Actor->Name1 = Name1; \
		Actor->Name2 = Name2; \
		Actor->FinishSpawning(Transform); \
		return Actor; \
	} \
	\
	static Class* Spawn( \
		const UObject* WorldContext, \
		Type1 Name1, \
		Type2 Name2, \
		const FTransform& Transform, \
		APawn* InstigatedBy \
	) \
	{ \
		auto SpawnParameters = FActorSpawnParameters(); \
		SpawnParameters.Instigator = InstigatedBy; \
		return Spawn(WorldContext, Name1, Name2, Transform, SpawnParameters); \
	}

#define DECLARE_SPAWN_ThreeParams(Class, Type1, Name1, Type2, Name2, Type3, Name3) \
	static Class* Spawn( \
		const UObject* WorldContext, \
		Type1 Name1, \
		Type2 Name2, \
		Type3 Name3, \
		const FTransform& Transform = FTransform(), \
		const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters() \
	) \
	{ \
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert); \
		Class* Actor = World->SpawnActorDeferred<Class>(StaticClass(), Transform, SpawnParameters.Owner, SpawnParameters.Instigator, SpawnParameters.SpawnCollisionHandlingOverride, SpawnParameters.TransformScaleMethod); \
		Actor->Name1 = Name1; \
		Actor->Name2 = Name2; \
		Actor->Name3 = Name3; \
		Actor->FinishSpawning(Transform); \
		return Actor; \
	} \
	\
	static Class* Spawn( \
		const UObject* WorldContext, \
		Type1 Name1, \
		Type2 Name2, \
		Type3 Name3, \
		const FTransform& Transform, \
		APawn* InstigatedBy \
	) \
	{ \
		auto SpawnParameters = FActorSpawnParameters(); \
		SpawnParameters.Instigator = InstigatedBy; \
		return Spawn(WorldContext, Name1, Name2, Name3, Transform, SpawnParameters); \
	}

#define DECLARE_SPAWN_FourParams(Class, Type1, Name1, Type2, Name2, Type3, Name3, Type4, Name4) \
	static Class* Spawn( \
		const UObject* WorldContext, \
		Type1 Name1, \
		Type2 Name2, \
		Type3 Name3, \
		Type4 Name4, \
		const FTransform& Transform = FTransform(), \
		const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters() \
	) \
	{ \
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert); \
		Class* Actor = World->SpawnActorDeferred<Class>(StaticClass(), Transform, SpawnParameters.Owner, SpawnParameters.Instigator, SpawnParameters.SpawnCollisionHandlingOverride, SpawnParameters.TransformScaleMethod); \
		Actor->Name1 = Name1; \
		Actor->Name2 = Name2; \
		Actor->Name3 = Name3; \
		Actor->Name4 = Name4; \
		Actor->FinishSpawning(Transform); \
		return Actor; \
	} \
	\
	static Class* Spawn( \
		const UObject* WorldContext, \
		Type1 Name1, \
		Type2 Name2, \
		Type3 Name3, \
		Type4 Name4, \
		const FTransform& Transform, \
		APawn* InstigatedBy \
	) \
	{ \
		auto SpawnParameters = FActorSpawnParameters(); \
		SpawnParameters.Instigator = InstigatedBy; \
		return Spawn(WorldContext, Name1, Name2, Name3, Name4, Transform, SpawnParameters); \
	}

#define softAssertValid(ObjectPtr) \
	softAssert(IsValid(ObjectPtr))

#define softAssertValidR(ObjectPtr, Return) \
	softAssertR(IsValid(ObjectPtr), Return)

#define softAssert(Condition) \
	if (!(Condition)) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, #Condition); \
		return; \
	}

#define softAssertR(Condition, Return) \
	if (!(Condition)) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, #Condition); \
		return Return; \
	}

#define softAssertRN(Condition) \
	softAssertR(Condition, nullptr)

#define softAssertOk(Result) \
	if (Result.IsErr()) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, Result.GetErr().Message); \
		return; \
	}

#define softAssertRErr(Condition, Message) \
	if (!(Condition)) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, #Condition); \
		return FErr(Message); \
	}

#define softAssertMsg(Condition, Message) \
	if (!(Condition)) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, Message); \
		return; \
	}

#define softAssertMsgF(Condition, MsgTemplate, ...) \
	if (!(Condition)) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, FString::Printf(TEXT(MsgTemplate), __VA_ARGS__)); \
		return; \
	}

#define softAssertMsgR(Condition, Message, Return) \
	if (!(Condition)) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, Message); \
		return Return; \
	}

#define softAssertMsgRN(Condition, Message) \
	softAssertMsgR(Condition, Message, nullptr)

#define softAssertResultOk(Result) \
	if (Result.IsErr()) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, Result.GetErr().Message); \
		return; \
	}

#define silentAssert(Condition) \
	if (!(Condition)) \
	    return;

#define silentAssertR(Condition, Return) \
	if (!(Condition)) \
	    return Return;

#define silentAssertValid(ObjectPtr) \
	silentAssert(IsValid(ObjectPtr))

#define silentAssertValidR(ObjectPtr, Return) \
	silentAssertR(IsValid(ObjectPtr), Return)

#define thruAssert(Condition) \
	if (!(Condition)) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, #Condition); \
	}

#define thruAssertValid(ObjectPtr) \
	thruAssert(IsValid(ObjectPtr))

#define thruAssertMsg(Condition, Message) \
	if (!(Condition)) \
	{ \
		UCommon::HandleAssert(__FILE__, __LINE__, Message); \
	}

#define todo() \
	errorF("TODO: %s, line %s", *FPaths::GetCleanFilename(__FILE__), __LINE__);

#define todoReturn(Return) \
	todo() \
	return Return;

#define notImplemented() \
	errorF("Not Implemented: %s, line %s", *FPaths::GetCleanFilename(__FILE__), __LINE__);

#define notImplementedR(Return) \
	notImplemented() \
	return Return;

#define addDynamicSafe(Delegate, Function) \
	if (!Delegate.IsAlreadyBound(this, &Function)) \
		Delegate.AddDynamic(this, &Function);

#define removeDynamicSafe(Delegate, Function) \
	if (Delegate.IsAlreadyBound(this, &Function)) \
		Delegate.RemoveDynamic(this, &Function);

#define SINGLETON_ACTOR(Class) \
	static Class* Get(const UObject* WorldContext)\
	{\
		static auto Instance = TWeakObjectPtr<Class>();\
		if (!Instance.IsValid())\
			Instance = UCommon::GetActorOfClass<Class>(WorldContext);\
	\
		softAssertR(Instance.IsValid(), nullptr);\
		return Instance.Get();\
	}\
	\
	static Class* GetOrSpawn(const UObject* WorldContext)\
	{\
		static auto Instance = TWeakObjectPtr<Class>();\
		\
		if (!Instance.IsValid())\
		{\
			Instance = UCommon::GetActorOfClass<Class>(WorldContext);\
			if (!Instance.IsValid())\
				Instance = UCommon::SpawnActor<Class>(WorldContext);\
		}\
		\
		softAssertR(Instance.IsValid(), nullptr);\
		return Instance.Get();\
	}

#define FORMAT(Template, ...) \
	FString::Format(TEXT(Template), {__VA_ARGS__})
