// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "MultiplayerSessionSubsystem.h"
#include "Components/Button.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	
	AddToViewport();
	
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(true);
		}
	}
	
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		SessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
	}
	if (SessionSubsystem)
	{
		SessionSubsystem->MultiplayerOnCreateSessionCompleteDelegate.AddDynamic(this, &UMenu::OnCreateSession);
		SessionSubsystem->MultiplayerOnFindSessionsCompleteDelegate.AddUObject(this, &UMenu::OnFindSessions);
		SessionSubsystem->MultiplayerOnJoinSessionCompleteDelegate.AddUObject(this, &UMenu::OnJoinSession);
		SessionSubsystem->MultiplayerOnDestroySessionCompleteDelegate.AddDynamic(this, &UMenu::OnDestroySession);
		SessionSubsystem->MultiplayerOnStartSessionCompleteDelegate.AddDynamic(this, &UMenu::OnStartSession);
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::JoinButtonClicked);
	}
	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString(TEXT("Session created successfully!!!!!!!!!!"))
			);
		}
		UWorld* World = GetWorld();
		if (World)
		{
			CleanupMenu();
			World->ServerTravel(FString("/Game/Maps/Lobby?listen"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Failed to create session!!!!!!!!!!"))
			);
		}
		HostButton->SetIsEnabled(true);
	}
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionSearchResults, bool bWasSuccessful)
{
	if (!SessionSubsystem)
	{
		return;
	}
	if (!bWasSuccessful)
	{
		JoinButton->SetIsEnabled(true);
		return;
	}
	for (auto& Result : SessionSearchResults)
	{
		FString SessionName;
		Result.Session.SessionSettings.Get(FName("MatchType"), SessionName);
		
		if (SessionName == MatchType)
		{
			SessionSubsystem->JoinSession(Result);
			return;
		}
	}
	JoinButton->SetIsEnabled(true);
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
		return;
	}
	
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			if (!SessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
			{
				JoinButton->SetIsEnabled(true);
				return;
			}
			
			UWorld* World = GetWorld();
			if (World)
			{
				APlayerController* PlayerController = World->GetFirstPlayerController();
				if (PlayerController)
				{
					CleanupMenu();
					PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
				}
			}
			
		}
	}
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
	
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
	
}

void UMenu::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	if (SessionSubsystem)
	{
		SessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
	else
	{
		HostButton->SetIsEnabled(true);
	}
}

void UMenu::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);
	if (SessionSubsystem)
	{
		SessionSubsystem->FindSessions(10000);
	}
	else
	{
		JoinButton->SetIsEnabled(true);
	}
}

void UMenu::MenuTearDown()
{
	if (SessionSubsystem)
	{
		SessionSubsystem->MultiplayerOnCreateSessionCompleteDelegate.RemoveDynamic(this, &UMenu::OnCreateSession);
		SessionSubsystem->MultiplayerOnFindSessionsCompleteDelegate.RemoveAll(this);
		SessionSubsystem->MultiplayerOnJoinSessionCompleteDelegate.RemoveAll(this);
		SessionSubsystem->MultiplayerOnDestroySessionCompleteDelegate.RemoveDynamic(this, &UMenu::OnDestroySession);
		SessionSubsystem->MultiplayerOnStartSessionCompleteDelegate.RemoveDynamic(this, &UMenu::OnStartSession);
	}
}

void UMenu::CleanupMenu()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
