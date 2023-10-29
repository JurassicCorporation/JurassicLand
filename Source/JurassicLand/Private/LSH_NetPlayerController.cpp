// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_NetPlayerController.h"
#include "Components/WidgetComponent.h"
#include "JE_NicknameWidget.h"
#include "BlueTrex.h"
#include "Components/TextRenderComponent.h"
#include "JE_PlayerState.h"
#include "LSH_NetGameInstance.h"


ALSH_NetPlayerController::ALSH_NetPlayerController()
{
	//PrimaryActorTick.bCanEverTick = true;


	//if (player)
	//{
	//	// 닉네임 컴포넌트 생성
	//	nickNameComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("nickNameComp"));
	//	nickNameComp->SetupAttachment(player->GetRootComponent());
	//	nickNameComp->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	//	nickNameComp->SetWidgetSpace(EWidgetSpace::Screen);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NicknameUI"));
	//}

	
}

void ALSH_NetPlayerController::BeginPlay()
{
    Super::BeginPlay();

	gi = Cast<ULSH_NetGameInstance>(GetGameInstance());
	player = Cast<ABlueTrex>(GetPawn());


	AJE_PlayerState* playerState = GetPlayerState<AJE_PlayerState>();
	//AJE_PlayerState* playerState = Cast<AJE_PlayerState>(player->GetPlayerState());
	if (playerState != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, gi->myName);
		if (player != nullptr)		{
			
			//player->playerState->SetPlayerName(gi->myName);
			playerState->SetPlayerName(gi->myName);
			GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, playerState->PlayerName);
			player->ServerSetNickName();
		}
		
	}


	/*if (player != nullptr)
	{
		player->nicknameText->SetVisibility(true);

	}*/

	/*if (nickNameComp != nullptr)
	{
		nickNameComp->AttachToComponent(player->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "HeadSocket");
		nickNameUI = Cast<UJE_NicknameWidget>(nickNameComp->GetWidget());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NicknameUI"));
	}*/

	//if (player)
	//{
	//	nickNameComp->AttachToComponent(player->GetRootComponent());
	//}
}
