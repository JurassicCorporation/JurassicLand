
// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_CustomWholeWidget.h"
#include "LSH_NetGameInstance.h"
#include "Components/Button.h"
#include "BlueTrex.h"
#include "Kismet/GameplayStatics.h"


void UJE_CustomWholeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();

	btn_load->OnClicked.AddDynamic(this, &UJE_CustomWholeWidget::OnClickedLoad);
	btn_save->OnClicked.AddDynamic(this, &UJE_CustomWholeWidget::OnClickedSave);
	btn_backtomain->OnClicked.AddDynamic(this, &UJE_CustomWholeWidget::OnClickedBacktomain);
}

void UJE_CustomWholeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_CustomWholeWidget::OnClickedLoad()
{
	player->LoadCustomItemData();
}

void UJE_CustomWholeWidget::OnClickedSave()
{
	player->SaveCustomItemData();

}

void UJE_CustomWholeWidget::OnClickedBacktomain()
{
	FString LevelName = TEXT("MainMap");
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}
