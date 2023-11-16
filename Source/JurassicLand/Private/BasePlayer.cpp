// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
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
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MoveComp.h"
#include "Raptor.h"
#include "LSH_NetPlayerController.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Skeletal Mesh Component
	PlayerBody = GetMesh();
/*	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Raptor/Model/Raptor_HumanIK.Raptor_HumanIK'"));*/

	PlayerBody->SetupAttachment(RootComponent);

// 	if (tempBody.Succeeded())
// 	{
// 		PlayerBody->SetSkeletalMesh(tempBody.Object);
// 	}

	//Spring Arm
	PlayerCamArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCamArm"));
	PlayerCamArm->SetupAttachment(RootComponent);
	PlayerCamArm->TargetArmLength = 400.0f;
	PlayerCamArm->SocketOffset = FVector(0.0f, 0.0f, 200.0f);

	//Camera
	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	PlayerCam->SetupAttachment(PlayerCamArm);
	PlayerCam->SetRelativeRotation(FRotator(0.0, 17.0f, 0.0f));
	PlayerCam->FieldOfView = 75.0f;

	//HP Bar Widget
	HP_Bar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_Bar"));
	HP_Bar->SetupAttachment(PlayerBody);
	ConstructorHelpers::FClassFinder<UUserWidget> tempHPBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2_BP/Widget/BP_LSH_BPHPWidget.BP_LSH_BPHPWidget_C'"));
	if (tempHPBar.Succeeded())
	{
		HP_Bar->SetWidgetClass(tempHPBar.Class);
	}

	//collision_Head
	PlayerHeadCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerHeadCollision"));
	PlayerHeadCollision->SetupAttachment(RootComponent);
	/*AttachToComponent(PlayerBody,FAttachmentTransformRules::KeepRelativeTransform, TEXT("bn_Head_10"));*/

	//collision_Upper Body
	/*PlayerUpperBodyCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerUpperCollision"));
	PlayerUpperBodyCollision->SetupAttachment(RootComponent);*/
	/*AttachToComponent(PlayerBody, FAttachmentTransformRules::KeepRelativeTransform, TEXT("bn_Neck_7"));*/

	//collision_Tail
	PlayerTailCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerTailCollision"));
	PlayerTailCollision->SetupAttachment(RootComponent);
	/*AttachToComponent(PlayerBody, FAttachmentTransformRules::KeepRelativeTransform, TEXT("bn_Tail05_71"));*/

	//Enhanced Input
	ConstructorHelpers::FObjectFinder<UInputMappingContext>tempEnhancedInputComp(TEXT("/Game/7_MISC/Input/IMC_Player.IMC_Player"));
	if (tempEnhancedInputComp.Succeeded())
	{
		IMC_Player = tempEnhancedInputComp.Object;
	}

	MoveComp = CreateDefaultSubobject<UMoveComp>(TEXT("MoveComp"));
	

	//pc = Cast<APlayerController>(GetController());
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%s"), *MoveComp->GetOwner()->GetName()));	

	pc = Cast<APlayerController>(GetController());


	if (pc != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(IMC_Player, 0);	
		}
	}

	// 닉네임	
	gi = GetGameInstance<ULSH_NetGameInstance>();

	if (GetController() != nullptr && GetController()->IsLocalPlayerController())
	{
		ServerSetInitInfo(gi->playerCustomInfo);
		ServerSetCustomItemInfo(gi->playerCustomItemInfo);
	}

	ARaptor* playerRaptor = Cast<ARaptor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//if (playerRaptor)
	//{
	//	return;
	//}
	//else
	//{
	//	// 캐릭터 초기화 지연 실행
	//	FTimerHandle initHandler;
	//	GetWorldTimerManager().SetTimer(initHandler, this, &ABasePlayer::InitializePlayer, 1.0f, false);
	//}
	
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!btickStop)
	{
		if (State_HP <= 0.f)
		{
			bIsHpZero = true;
			gi->isEnd = true;
			btickStop = true;
		}
	}

}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		MoveComp->SetupPlayerEnhancedInputComponent(EnhancedInputComponent, inputActions);
	}
	PlayerInputComponent->BindAxis(TEXT("Horizontal"),this,&ABasePlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"),this,&ABasePlayer::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Look_Horizontal"),this,&ABasePlayer::Look_Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Look_Vertical"),this,&ABasePlayer::Look_Vertical);


}




void ABasePlayer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasePlayer, bRoar);
	DOREPLIFETIME(ABasePlayer, bTailAttack);
	DOREPLIFETIME(ABasePlayer, bLaserBeam);
	DOREPLIFETIME(ABasePlayer, State_HP);
 	DOREPLIFETIME(ABasePlayer, bIsHpZero);
 	DOREPLIFETIME(ABasePlayer, initialCoin);
 	DOREPLIFETIME(ABasePlayer, currentCoin);
 	DOREPLIFETIME(ABasePlayer, playerName);
 	DOREPLIFETIME(ABasePlayer, playerColor);
 	DOREPLIFETIME(ABasePlayer, playerMeshNumber);
 	DOREPLIFETIME(ABasePlayer, playerHat);
 	DOREPLIFETIME(ABasePlayer, playerGlasses);
 	DOREPLIFETIME(ABasePlayer, playerShoes);
 	DOREPLIFETIME(ABasePlayer, HatTag);
 	DOREPLIFETIME(ABasePlayer, GlassesTag);
 	DOREPLIFETIME(ABasePlayer, ShoesTag);
	DOREPLIFETIME(ABasePlayer, IsSetPreset);
	DOREPLIFETIME(ABasePlayer, currBuffskillNum);
	DOREPLIFETIME(ABasePlayer, currSpecialskillNum);
	DOREPLIFETIME(ABasePlayer, currplayerSpecialSkillImg);
	DOREPLIFETIME(ABasePlayer, currplayerBuffSkillImg);
	DOREPLIFETIME(ABasePlayer, buffCool);
	DOREPLIFETIME(ABasePlayer, SpecialCool);


}

void ABasePlayer::InitializePlayer()
{
	// 닉네임 설정
	/*if (nicknameText)
	{
		nicknameText->SetText(FText::FromString(playerName));
	}*/
	if (gi->playerCustomInfo.dinoMeshNum == 1)
	{
		InitialCustomMulti();

		CustomColor();
	}

}

void ABasePlayer::SetColor()
{
	ServerSetInitInfo(gi->playerCustomInfo);

	CustomColor();

	//// 컬러 설정
	//if (IsColorCustom)
	//{
	//	if (!IsColor)
	//	{	
	//		dynamicMat1 = UMaterialInstanceDynamic::Create(CustomMat, this);
	//		GetMesh()->SetMaterial(0, dynamicMat1);
	//	}
	//}
	//else
	//{
	//	if (gi->IsColorChanged) currMat = CustomMat;
	//	else currMat = InitialMat;

	//	dynamicMat1 = UMaterialInstanceDynamic::Create(currMat, this);

	//	GetMesh()->SetMaterial(0, dynamicMat1);

	//}
	//	

	//dynamicMat1->SetVectorParameterValue(FName("MyColor"), playerColor);
}

void ABasePlayer::GetCustomItemData()
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

	for (TActorIterator<AJE_CustomItemActor> Itr(GetWorld()); Itr; ++Itr)
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
	}

	gi->playerCustomItemInfo.HatTagInstance = HatTag;
	gi->playerCustomItemInfo.GlassesTagInstance = GlassesTag;
	gi->playerCustomItemInfo.ShoesTagInstance = ShoesTag;
}

void ABasePlayer::SaveCustomItemData()
{
	GetCustomItemData();

	MySaveGame = Cast<UJE_SaveGame>(UGameplayStatics::CreateSaveGameObject(UJE_SaveGame::StaticClass()));

	// 장신구 블루프린트 액터 savegame에 저장
	MySaveGame->myHat = currentHat;
	MySaveGame->myGlasses = currentGlasses;
	MySaveGame->myShoes = currentShoes;

	// 장신구 블루프린트 액터 태그 savegame에 저장
	MySaveGame->myHatTag = HatTag;
	MySaveGame->myGlassesTag = GlassesTag;
	MySaveGame->myShoesTag = ShoesTag;

	UGameplayStatics::SaveGameToSlot(MySaveGame, "MyCustomSaveSlot", 0);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Save"));
}

void ABasePlayer::LoadCustomItemData()
{
	MySaveGame = Cast<UJE_SaveGame>(UGameplayStatics::LoadGameFromSlot("MyCustomSaveSlot", 0));


	if (MySaveGame == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Nothing"));
		return;
	}
	else
	{
		if (MySaveGame->myHatTag.IsValid())
		{
			/*FString Message = FString::Printf(TEXT("%s"), *MySaveGame->myHat->GetName());
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);*/

			FString Message1 = FString("Hat : ") + gi->playerCustomItemInfo.HatTagInstance.ToString();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message1);

		}

		if (MySaveGame->myGlassesTag.IsValid())
		{
			//FString Message1 = FString("Glasses : ") + gi->playerCustomItemInfo.GlassesTagInstance.ToString();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message1);

		}

		if (MySaveGame->myShoesTag.IsValid())
		{
// 			FString Message1 = FString("Shoes : ") + gi->playerCustomItemInfo.ShoesTagInstance.ToString();
// 			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message1);

		}

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Load"));
	}
}

void ABasePlayer::SetMesh()
{
	ServerSetInitInfo(gi->playerCustomInfo);

	CustomMesh();
}

void ABasePlayer::CustomColor()
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

void ABasePlayer::CustomMesh()
{
	// Mesh
	USkeletalMesh* selectedMesh = LoadObject<USkeletalMesh>(NULL, *meshPathList[playerMeshNumber], NULL, LOAD_None, NULL);
	if (selectedMesh != nullptr)
	{
		GetMesh()->SetSkeletalMesh(selectedMesh);
		if (playerMeshNumber == 1)
		{
			GetMesh()->SetRelativeScale3D(FVector(3.0f));
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
		if (playerMeshNumber == 1)
		{
			GetMesh()->SetMaterial(0, selectedDynamicMat);
			
			FString rapmatPath1 = TEXT("/Script/Engine.Material'/Game/4_SK/Raptor/Model/DromaMESH_Material__26.DromaMESH_Material__26'");

			UMaterial* RapselectedMat = LoadObject<UMaterial>(NULL, *rapmatPath1, NULL, LOAD_None, NULL);

			UMaterialInstanceDynamic* RapselectedDynamicMat = UMaterialInstanceDynamic::Create(RapselectedMat, this);

			GetMesh()->SetMaterial(1, RapselectedDynamicMat);


		}
		else
		{
			GetMesh()->SetMaterial(0, selectedDynamicMat);

		}

	}
}

void ABasePlayer::Horizontal(float ValX)
{
	pc = Cast<APlayerController>(GetController());

	if (pc != nullptr)
	{ 
	FRotator CurrControlRotation = pc->GetControlRotation();
	
	this->AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f, CurrControlRotation.Yaw, 0.0f)), ValX);
	}
}

void ABasePlayer::Vertical(float ValY)
{
	pc = Cast<APlayerController>(GetController());
	if (pc != nullptr){
	FRotator CurrControlRotation = pc->GetControlRotation();

	this->AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f, CurrControlRotation.Yaw, CurrControlRotation.Roll)), ValY);
	}
}

void ABasePlayer::Look_Horizontal(float Val)
{


 	this->AddControllerYawInput(Val*0.5);

	
}

void ABasePlayer::Look_Vertical(float Val)
{
	this->AddControllerPitchInput(Val);
}

void ABasePlayer::InitialCustomMulti_Implementation()
{
	ServerSetCustomItemInfo(gi->playerCustomItemInfo);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Initialize"));
}

void ABasePlayer::ServerSetInitInfo_Implementation(FPlayerCustomInfo initInfo)
{

	playerName = initInfo.dinoName;
	playerMeshNumber = initInfo.dinoMeshNum;
	playerColor = initInfo.dinoColor;


}

void ABasePlayer::ServerSetCustomItemInfo_Implementation(FPlayerCustomItemInfo customItemInfo)
{
	playerHat = customItemInfo.HatTagInstance;
	playerGlasses = customItemInfo.GlassesTagInstance;
	playerShoes = customItemInfo.ShoesTagInstance;
}

