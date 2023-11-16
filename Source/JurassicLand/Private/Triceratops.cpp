// Fill out your copyright notice in the Description page of Project Settings.


#include "Triceratops.h"

ATriceratops::ATriceratops()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempTriBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"));

	if (tempTriBody.Succeeded())
	{
		PlayerBody->SetSkeletalMesh(tempTriBody.Object);
		PlayerBody->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		PlayerBody->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		PlayerBody->SetRelativeScale3D(FVector(1.f));
	}

	ConstructorHelpers::FObjectFinder<UMaterial> TribodyMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/4_SK/Triceratops/Materials/MI_Triceratops1.MI_Triceratops1'"));
	if (TribodyMat.Succeeded())
	{
		TriMat = TribodyMat.Object;
		PlayerBody->SetMaterial(0, TriMat);
	}

}