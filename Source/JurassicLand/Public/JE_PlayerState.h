// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JE_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API AJE_PlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	class ULSH_NetGameInstance* gi;
	
};
