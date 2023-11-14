// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JE_CharacterSpawActor.generated.h"

UCLASS()
class JURASSICLAND_API AJE_CharacterSpawActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AJE_CharacterSpawActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
