// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_NicknameComponent.h"
#include "Blueprint/UserWidget.h"

UJE_NicknameComponent::UJE_NicknameComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UJE_NicknameComponent::BeginPlay()
{
	Super::BeginPlay();

	// �г���	ui �ν��Ͻ� �����
	nickNameUI = CreateWidget(GetWorld(), nickNameWidget);

	if (nickNameUI != nullptr)
	{
		nickNameUI->AddToViewport();
	}
}


void UJE_NicknameComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

