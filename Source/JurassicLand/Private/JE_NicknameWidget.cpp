// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_NicknameWidget.h"
#include "LSH_NetGameInstance.h"
#include "Components/TextBlock.h"

void UJE_NicknameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	gi = Cast<ULSH_NetGameInstance>(GetGameInstance());

	txt_playerName->SetText(FText::FromString(gi->myName));
	txt_playerName->SetText(FText::FromString(gi->playerCustomInfo.dinoName));
}

void UJE_NicknameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}
