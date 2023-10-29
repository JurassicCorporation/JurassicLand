// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JE_PlayerState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class JURASSICLAND_API AJE_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	FString PlayerName;

	UFUNCTION()
	void SetPlayerName(const FString& NewPlayerName);
	
};
