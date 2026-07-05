// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

class UMultiplayerSessionSubsystem;
class UButton;
/**
 * 
 */
UCLASS()
class ZEROPOINT_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch);
	
protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionSearchResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:
	
	UMultiplayerSessionSubsystem* SessionSubsystem;
	
	UPROPERTY(meta=(BindWidget))
	UButton* HostButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* JoinButton;
	
	UFUNCTION()
	void HostButtonClicked();
	
	UFUNCTION()
	void JoinButtonClicked();
	
	void MenuTearDown();
	void CleanupMenu();
	
	int32 NumPublicConnections;
	
	FString MatchType;
};
