// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_SkillWidget.h"
#include "LSH_NetGameInstance.h"
#include "BlueTrex.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "Kismet/GameplayStatics.h"
#include "JE_SkillModeBase.h"
#include "Raptor.h"
#include "BasePlayer.h"



void UJE_SkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = GetGameInstance<ULSH_NetGameInstance>();

	TrexPlayer = GetOwningPlayerPawn<ABlueTrex>();

	RaptorPlayer = GetOwningPlayerPawn<ARaptor>();
	if(RaptorPlayer) basePlayer = RaptorPlayer;
	//BasePlayer = GetOwningPlayerPawn<ABasePlayer>();

	presetArray.Add(img_preset1);
	presetArray.Add(img_preset2);
	//presetArray.Add(img_preset3);

	presetImgArray.Add(presetImg1);
	presetImgArray.Add(presetImg2);
	//presetImgArray.Add(presetImg3);

	presetImgStr.Init("", 2);

	btn_fire->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedFire);
	btn_laser->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedLaser);
	btn_ice->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedIce);
	//btn_bite->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedBite);
	//btn_tail->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedTail);
	btn_speedup->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedSpeedUP);
	btn_defenceup->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedDefenceUP);
	btn_attackup->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedAttackUP);


	btn_skill_backtomain->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedSkillTOMain);
	btn_skill_save->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedSavePreset);
}

void UJE_SkillWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_SkillWidget::OnClickedFire()
{
	const FSlateBrush* FireBrush = &btn_fire->WidgetStyle.Normal;
	skillImg = Cast<UTexture2D>(FireBrush->GetResourceObject());

	SetSpecialPreset();
	
}

void UJE_SkillWidget::OnClickedLaser()
{
	const FSlateBrush* LaserBrush = &btn_laser->WidgetStyle.Normal;
	skillImg = Cast<UTexture2D>(LaserBrush->GetResourceObject());

	SetSpecialPreset();

}

void UJE_SkillWidget::OnClickedIce()
{
	const FSlateBrush* IceBrush = &btn_ice->WidgetStyle.Normal;
	skillImg = Cast<UTexture2D>(IceBrush->GetResourceObject());

	SetSpecialPreset();

}

void UJE_SkillWidget::OnClickedSpeedUP()
{
	const FSlateBrush* FootBrush = &btn_speedup->WidgetStyle.Normal;
	skillImg = Cast<UTexture2D>(FootBrush->GetResourceObject());

	SetBuffPreset();
	
}

void UJE_SkillWidget::OnClickedDefenceUP()
{
	const FSlateBrush* DefenceBrush = &btn_defenceup->WidgetStyle.Normal;
	skillImg = Cast<UTexture2D>(DefenceBrush->GetResourceObject());

	SetBuffPreset();

}

void UJE_SkillWidget::OnClickedAttackUP()
{
	const FSlateBrush* DefenceBrush = &btn_attackup->WidgetStyle.Normal;
	skillImg = Cast<UTexture2D>(DefenceBrush->GetResourceObject());

	SetBuffPreset();

}

void UJE_SkillWidget::SetBuffPreset()
{
	if(TrexPlayer) TrexPlayer->IsSetPreset = true;
	else basePlayer->IsSetPreset = true;

	int i = 0;

	presetImgArray[i] = Cast<UTexture2D>(presetArray[i]->GetBrush().GetResourceObject());

	if (presetImgArray[i] == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), i));

		presetArray[i]->SetVisibility(ESlateVisibility::Visible);
		presetArray[i]->SetBrushResourceObject(skillImg);
		//presetImgStr.Insert(*skillImg->GetName(), i);
		buffSkillImg = skillImg;
		presetImgStr[i] = *skillImg->GetName();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("%s"), *skillImg->GetName()));

		if (*skillImg->GetName() == presetImgStr[i])
		{
			presetArray[i]->SetBrushResourceObject(nullptr);
			presetArray[i]->SetVisibility(ESlateVisibility::Hidden);

			presetImgStr[i] = FString("");
		}
	}

}

void UJE_SkillWidget::SetSpecialPreset()
{
	if (TrexPlayer) TrexPlayer->IsSetPreset = true;
	else basePlayer->IsSetPreset = true;
	int i = 1;

	presetImgArray[i] = Cast<UTexture2D>(presetArray[i]->GetBrush().GetResourceObject());

	if (presetImgArray[i] == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), i));

		presetArray[i]->SetVisibility(ESlateVisibility::Visible);
		presetArray[i]->SetBrushResourceObject(skillImg);
		//presetImgStr.Insert(*skillImg->GetName(), i);
		specialSkillImg = skillImg;
		presetImgStr[i] = *skillImg->GetName();
	}
	else
	{
		if (*skillImg->GetName() == presetImgStr[i])
		{
			presetArray[i]->SetBrushResourceObject(nullptr);
			presetArray[i]->SetVisibility(ESlateVisibility::Hidden);

			presetImgStr[i] = FString("");
		}
	}
}

void UJE_SkillWidget::SetPreset()
{
	for (FString skillName : presetImgStr)
	{
		if(skillName == *skillImg->GetName()) return;
	}
	for (int i = 0; i < 2; i++)
	{
		presetImgArray[i] = Cast<UTexture2D>(presetArray[i]->GetBrush().GetResourceObject());

		if (presetImgArray[i] == nullptr)
		{
			GEngine->AddOnScreenDebugMessage( - 1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), i));

			presetArray[i]->SetVisibility(ESlateVisibility::Visible);
			presetArray[i]->SetBrushResourceObject(skillImg);
			presetImgStr.Insert(*skillImg->GetName(), i);
			break;
		}
	}
	/*presetImg1 = Cast<UTexture2D>(img_preset1->GetBrush().GetResourceObject());
	presetImg2 = Cast<UTexture2D>(img_preset2->GetBrush().GetResourceObject());
	presetImg3 = Cast<UTexture2D>(img_preset3->GetBrush().GetResourceObject());*/


	/*if (presetImg1 == nullptr)
	{
		img_preset1->SetBrushResourceObject(skillImg);
		presetImgStr.Add(*skillImg->GetName());

	}
	else if (presetImg2 == nullptr)
	{
		img_preset2->SetBrushResourceObject(skillImg);
		presetImgStr.Add(*skillImg->GetName());

	}
	else if (presetImg3 == nullptr)
	{
		img_preset3->SetBrushResourceObject(skillImg);
		presetImgStr.Add(*skillImg->GetName());

	}
	else
	{
		return;
	}*/

	for (FString inSkill : presetImgStr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, inSkill);
	}

	/*FString Message = presetImg1 == nullptr ? FString("None") : FString("Yes");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Message);

	FString Messag1 = presetImg2 == nullptr ? FString("None") : FString("Yes");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Messag1);

	FString Message2 = presetImg3 == nullptr ? FString("None") : FString("Yes");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Message2);*/
	
	//if()
}

void UJE_SkillWidget::FindPreset()
{
	for (int i = 0; i < 2; i++)
	{		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%d"),i));


		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, presetImgStr[i]);

		if (*skillImg->GetName() == presetImgStr[i])
		{
			presetArray[i]->SetBrushResourceObject(nullptr);
			presetArray[i]->SetVisibility(ESlateVisibility::Hidden);

			presetImgStr[i] = FString("");
			break;
		}

		/*if (!presetImgStr[i].IsEmpty())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, presetImgStr[i]);

			if (*skillImg->GetName() == presetImgStr[i])
			{
				UTexture2D* EmptyTexture = nullptr;
				presetArray[i]->SetBrushResourceObject(EmptyTexture);
				presetImgStr[i]="";
				break;
			}
		}*/
		

	}
}

void UJE_SkillWidget::OnClickedSkillTOMain()
{
	FString LevelName = TEXT("MainMap");
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}

void UJE_SkillWidget::OnClickedSavePreset()
{
	int32 ArrayNum = 3;
	for (int i=0; i< ArrayNum; i++)
	{
		if (BuffArray[i] == presetImgStr[0])
		{
			gi->playerSkillInfo.BuffskillNum = i;
			gi->playerSkillInfo.playerBuffSkillImg = buffSkillImg;
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *BuffArray[i]));
			
		}

		if (SpecialArray[i] == presetImgStr[1])
		{
			gi->playerSkillInfo.SpecialskillNum = i;
			gi->playerSkillInfo.playerSpecialSkillImg = specialSkillImg;
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("%s"), *SpecialArray[i]));
			
		}

	}
	if (TrexPlayer)
	{
		TrexPlayer->ServerSetSkills(gi->playerSkillInfo);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%d"), TrexPlayer->currBuffskillNum));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("%d"), TrexPlayer->currSpecialskillNum));
	}
	else
	{
		TrexPlayer->ServerSetSkills(gi->playerSkillInfo);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%d"), TrexPlayer->currBuffskillNum));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("%d"), TrexPlayer->currSpecialskillNum));
	}
	
	//player->IsSetPreset = false;
}
