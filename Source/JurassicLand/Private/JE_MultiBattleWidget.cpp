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
	gi = GetGameInstance<ULSH_NetGameInstance>();

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

	FString Message = FString::Printf(TEXT("%d"), readyCount);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
	UE_LOG(LogTemp, Warning, TEXT("readycount %d , %d"), readyCount, clickOnce);

	APlayerController* PlayerController = GetOwningPlayer();


	if (PlayerController)
			{
				if (PlayerController->GetLocalRole() == ROLE_Authority)
				{
					// �� �ڵ�� ���������� ����˴ϴ�.
					AGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGameModeBase>();
					if (GameMode)
					{
						int32 PlayerCount = GameMode->GetNumPlayers();
						// PlayerCount ������ ���� ������ �÷��̾� ���� ������ �ֽ��ϴ�.
						UE_LOG(LogTemp, Warning, TEXT("%d"), PlayerCount);
					}
				}
				else
				{
					// �� �ڵ�� Ŭ���̾�Ʈ������ ����˴�		
				}
			}


}

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
//			// �� �ڵ�� ���������� ����˴ϴ�.
//			UE_LOG(LogTemp, Warning, TEXT("server"));
//			readyCount++;
//		}
//		else
//		{
//			// �� �ڵ�� Ŭ���̾�Ʈ������ ����˴ϴ�.
//			UE_LOG(LogTemp, Warning, TEXT("client"));
//
//		}
//	}
//
//	UE_LOG(LogTemp, Warning, TEXT("serverReadyCountUP %d"), readyCount);
//
//}

