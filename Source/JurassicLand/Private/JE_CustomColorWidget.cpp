// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_CustomColorWidget.h"
#include "LSH_NetGameInstance.h"
#include "Components/Button.h"
#include "BlueTrex.h"
#include "GameFramework/PlayerState.h"
#include "JE_PlayerState.h"



void UJE_CustomColorWidget::NativeConstruct()
{
	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();
	ps = GetOwningPlayerState<AJE_PlayerState>();

	btn_red->OnClicked.AddDynamic(this, &UJE_CustomColorWidget::OnRedClicked);
	btn_yellow->OnClicked.AddDynamic(this, &UJE_CustomColorWidget::OnYellowClicked);
	btn_blue->OnClicked.AddDynamic(this, &UJE_CustomColorWidget::OnBlueClicked);
	btn_green->OnClicked.AddDynamic(this, &UJE_CustomColorWidget::OnGreenClicked);
}

void UJE_CustomColorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_CustomColorWidget::OnYellowClicked()
{

	FLinearColor nowColor = FLinearColor(1.0f, 0.17f, 0.65f);
	if (currentColor != nowColor)
	{
		gi->IsColorChanged = true;

		currentColor = nowColor;
		player->IsColorCustom = true;
	}
	else
	{
		gi->IsColorChanged = false;

		currentColor = FLinearColor::White;
		player->IsColorCustom = false;

	}
	
	player->playerColor = currentColor;
	//gi->playerCustomInfo.dinoColor = currentColor;
	//ps->pCustomInfo.pColor = currentColor;
	//ps->SetInstanceCustomInfo();
	player->SetColor();
}

void UJE_CustomColorWidget::OnBlueClicked()
{	

	if (currentColor != FLinearColor::Blue)
	{
		gi->IsColorChanged = true;

		currentColor = FLinearColor::Blue;
		player->IsColorCustom = true;

	}
	else
	{
		gi->IsColorChanged = false;

		currentColor = FLinearColor::White;
		player->IsColorCustom = false;

	}
	player->playerColor = currentColor;
	//gi->playerCustomInfo.dinoColor = currentColor;
	//ps->pCustomInfo.pColor = currentColor;
	//ps->SetInstanceCustomInfo();

	player->SetColor();

}

void UJE_CustomColorWidget::OnGreenClicked()
{

	if (currentColor != FLinearColor::Green)
	{
		gi->IsColorChanged = true;

		currentColor = FLinearColor::Green;
		player->IsColorCustom = true;

	}
	else
	{
		gi->IsColorChanged = false;

		currentColor = FLinearColor::White;
		player->IsColorCustom = false;

	}
	player->playerColor = currentColor;
	//gi->playerCustomInfo.dinoColor = currentColor;
	//ps->pCustomInfo.pColor = currentColor;
	//ps->SetInstanceCustomInfo();

	player->SetColor();

}

void UJE_CustomColorWidget::OnRedClicked()
{

	if (currentColor != FLinearColor::Red)
	{
		gi->IsColorChanged = true;

		currentColor = FLinearColor::Red;
		player->IsColorCustom = true;

	}
	else
	{
		gi->IsColorChanged = false;

		currentColor = FLinearColor::White;
		player->IsColorCustom = false;

	}
	player->playerColor = currentColor;
	//gi->playerCustomInfo.dinoColor = currentColor;
	//ps->pCustomInfo.pColor = currentColor;
	//ps->SetInstanceCustomInfo();
	player->SetColor();

}

