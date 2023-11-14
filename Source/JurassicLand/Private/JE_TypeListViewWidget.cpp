// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_TypeListViewWidget.h"
#include "LSH_NetGameInstance.h"
#include "Components/Button.h"
#include "BlueTrex.h"
#include "Raptor.h"
#include "Kismet/GameplayStatics.h"
#include "JE_SkillModeBase.h"
#include "JE_CharacterSpawActor.h"


void UJE_TypeListViewWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();

	skillmode = Cast<AJE_SkillModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	spawnLocActor = Cast<AJE_CharacterSpawActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AJE_CharacterSpawActor::StaticClass()));

	//baseplayer = GetOwningPlayerPawn<ABasePlayer>();
	//player->GetController();
	
	btn_type->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType);
	btn_type_1->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType2);
	btn_type_2->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType3);
	btn_type_3->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType4);
}

void UJE_TypeListViewWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	
}

void UJE_TypeListViewWidget::OnClickedType()
{
	gi->playerCustomInfo.dinoMeshNum = 0;

	player->SetMesh();
}

void UJE_TypeListViewWidget::OnClickedType2()
{
	gi->playerCustomInfo.dinoMeshNum = 1;

	//raptorplayer = GetWorld()->SpawnActor<ARaptor>(gi->raptor, spawnLocActor->GetActorLocation(), spawnLocActor->GetActorRotation());

	//gi->dinoraptor = raptorplayer;

	//gi->dinocharacter = Cast<ARaptor>(ARaptor::StaticClass());
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%s"), *gi->dinocharacter->GetName()));
	/*if (skillmode)
	{
		skillmode->DefaultPawnClass = ARaptor::StaticClass();
	}*/
	player->SetMesh();
}

void UJE_TypeListViewWidget::OnClickedType3()
{
	gi->playerCustomInfo.dinoMeshNum = 2;

	player->SetMesh();
}

void UJE_TypeListViewWidget::OnClickedType4()
{
	gi->playerCustomInfo.dinoMeshNum = 3;

	player->SetMesh();
}
