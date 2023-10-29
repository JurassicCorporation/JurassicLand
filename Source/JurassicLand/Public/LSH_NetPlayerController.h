// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LSH_NetPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API ALSH_NetPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ALSH_NetPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySettings)
   class UWidgetComponent* nickNameComp;

	UPROPERTY()
	class UJE_NicknameWidget* nickNameUI;*/
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=MySettings)
	bool bBattleIn = false;

	class ABlueTrex* player;

	class ULSH_NetGameInstance* gi;


};
