// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionCompleteDelegate, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsCompleteDelegate, const TArray<FOnlineSessionSearchResult>& SessionSearchResult, bool bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionCompleteDelegate, bool, bWasSuccessful);
/**
 * 
 */
UCLASS()
class ZEROPOINT_API UMultiplayerSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UMultiplayerSessionSubsystem();
	
	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSessions(int32 MaxSearchResults);
	void DestroySession();
	
	FMultiplayerOnCreateSessionCompleteDelegate MultiplayerOnCreateSessionCompleteDelegate;
	FMultiplayerOnDestroySessionCompleteDelegate MultiplayerOnDestroySessionCompleteDelegate;
	FMultiplayerOnFindSessionsCompleteDelegate MultiplayerOnFindSessionsCompleteDelegate;
	
protected:
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsCompleteDelegate(bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	
private:
	IOnlineSessionPtr SessionInterface;
	
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	
	int32 DesiredNumPublicConnections;
	FString DesiredMatchType;
	bool bCreateSessionOnDestroy = false;
};
