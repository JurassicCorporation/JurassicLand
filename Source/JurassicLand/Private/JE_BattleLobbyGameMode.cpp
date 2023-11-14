// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleLobbyGameMode.h"
#include "BlueTrex.h"
#include "BasePlayer.h"
#include "Raptor.h"
#include "LSH_NetGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


AJE_BattleLobbyGameMode::AJE_BattleLobbyGameMode()
{
	if (GetWorld())
	{
		if (ULSH_NetGameInstance* myGI = Cast<ULSH_NetGameInstance>(GetWorld()->GetGameInstance()))
		{
			if (myGI->playerCustomInfo.dinoMeshNum == 1)
			{
				static ConstructorHelpers::FClassFinder<ARaptor> RaptorPlayerClass(TEXT("/Game/2_BP/BP_Raptor"));
				if (RaptorPlayerClass.Class != NULL)
				{
					DefaultPawnClass = RaptorPlayerClass.Class;
				}
				//if (ARaptor::StaticClass() != nullptr)
				//{
				//	DefaultPawnClass = ARaptor::StaticClass();
				//}
			}
			else
			{
					static ConstructorHelpers::FClassFinder<ABlueTrex> TrexPlayerClass(TEXT("/Game/2_BP/BP_BlueTRex"));
				if (TrexPlayerClass.Class != NULL)
				{
					DefaultPawnClass = TrexPlayerClass.Class;
				}
			}
		}
	}
	
}

void AJE_BattleLobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	gi = GetGameInstance<ULSH_NetGameInstance>();
	if (gi->playerCustomInfo.dinoMeshNum == 1)
	{
		ABlueTrex* playertrex = Cast<ABlueTrex>(UGameplayStatics::GetActorOfClass(GetWorld(), ABlueTrex::StaticClass()));

		if(playertrex) playertrex->Destroy();

		ARaptor* playerRaptor = GetWorld()->SpawnActor<ARaptor>(gi->raptor, FVector((760.0f, -500.0f, 1000.0f)), FRotator());

		GetWorld()->GetFirstPlayerController()->Possess(playerRaptor);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%s"), *GetWorld()->GetFirstPlayerController()->GetName()));

		//playerRaptor->pc = Cast<APlayerController>(GetOwner());
	}
}
