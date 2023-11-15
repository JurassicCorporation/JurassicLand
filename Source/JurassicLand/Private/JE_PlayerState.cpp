// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_PlayerState.h"
#include "LSH_NetGameInstance.h"


void AJE_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<ULSH_NetGameInstance>(GetGameInstance());


}
