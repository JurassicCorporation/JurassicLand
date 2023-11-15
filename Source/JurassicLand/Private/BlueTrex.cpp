// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueTrex.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimationAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/TimerHandle.h"
#include "JE_NicknameComponent.h"
#include "LSH_NetGameInstance.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"
#include "JE_CustomItemActor.h"
#include "JE_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h" 
#include "UObject/ConstructorHelpers.h"
#include "JE_CustomPlayerController.h"
#include "JE_InBattleController.h"
#include "JE_BattleWidget.h"
#include "Raptor.h"
#include "GameFramework/PlayerState.h"
#include "JE_PlayerState.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(TRexTailAttack);

// Sets default values
ABlueTrex::ABlueTrex()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*-------- Skeletal Mesh Component Setting --------*/
	TRexBody = GetMesh();

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlueTRex/SK_TRex.SK_TRex'"));
	if (tempBody.Succeeded())
	{
		TRexBody->SetSkeletalMesh(tempBody.Object);
		TRexBody->SetRelativeScale3D(FVector(0.5f));
		TRexBody->SetRelativeLocation(FVector(0, 0, -87.0f));
		TRexBody->SetRelativeRotation(FRotator(0, -90.0f, 0));
	}
	/*--------- Spring Arm Component Setting -----------*/
//	TRexEyeArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TRexEyeArm"));
//	TRexEyeArm->SetupAttachment(GetCapsuleComponent());
//	TRexEyeArm->SetRelativeLocation(FVector(0.0f,0.0f,100.0f));
//	TRexEyeArm->SetRelativeRotation(FRotator(-15.0f,0.0f,0.0f));
//
	bUseControllerRotationYaw = true;
//	TRexEyeArm->bUsePawnControlRotation = true;
//	//TRexEye->bUsePawnControlRotation = false;
//	
//
//	/*--------- Camera Component Setting --------*/
//	TRexEye = CreateDefaultSubobject<UCameraComponent>(TEXT("TRexEye"));
//	TRexEye->SetupAttachment(TRexEyeArm);
//// 	TRexEye->SetWorldLocation(FVector(0.0f,0.0f,0.0f));
//// 	TRexEye->SetWorldRotation(FRotator(0.0f,0.0f,0.0f));

	/*--------- Enhanced Input Setting ----------*/
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>tempIMC_TRex(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/7_MISC/Input/IMC_Player.IMC_Player'"));
	if (tempIMC_TRex.Succeeded())
	{
		IMC_TRex = tempIMC_TRex.Object;
	}


	CharacterMovement = GetCharacterMovement();

	//코인
	currentCoin = initialCoin;

	//Color Material
	ConstructorHelpers::FObjectFinder<UMaterial> bodyMat(TEXT("/Script/Engine.Material'/Game/4_SK/BlueTRex/MAT_TREX_ColorChange.MAT_TREX_ColorChange'"));
	if (bodyMat.Succeeded())
	{
		CustomMat = bodyMat.Object;
	}

	ConstructorHelpers::FObjectFinder<UMaterial> inibodyMat(TEXT("/Script/Engine.Material'/Game/4_SK/BlueTRex/MAT_TRex.MAT_TRex'"));
	if (bodyMat.Succeeded())
	{
		InitialMat = inibodyMat.Object;

	}

	//Trex AnimBlueprint
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> trexAnim(*animPathList[playerMeshNumber]);

	if (trexAnim.Succeeded())
	{
		trexAnimClass = trexAnim.Object;
	}

}

// Called when the game starts or when spawned
void ABlueTrex::BeginPlay()
{
	Super::BeginPlay();
	/*-----------Enhanced Input IMC Set up---------*/
	pc = Cast<APlayerController>(GetController());
	if (pc != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
			SubSystem->AddMappingContext(IMC_TRex, 0);
	}
	
	// 게임인스턴스에 플레이어 정보 불러오기
	gi = GetGameInstance<ULSH_NetGameInstance>();	

	// 스킬
	ServerSetSkills(gi->playerSkillInfo);

	if (GetController() != nullptr && GetController()->IsLocalPlayerController())
	{
		if (HasAuthority())
		{
			// 플레이어 스테이트 불러오기
			ps = GetController()->GetPlayerState<AJE_PlayerState>();

			ServerSetInitInfo();
			ServerSetCustomItemInfo();
			//ServerSetSkills(gi->playerSkillInfo);

			FTimerHandle initHandler;
			GetWorldTimerManager().SetTimer(initHandler, this, &ABlueTrex::InitializePlayer, 3.0f, false);
		}
		else
		{
			ServerGetplayerState();
		}
			
		
		
	}

	// 캐릭터 초기화 지연 실행 // 1초는 너무 빠름
	//FTimerHandle initHandler;
	//GetWorldTimerManager().SetTimer(initHandler, this, &ABlueTrex::InitializePlayer, 3.0f, false);

}

// Called every frame
void ABlueTrex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!btickStop)
	{
		if (TRexHP <= 0.f)
		{
			bIsHpZero = true;
			gi->isEnd = true;
			btickStop = true;
		}
	}
	

}

// Called to bind functionality to input
void ABlueTrex::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*-----------Enhanced Input Bind Setting---------*/
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		SetupPlayerEnhancedInputComponent(EnhancedInputComponent, inputActions);
	}
}

void ABlueTrex::SetupPlayerEnhancedInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> InputActions)
{
	EnhancedInputComponent->BindAction(InputActions[0], ETriggerEvent::Triggered, this, &ABlueTrex::TRexMove);
	EnhancedInputComponent->BindAction(InputActions[1],ETriggerEvent::Triggered,this,&ABlueTrex::TRexLook);
	EnhancedInputComponent->BindAction(InputActions[2], ETriggerEvent::Started, this, &ABlueTrex::TRexTailAttack);
}

void ABlueTrex::TRexMove(const FInputActionValue& Val)
{
	FVector2D tempVal = Val.Get<FVector2D>();
	float valY = tempVal.Y;
	float valX = tempVal.X;

	FRotator CurrControlRotation = GetControlRotation();
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f, CurrControlRotation.Yaw, CurrControlRotation.Roll)), valX);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f, CurrControlRotation.Yaw, 0.0f)), valY);
	

}

void ABlueTrex::TRexLook(const FInputActionValue& Val)
{
	FVector2D tempVal = Val.Get<FVector2D>();
	float valX = tempVal.X;
	float valY = tempVal.Y;
// 
	AddControllerYawInput(valX*0.4);
	AddControllerPitchInput(valY);

}

void ABlueTrex::TRexTailAttack_Implementation(const FInputActionValue& Val)
{

	if(TailAttackAnim!=nullptr&&TailAttack==false)
	{
		
		TailAttack = true;
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		this->bUseControllerRotationYaw = false;
		
	}
}


void ABlueTrex::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlueTrex, TRexHP);
	DOREPLIFETIME(ABlueTrex, bIsHpZero);
	DOREPLIFETIME(ABlueTrex, initialCoin);
	DOREPLIFETIME(ABlueTrex, currentCoin);
	DOREPLIFETIME(ABlueTrex, playerName);
	DOREPLIFETIME(ABlueTrex, playerColor);
	DOREPLIFETIME(ABlueTrex, playerMeshNumber);
	DOREPLIFETIME(ABlueTrex, playerHat);
	DOREPLIFETIME(ABlueTrex, playerGlasses);
	DOREPLIFETIME(ABlueTrex, playerShoes);
	DOREPLIFETIME(ABlueTrex, HatTag);
	DOREPLIFETIME(ABlueTrex, GlassesTag);
	DOREPLIFETIME(ABlueTrex, ShoesTag);
	DOREPLIFETIME(ABlueTrex, IsSetPreset);
	DOREPLIFETIME(ABlueTrex, currBuffskillNum);
	DOREPLIFETIME(ABlueTrex, currSpecialskillNum);
	DOREPLIFETIME(ABlueTrex, currplayerSpecialSkillImg);
	DOREPLIFETIME(ABlueTrex, currplayerBuffSkillImg);
	DOREPLIFETIME(ABlueTrex, buffCool);
	DOREPLIFETIME(ABlueTrex, SpecialCool);


}

void ABlueTrex::ServerGetplayerState_Implementation()
{
	if (GetController() != nullptr)
	{
		if (AJE_PlayerState* clinetPS = GetController()->GetPlayerState<AJE_PlayerState>())
		{
			//ServerSetInitInfo();
			//ServerSetCustomItemInfo();

			playerName = clinetPS->pCustomInfo.pName;
			playerColor = clinetPS->pCustomInfo.pColor;
			playerMeshNumber = clinetPS->pCustomInfo.pMeshNum;

			playerHat = clinetPS->pCustomItemInfo.pHatName;
			playerGlasses = clinetPS->pCustomItemInfo.pGlassesName;
			playerShoes = clinetPS->pCustomItemInfo.pShoesName;

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Client"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, clinetPS->pCustomInfo.pColor.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, clinetPS->pCustomItemInfo.pHatName.ToString());

			FTimerHandle initHandler;
			GetWorldTimerManager().SetTimer(initHandler, this, &ABlueTrex::InitializePlayer, 3.0f, false);
		}
	}
}

// 초기 설정 함수
void ABlueTrex::InitializePlayer()
{

	if (gi->playerCustomInfo.dinoMeshNum != 1)
	{
		// 게임인스턴스에 커스텀 정보 불러오기
		InitialCustomMulti();

		// 커스텀 컬러 설정
		//ServerSetInitInfo();
		CustomColor();

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Initial"));
	}
	
}

void ABlueTrex::InitialCustomMulti_Implementation()
{
	// 게임인스턴스에 커스텀 아이템 정보 불러오기
	//ServerSetCustomItemInfo();
}

void ABlueTrex::SetColor()
{
	//playerColor = gi->playerCustomInfo.dinoColor;
	// 게임인스턴스에 커스텀 정보 불러오기
	//ServerSetInitInfo();

	// 불러온 정보로 컬러 설정
	CustomColor();
}

void ABlueTrex::SetMesh()
{
	ServerSetInitInfo();

	CustomMesh();
}

void ABlueTrex::CustomColor()
{
	
	// 컬러 설정
	if (IsColorCustom)
	{
		if (!IsColor)
		{
			dynamicMat1 = UMaterialInstanceDynamic::Create(CustomMat, this);
			GetMesh()->SetMaterial(0, dynamicMat1);
		}
	}
	else
	{
		if (gi->IsColorChanged) currMat = CustomMat;
		else currMat = InitialMat;

		dynamicMat1 = UMaterialInstanceDynamic::Create(currMat, this);

		GetMesh()->SetMaterial(0, dynamicMat1);

	}


	dynamicMat1->SetVectorParameterValue(FName("MyColor"), playerColor);
}

void ABlueTrex::CustomMesh()
{
	// Mesh
	USkeletalMesh* selectedMesh = LoadObject<USkeletalMesh>(NULL, *meshPathList[playerMeshNumber], NULL, LOAD_None, NULL);
	if (selectedMesh != nullptr)
	{
		GetMesh()->SetSkeletalMesh(selectedMesh);
		if (playerMeshNumber == 1)
		{
			GetMesh()->SetRelativeScale3D(FVector(2.0f));
		}
		else
		{
			GetMesh()->SetRelativeScale3D(FVector(0.5f));
		}
	}

	//Material
	UMaterial* selectedMat = LoadObject<UMaterial>(NULL, *matPathList[playerMeshNumber], NULL, LOAD_None, NULL);
	if (selectedMat != nullptr)
	{
		UMaterialInstanceDynamic* selectedDynamicMat = UMaterialInstanceDynamic::Create(selectedMat, this);

		GetMesh()->SetMaterial(0, selectedDynamicMat);

	}

	UAnimationAsset* selectedAnim = LoadObject<UAnimationAsset>(NULL, *animPathList[playerMeshNumber], NULL, LOAD_None, NULL);
	if (playerMeshNumber > 0)
	{
		if (selectedAnim != nullptr)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			GetMesh()->PlayAnimation(selectedAnim, true);
		}
	}
	else
	{
		if (trexAnimClass != nullptr)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(trexAnimClass->GeneratedClass);
		}
		
	}
	
}

void ABlueTrex::SaveSkills()
{
	
}

void ABlueTrex::ServerSetSkills_Implementation(FPlayerSkillInfo skillInfo)
{
	currBuffskillNum = skillInfo.BuffskillNum;
	currSpecialskillNum = skillInfo.SpecialskillNum;
	currplayerBuffSkillImg = skillInfo.playerBuffSkillImg;
	currplayerSpecialSkillImg = skillInfo.playerSpecialSkillImg;
}

void ABlueTrex::getSkillCool()
{
	AJE_InBattleController* battlepc = Cast<AJE_InBattleController>(GetController());

 	if (battlepc != nullptr && battlepc->IsLocalPlayerController())
 	{
		//battleUI = CreateWidget<UJE_BattleWidget>(GetWorld(), battlewidget);
 		if(battleUI != nullptr) battleUI->SetSkillCool(coolTimeIndex);
 	}
}

void ABlueTrex::ServerSetInitInfo_Implementation()
{
	playerName = ps->pCustomInfo.pName;
	playerColor = ps->pCustomInfo.pColor;
	playerMeshNumber = ps->pCustomInfo.pMeshNum;

}

void ABlueTrex::ServerSetCustomItemInfo_Implementation()
{
	playerHat = ps->pCustomItemInfo.pHatName;
	playerGlasses = ps->pCustomItemInfo.pGlassesName;
	playerShoes = ps->pCustomItemInfo.pShoesName;

}

// 현재 플레이어의 커스텀 아이템 가져오기
void ABlueTrex::GetCustomItemData()
{
	TArray<AJE_CustomItemActor*> allItem;

	for (TActorIterator<AJE_CustomItemActor> Itr(GetWorld()); Itr; ++Itr)
	{
		AJE_CustomItemActor* currActor = *Itr;

		if (currActor->ActorHasTag("Hat"))
		{
			currentHat = currActor;

			const TArray<FName>& myTags = currActor->Tags;
			if (myTags.IsValidIndex(1))
			{
				HatTag = myTags[1];
			}
		}
		else if (currActor->ActorHasTag("Glasses"))
		{
			currentGlasses = currActor;
			const TArray<FName>& myTags = currActor->Tags;
			if (myTags.IsValidIndex(1))
			{
				GlassesTag = myTags[1];
			}
		}
		else if (currActor->ActorHasTag("Shoes"))
		{
			currentShoes = currActor;
			const TArray<FName>& myTags = currActor->Tags;
			if (myTags.IsValidIndex(1))
			{
				ShoesTag = myTags[1];
			}
		}
		else
		{
			continue;
		}
	}

	/*for (TActorIterator<AJE_CustomItemActor> Itr(GetWorld()); Itr; ++Itr)
	{
		AJE_CustomItemActor* currActor = *Itr;

		if (currActor->ActorHasTag("Hat"))
		{
			currentHat = currActor;
		}
		else if (currActor->ActorHasTag("Glasses"))
		{
			currentGlasses = currActor;
		}
		else if (currActor->ActorHasTag("Shoes"))
		{
			currentShoes = currActor;
		}
		else
		{
			continue;
		}
	}*/

	/*ps->pCustomItemInfo.pHatName = HatTag;
	ps->pCustomItemInfo.pGlassesName = GlassesTag;
	ps->pCustomItemInfo.pShoesName = ShoesTag;*/

	gi->playerCustomItemInfo.HatTagInstance = HatTag;
	gi->playerCustomItemInfo.GlassesTagInstance = GlassesTag;
	gi->playerCustomItemInfo.ShoesTagInstance = ShoesTag;
	
}

void ABlueTrex::SaveCustomItemData()
{
	// 현재 플레이어의 커스텀 아이템 가져오기
	GetCustomItemData();

// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, ps->pCustomItemInfo.pHatName.ToString());
// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, ps->pCustomItemInfo.pGlassesName.ToString());
// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, ps->pCustomItemInfo.pShoesName.ToString());

	// 플레이트 스테이트 커스텀 아이템 게임 인스턴스에 함수
	//ps->SetInstanceCustomItemInfo();

	MySaveGame = Cast<UJE_SaveGame>(UGameplayStatics::CreateSaveGameObject(UJE_SaveGame::StaticClass()));

	//// 장신구 블루프린트 액터 savegame에 저장
	//MySaveGame->myHat = currentHat;
	//MySaveGame->myGlasses = currentGlasses;
	//MySaveGame->myShoes = currentShoes;

	// 장신구 블루프린트 액터 태그 savegame에 저장
	MySaveGame->myHatTag = HatTag;
	MySaveGame->myGlassesTag = GlassesTag;
	MySaveGame->myShoesTag = ShoesTag;

	UGameplayStatics::SaveGameToSlot(MySaveGame, "MyCustomSaveSlot", 0);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Save"));
}

void ABlueTrex::LoadCustomItemData()
{
	MySaveGame = Cast<UJE_SaveGame>(UGameplayStatics::LoadGameFromSlot("MyCustomSaveSlot", 0));

	//if (MySaveGame == nullptr)
	//{
	//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Nothing"));
	//	return;
	//}
	//else
	//{
	//	if (MySaveGame->myHatTag.IsValid())
	//	{
	//		/*FString Message = FString::Printf(TEXT("%s"), *MySaveGame->myHat->GetName());
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);*/

	//		//FString Message1 = FString("Hat : ") + gi->playerCustomItemInfo.HatTagInstance.ToString();
	//		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message1);

	//	}

	//	if (MySaveGame->myGlassesTag.IsValid())
	//	{
	//		//FString Message1 = FString("Glasses : ") + gi->playerCustomItemInfo.GlassesTagInstance.ToString();
	//		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message1);

	//	}

	//	if (MySaveGame->myShoesTag.IsValid())
	//	{
	//		//FString Message1 = FString("Shoes : ") + gi->playerCustomItemInfo.ShoesTagInstance.ToString();
	//		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message1);

	//	}

	//	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Load"));
	//}
}
