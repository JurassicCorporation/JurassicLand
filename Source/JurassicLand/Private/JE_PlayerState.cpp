// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_PlayerState.h"
#include "Net/UnrealNetwork.h"	// 언리얼 네트워크 기능 사용을 위한 헤더


void AJE_PlayerState::SetPlayerName(const FString& NewPlayerName)
{
	PlayerName = NewPlayerName;
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Blue, PlayerName);

}

void AJE_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJE_PlayerState, PlayerName);
}