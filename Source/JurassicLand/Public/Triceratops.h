// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "Triceratops.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API ATriceratops : public ABasePlayer
{
	GENERATED_BODY()

public:
	ATriceratops();

public:
	class UMaterialInterface* TriMat;
	
};
