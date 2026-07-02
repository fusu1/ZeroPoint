// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionCompleteDelegate, bool, bWasSuccessful);

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
	
	FMultiplayerOnCreateSessionCompleteDelegate MultiplayerOnCreateSessionCompleteDelegate;
	
protected:
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
private:
	IOnlineSessionPtr SessionInterface;
	
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
};
