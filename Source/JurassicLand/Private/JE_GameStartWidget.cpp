// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_GameStartWidget.h"
#include "JE_GI.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "LSH_NetGameInstance.h"
#include "BlueTrex.h"
#include "GameFramework/PlayerState.h"


void UJE_GameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//je_gi = GetGameInstance<UJE_GI>();
	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();

	btn_skip->OnClicked.AddDynamic(this, &UJE_GameStartWidget::OnClickedSkip);
	btn_nickCheck->OnClicked.AddDynamic(this, &UJE_GameStartWidget::OnClickedNickCheck);

}

void UJE_GameStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (currentTime < endTime)
	{
		currentTime += InDeltaTime;

		pb_loading->SetPercent(currentTime / endTime);
	}
	else
	{
		if(loadingCount == 0)
		{
			SwitchCanvas(1);
			loadingCount++;
		}
		else
		{
			return;
		}
	}

}

void UJE_GameStartWidget::OnClickedSkip()
{
	//FString Message = FString::Printf(TEXT("SkipButtonClicked"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
	
	SwitchCanvas(2);
}

void UJE_GameStartWidget::OnClickedNickCheck()
{
	if (!edit_nickname->GetText().IsEmpty())
	{
		gi->myName = edit_nickname->GetText().ToString();
		gi->playerCustomInfo.dinoName = edit_nickname->GetText().ToString();
	}
	
	FString LevelName = TEXT("MainMap");
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));

}

void UJE_GameStartWidget::SwitchCanvas(int32 index)
{
	ws_GameStartUI->SetActiveWidgetIndex(index);
}
