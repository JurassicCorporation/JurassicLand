// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Progressbar.h"
#include "Animation/WidgetAnimation.h"
#include "BlueTrex.h"
#include "LSH_NetGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "JE_BattleInController.h"
#include "JE_InBattleController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void UJE_BattleWidget::NativeConstruct()
{

	Super::NativeConstruct();

	//battleStartAnim = UKismetWidgetBlueprintLibrary::GetAnimationByName(TEXT("battleStartAnim"));

	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();
	//pc = GetOwningPlayer<AJE_BattleInController>();

	//player->bIsHPShow = true;
	pbArr.Add(pb_coolTime1);
	pbArr.Add(pb_coolTime2);
	pbArr.Add(pb_coolTime3);
	pbArr.Add(pb_coolTimeq);
	pbArr.Add(pb_coolTimee);

	coolTimeActors.Init(nullptr, 5);

	img_specialskill->SetBrushResourceObject(gi->playerSkillInfo.playerSpecialSkillImg);
	img_buffskill->SetBrushResourceObject(gi->playerSkillInfo.playerBuffSkillImg);

	GetWorld()->GetTimerManager().SetTimer(initHandler, this, &UJE_BattleWidget::StartUIAnim, 3.0f, false);

	btn_toMain->OnClicked.AddDynamic(this, &UJE_BattleWidget::OnClickedToMain);
}

void UJE_BattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//FString Message = gi->isEnd == true ? FString::Printf(TEXT("true")) : FString::Printf(TEXT("false"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);

	if (IsValid(coolTimeActors[0]))
	{
		SetTailCool(0);
	}

	if (IsValid(coolTimeActors[1]))
	{
		SetBiteCool(1);
	}

	if (IsValid(coolTimeActors[2]))
	{
		SetRoarCool(2);
	}

	if (IsValid(coolTimeActors[3]))
	{
		SetBuffCool(3);
	}

	if (IsValid(coolTimeActors[4]))
	{
		SetSpecialCool(4);
	}

	if (gi->isEnd && !ischange)
	{
		if (player->TRexHP <= 0.f)
		{
			ws_Battle->SetActiveWidgetIndex(3);
			txt_battleresult->SetText(FText::FromString("Lose"));
			GetWorld()->GetTimerManager().SetTimer(CoinHandler, this, &UJE_BattleWidget::CoinUI, 3.0f, false);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Lose")));
			
			ischange = true;

		}
		else
		{
			ws_Battle->SetActiveWidgetIndex(3);
			txt_battleresult->SetText(FText::FromString("Win"));
			player->currentCoin += 5000.f;
			GetWorld()->GetTimerManager().SetTimer(CoinHandler, this, &UJE_BattleWidget::CoinUI, 3.0f, false);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Win")));
			ischange = true;

		}

	}

}

void UJE_BattleWidget::LoadingUI()
{
	ws_Battle->SetActiveWidgetIndex(2);
}

void UJE_BattleWidget::StartUIAnim()
{
	ws_Battle->SetActiveWidgetIndex(1);
	PlayAnimationForward(startText);

	FTimerHandle AnimHandler;
	GetWorld()->GetTimerManager().SetTimer(AnimHandler, FTimerDelegate::CreateLambda([&]() {

		
		//FString Message = FString::Printf(TEXT("startUIANim"));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
		LoadingUI();

		}), 5.0f, false);
}

void UJE_BattleWidget::CoinUI()
{
	//ws_Battle->SetActiveWidgetIndex(4);
	bisMouse = true;

	APlayerController* pc = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly InputModeData;

	pc->SetInputMode(InputModeData);

	btn_toMain->SetVisibility(ESlateVisibility::Visible);
	/*if (pc)
	{
		FInputModeGameAndUI InputMode;
		pc->SetInputMode(InputMode);
		pc->bShowMouseCursor = true;
	}*/

}

void UJE_BattleWidget::OnClickedToMain()
{
	//FString LevelName = TEXT("MainMap");
	//UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));

	//ws_Battle->SetActiveWidgetIndex(0);

	FString mapAdress = "/Game/1_Level/MainMap";
	bool travelResult = GetWorld()->ServerTravel(mapAdress + "?Listen", true);

	UE_LOG(LogTemp, Warning, TEXT("Server travel Result : %s"), travelResult ? *FString("Success") : *FString("Failed"));


	
}

void UJE_BattleWidget::SetSkillCool(int32 usedskill)
{
	switch (usedskill)
	{
	case 0:
		SetTailCool(usedskill);
		break;
	case 1:
		SetBiteCool(usedskill);
		break;
	case 2:
		SetRoarCool(usedskill);
		break;
	case 3:
		SetBuffCool(usedskill);
		break;
	case 4:
		SetSpecialCool(usedskill);
		break;
	default:
		break;
	}
}

void UJE_BattleWidget::SetTailCool(int32 skillNum)
{
	float skillcoolTime = 2.0f;

	if (!IsValid(coolTimeActors[skillNum]))
	{
		coolTimeActors[skillNum] = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *coolTimeActors[skillNum]->GetName());
		coolTimeActors[skillNum]->SetLifeSpan(skillcoolTime);

	}

	float value = coolTimeActors[skillNum]->GetLifeSpan();
	float rangemin = 0.1f;
	float rangemax = skillcoolTime;

	if (value - rangemin <= 0.f)
	{
		pbArr[skillNum]->SetPercent(0.f);
		player->coolTimeIndex = -1;

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("End"));
		//coolTimeActor = nullptr;
	}
	else
	{
		pbArr[skillNum]->SetPercent((value - rangemin) / (rangemax - rangemin));
	}


	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Tail : %2.f"), value));
}

void UJE_BattleWidget::SetBiteCool(int32 skillNum)
{
	float skillcoolTime = 2.0f;

	if (!IsValid(coolTimeActors[skillNum]))
	{
		coolTimeActors[skillNum] = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *coolTimeActors[skillNum]->GetName());
		coolTimeActors[skillNum]->SetLifeSpan(skillcoolTime);

	}

	float value = coolTimeActors[skillNum]->GetLifeSpan();
	float rangemin = 0.1f;
	float rangemax = skillcoolTime;

	if (value - rangemin <= 0.f)
	{
		pbArr[skillNum]->SetPercent(0.f);
		player->coolTimeIndex = -1;

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("End"));
		//coolTimeActor = nullptr;
	}
	else
	{
		pbArr[skillNum]->SetPercent((value - rangemin) / (rangemax - rangemin));
	}


	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Bite : %2.f"), value));
}

void UJE_BattleWidget::SetRoarCool(int32 skillNum)
{
	float skillcoolTime = 2.0f;

	if (!IsValid(coolTimeActors[skillNum]))
	{
		coolTimeActors[skillNum] = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *coolTimeActors[skillNum]->GetName());
		coolTimeActors[skillNum]->SetLifeSpan(skillcoolTime);

	}

	float value = coolTimeActors[skillNum]->GetLifeSpan();
	float rangemin = 0.1f;
	float rangemax = skillcoolTime;

	if (value - rangemin <= 0.f)
	{
		pbArr[skillNum]->SetPercent(0.f);
		player->coolTimeIndex = -1;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("End"));
		//coolTimeActor = nullptr;
	}
	else
	{
		pbArr[skillNum]->SetPercent((value - rangemin) / (rangemax - rangemin));
	}


	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Roar : %2.f"), value));
}

void UJE_BattleWidget::SetBuffCool(int32 skillNum)
{
	float skillcoolTime = 5.0f;
	if (player->BCoolTime)
	{
		if (!IsValid(coolTimeActors[skillNum]))
		{
			coolTimeActors[skillNum] = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *coolTimeActors[skillNum]->GetName());
			coolTimeActors[skillNum]->SetLifeSpan(skillcoolTime);

		}

		float value = coolTimeActors[skillNum]->GetLifeSpan();
		float rangemin = 0.1f;
		float rangemax = skillcoolTime;

		if (value - rangemin <= 0.f)
		{
			pbArr[skillNum]->SetPercent(0.f);
			player->coolTimeIndex = -1;

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("End"));
			//coolTimeActor = nullptr;
		}
		else
		{
			pbArr[skillNum]->SetPercent((value - rangemin) / (rangemax - rangemin));
		}


		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("buffCool : %2.f"), value));
	}
	
}

void UJE_BattleWidget::SetSpecialCool(int32 skillNum)
{
	//if (usedskill <= 2)
//{
//	skillcoolTime = 2.0f;
//}
//else
//{
//	skillcoolTime = 5.0f;
//}
	if (player->SCoolTime)
	{
		float skillcoolTime = 5.0f;

		if (!IsValid(coolTimeActors[skillNum]))
		{
			coolTimeActors[skillNum] = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *coolTimeActors[skillNum]->GetName());
			coolTimeActors[skillNum]->SetLifeSpan(skillcoolTime);

		}

		float value = coolTimeActors[skillNum]->GetLifeSpan();
		float rangemin = 0.1f;
		float rangemax = skillcoolTime;

		if (value - rangemin <= 0.f)
		{
			pbArr[skillNum]->SetPercent(0.f);
			player->coolTimeIndex = -1;

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("End"));
			//coolTimeActor = nullptr;
		}
		else
		{
			pbArr[skillNum]->SetPercent((value - rangemin) / (rangemax - rangemin));
		}


		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Special : %2.f"), value));
	}
	
}
