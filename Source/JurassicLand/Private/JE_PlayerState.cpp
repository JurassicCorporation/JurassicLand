// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_PlayerState.h"
#include "LSH_NetGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"


void AJE_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<ULSH_NetGameInstance>(GetGameInstance());

	if (gi != nullptr && GetPlayerController() != nullptr && GetPlayerController()->IsLocalPlayerController())
	{
		InitialInfo();
		SetdinoName(gi->playerCustomInfo.dinoName);

	}
}

void AJE_PlayerState::SetdinoName_Implementation(const FString& myName)
{
	SetPlayerName(myName);
}


void AJE_PlayerState::InitialInfo_Implementation()
{	
	// 게임인스턴스의 플레이어 정보 가져오기
	//pCustomInfo.pName = gi->playerCustomInfo.dinoName;
	//pCustomInfo.pMeshNum = gi->playerCustomInfo.dinoMeshNum;
	//pCustomInfo.pColor = gi->playerCustomInfo.dinoColor;
	SetInstanceCustomInfo();

	// 게임 인스턴스의 플레이어 커스텀 아이템 가져오기
	/*pCustomItemInfo.pHatName = gi->playerCustomItemInfo.HatTagInstance;
	pCustomItemInfo.pGlassesName = gi->playerCustomItemInfo.GlassesTagInstance;
	pCustomItemInfo.pShoesName = gi->playerCustomItemInfo.ShoesTagInstance;*/
	SetInstanceCustomItemInfo();
}

void AJE_PlayerState::SetInstanceCustomInfo_Implementation()
{
	pCustomInfo.pName = gi->playerCustomInfo.dinoName;
	pCustomInfo.pMeshNum = gi->playerCustomInfo.dinoMeshNum;
	pCustomInfo.pColor = gi->playerCustomInfo.dinoColor;
	/*gi->playerCustomInfo.dinoName = pCustomInfo.pName;
	gi->playerCustomInfo.dinoMeshNum = pCustomInfo.pMeshNum;
	gi->playerCustomInfo.dinoColor = pCustomInfo.pColor;*/

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("SaveColor"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, pCustomInfo.pColor.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, gi->playerCustomInfo.dinoColor.ToString());
}

void AJE_PlayerState::SetInstanceCustomItemInfo_Implementation()
{
	pCustomItemInfo.pHatName = gi->playerCustomItemInfo.HatTagInstance;
	pCustomItemInfo.pGlassesName = gi->playerCustomItemInfo.GlassesTagInstance;
	pCustomItemInfo.pShoesName = gi->playerCustomItemInfo.ShoesTagInstance;
	/*gi->playerCustomItemInfo.HatTagInstance = pCustomItemInfo.pHatName;
	gi->playerCustomItemInfo.GlassesTagInstance = pCustomItemInfo.pGlassesName;
	gi->playerCustomItemInfo.ShoesTagInstance = pCustomItemInfo.pShoesName;*/

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Save"));

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, pCustomItemInfo.pHatName.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, pCustomItemInfo.pGlassesName.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, pCustomItemInfo.pShoesName.ToString());

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, gi->playerCustomItemInfo.HatTagInstance.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, gi->playerCustomItemInfo.GlassesTagInstance.ToString()); 
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, gi->playerCustomItemInfo.ShoesTagInstance.ToString());
}

void AJE_PlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AJE_PlayerState, pCustomInfo);
	DOREPLIFETIME(AJE_PlayerState, pCustomItemInfo);
	//DOREPLIFETIME(AJE_PlayerState, pMeshNum);
	//DOREPLIFETIME(AJE_PlayerState, pHatName);
	//DOREPLIFETIME(AJE_PlayerState, pGlassesName);
	//DOREPLIFETIME(AJE_PlayerState, pShoesName);
}