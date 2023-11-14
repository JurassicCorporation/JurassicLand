// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JE_BattleLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API AJE_BattleLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJE_BattleLobbyGameMode();

protected:
	virtual void BeginPlay() override;

public:
	class ULSH_NetGameInstance* gi;
	
};
