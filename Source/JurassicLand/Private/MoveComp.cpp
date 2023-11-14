// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComp.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"
#include "BasePlayer.h"
// Sets default values for this component's properties
UMoveComp::UMoveComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	player = GetOwner<ABasePlayer>();
}


// Called every frame
void UMoveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveComp::SetupPlayerEnhancedInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	enhancedInputComponent->BindAction(inputActions[0], ETriggerEvent::Triggered, this, &UMoveComp::PlayerMove);

	enhancedInputComponent->BindAction(inputActions[1], ETriggerEvent::Triggered, this, &UMoveComp::PlayerLook);
	
				
	//Special Skill 'Q' key
	//enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Triggered, this, &UMoveComp::PlayerLook);*/
	
	//Buff Skill 'e' key
	/*enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Triggered, this, &UMoveComp::PlayerLook);*/
	
	//Basic Attack - TailAttack '1' key
	//BP·Î ±¸Çö

	//Basic Attack - BiteAttack '2' key
	/*enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Triggered, this, &UMoveComp::PlayerLook);*/

	//Basic Attack - RoarAttack '3' key
	/*enhancedInputComponent->BindAction(inputActions[2], ETriggerEvent::Triggered, this, &UMoveComp::PlayerLook);*/

}

void UMoveComp::PlayerMove(const FInputActionValue& Val)
{
	FVector2D tempVal = Val.Get<FVector2D>();
	float valY = tempVal.Y;
	float valX = tempVal.X;

	FRotator CurrControlRotation = player->
		pc->GetControlRotation();
	player->AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f, CurrControlRotation.Yaw, CurrControlRotation.Roll)), valX);
	player->AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f, CurrControlRotation.Yaw, 0.0f)), valY);

	GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Emerald,TEXT("MoveMove"));
}

void UMoveComp::PlayerLook(const FInputActionValue& Val)
{

	FVector2D tempVal = Val.Get<FVector2D>();
	float valX = tempVal.X;
	float valY = tempVal.Y;
	// 
	player->AddControllerYawInput(valX * 0.5);
	player->AddControllerPitchInput(valY);
}


