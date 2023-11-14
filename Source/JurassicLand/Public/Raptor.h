// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "Raptor.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API ARaptor : public ABasePlayer
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties	
	ARaptor();

// material
public:
	class UMaterialInterface* RapCustomMat;
	class UMaterialInterface* RapInitialMat;
	class UMaterialInterface* RapInitialMat1;

};
