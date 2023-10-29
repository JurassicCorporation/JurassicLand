// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_MultiBattleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "LSH_NetGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "LSH_NetPlayerController.h"
#include "LSH_BattleGameModeBase.h"
#include <GameFramework/GameModeBase.h>


void UJE_MultiBattleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = GetGameInstance<ULSH_NetGameInstance>();

	//GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, gi->myName);

	btn_ready->OnClicked.AddDynamic(this, &UJE_MultiBattleWidget::OnClickedReady);

}

void UJE_MultiBattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	
}

void UJE_MultiBattleWidget::OnClickedReady()
{
	if (clickOnce)
	{
		readyCount++;
		clickOnce = false;
	}

	UE_LOG(LogTemp, Warning, TEXT("readycount %d , %d"), readyCount, clickOnce);

	APlayerController* PlayerController = GetOwningPlayer();


	if (PlayerController)
			{

				if (PlayerController->GetLocalRole() == ROLE_Authority)
				{
					// 이 코드는 서버에서만 실행됩니다.
					AGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGameModeBase>();
					if (GameMode)
					{
						int32 PlayerCount = GameMode->GetNumPlayers();
						// PlayerCount 변수는 현재 세션의 플레이어 수를 가지고 있습니다.
						UE_LOG(LogTemp, Warning, TEXT("%d"), PlayerCount);
						if (PlayerCount >= 2)
						{
							gi->OnTravlebattleMap();
							ALSH_NetPlayerController* lsh_pc = Cast<ALSH_NetPlayerController>(PlayerController);
							lsh_pc->bBattleIn = true;
						}
					}
				}
				else
				{
					// 이 코드는 클라이언트에서만 실행됩니		
				

					FString Message = FString::Printf(TEXT("Client"));
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
				}
			}

	


}

void UJE_MultiBattleWidget::MulticastBattleSwitchWidget_Implementation(int32 index)
{
	ws_MultiBattle->SetActiveWidgetIndex(1);
	FString Message = FString::Printf(TEXT("Multicast, %d"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);

}

void UJE_MultiBattleWidget::ServerBattleSwitchWidget_Implementation(int32 index)
{
	MulticastBattleSwitchWidget(1);
	FString Message = FString::Printf(TEXT("%d"), index);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Message);
}

//void UJE_MultiBattleWidget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	//DOREPLIFETIME(UJE_MultiBattleWidget, widgetIndex);
//
//}

//void UJE_MultiBattleWidget::serverReadyCountUp_Implementation(int32 allReadyCount)
//{
//	//MulticastReadyCount();
//	
//
//	APlayerController* PlayerController = GetOwningPlayer();
//
//	if (PlayerController)
//	{
//		if (PlayerController->GetLocalRole() == ROLE_Authority)
//		{
//			// 이 코드는 서버에서만 실행됩니다.
//			UE_LOG(LogTemp, Warning, TEXT("server"));
//			readyCount++;
//		}
//		else
//		{
//			// 이 코드는 클라이언트에서만 실행됩니다.
//			UE_LOG(LogTemp, Warning, TEXT("client"));
//
//		}
//	}
//
//	UE_LOG(LogTemp, Warning, TEXT("serverReadyCountUP %d"), readyCount);
//
//}

