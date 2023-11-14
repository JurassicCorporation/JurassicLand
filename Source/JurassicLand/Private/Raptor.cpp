// Fill out your copyright notice in the Description page of Project Settings.


#include "Raptor.h"

ARaptor::ARaptor()
{

	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRaptorBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Raptor/Model/Raptor_HumanIK.Raptor_HumanIK'"));
		
	if (tempRaptorBody.Succeeded())
	{
		
		PlayerBody->SetSkeletalMesh(tempRaptorBody.Object);
		PlayerBody->SetRelativeLocation(FVector(0.0f,0.0f,-88.0f));
		PlayerBody->SetRelativeRotation(FRotator(0.0,-90.0f,0.0f));
		PlayerBody->SetRelativeScale3D(FVector(3.0f));
	}

	//material 초기 설정
	ConstructorHelpers::FObjectFinder<UMaterial> rapbodyMat(TEXT("/Script/Engine.Material'/Game/4_SK/Raptor/Model/DromaMESH_DromaBodyM.DromaMESH_DromaBodyM'"));
	if (rapbodyMat.Succeeded())
	{
		CustomMat = rapbodyMat.Object;
		PlayerBody->SetMaterial(1, RapInitialMat);
	}

	ConstructorHelpers::FObjectFinder<UMaterial> rapbodyMat1(TEXT("/Script/Engine.Material'/Game/4_SK/Raptor/Model/DromaMESH_Material__26.DromaMESH_Material__26'"));
	if (rapbodyMat1.Succeeded())
	{
		InitialMat = rapbodyMat1.Object;
		PlayerBody->SetMaterial(0, RapInitialMat1);

	}
}
