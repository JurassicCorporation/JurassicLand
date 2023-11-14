// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "JE_CustomItemData.h"
#include "BasePlayer.generated.h"

UCLASS()
class JURASSICLAND_API ABasePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


/*--------- Character Component -----------*/
public:
	//SkeletalMesh
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class USkeletalMeshComponent* PlayerBody;
	
	//Spring Arm
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class USpringArmComponent* PlayerCamArm;

	//Camera
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UCameraComponent* PlayerCam;

	//Collision_ Head
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UCapsuleComponent* PlayerHeadCollision;
	
	//Collision_ UpperBody
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UCapsuleComponent* PlayerUpperBodyCollision;
	
	//Collision_ Tail
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UCapsuleComponent* PlayerTailCollision;

	//HP Bar Widget
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UWidgetComponent* HP_Bar;


	/********** Player Common Value *************/
public:
	/*State - HP, Speed, Power, Defence*/
	

	
	//State_HP(Damage System Value)
	//HP����ȭ
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float State_HP = 50; 
	
	//HP ���� ����ȭ ���� �Լ�
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	//noDamageTime(���� �°����� ���ʰ� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	bool noDamageTime = false;

	//State_Speed
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float SpeedStat = 4.0f;

	//State_Power
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float PowerStat = 6.0f;

	//State_Defence
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float DefenceStat = 5.0f;

	//State_Temp : Player State Before Buff
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float TempStat = 0.0f;


	/*--------------- Value about Skill ------------*/
	//Special Skill Selection
	UPROPERTY(EditAnywhere, Category = Player_SkillSelection, BlueprintReadWrite)
	int SpecialSkill = 0;
	
	//Buff Skill Selection
	UPROPERTY(EditAnywhere, Category = Player_SkillSelection, BlueprintReadWrite)
	int BuffSkill = 0;

	/*----------- Skill Control Value ------------*/
	//ICE Attack Forward Vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillControl, BlueprintReadWrite)
	FVector IceAttackFwdVector;
	
	//ICE Attack Location Vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillControl, BlueprintReadWrite)
	FVector IceAttackLocVector;

	//Special Skill Cool Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", BlueprintReadWrite)
	bool SCoolTime = false;
	
	//Buff Skill Cool Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", BlueprintReadWrite)
	bool BCoolTime = false;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float buffCool = 5.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float SpecialCool = 5.0f;

	// ��ų ����ϴ� Ű�� ���� ��Ÿ�� �ε���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 coolTimeIndex = -1;

// 	Basic Skill Cool Time
// 		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillControl, BlueprintReadWrite)
// 		bool CoolTime_BasicSkill = false;


/*--------- Animation Control value ----------*/
	
	//Turn Left
	UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bTurnLeft = false;
	 
	 //Turn Right
	 UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bTurnRight = false;
	 
	 //Laser Beam
	 UPROPERTY(Replicated,EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bLaserBeam = false;

	 //TailAttack
	  UPROPERTY(Replicated,EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bTailAttack= false;
	 UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bIsNoHit = true;
	 
	 //Roar
	  UPROPERTY(Replicated,EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bRoar= false;
	 
	 //Bite
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bBite = false;
	 
	 //ICE Stalagmite
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bICEStalagmite = false;

	 //Breath Flame
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bFlameOnOff = false;

/*---------- Customize System Value -------------*/
	  //GlassesActorClass
	  UPROPERTY(EditAnywhere, Category = CustomizeSys, BlueprintReadWrite)
	  TSubclassOf<class AActor> GlassesActorClass;
	  
	  //HatActorClass
	   UPROPERTY(EditAnywhere, Category = CustomizeSys, BlueprintReadWrite)
	  TSubclassOf<class AActor> HatActorClass;

	  //RShoesActorClass
	  UPROPERTY(EditAnywhere, Category = CustomizeSys, BlueprintReadWrite)
	  TSubclassOf<class AActor> RShoesActorClass;
	  
	  //LShoesActorClass
	  UPROPERTY(EditAnywhere, Category = CustomizeSys, BlueprintReadWrite)
	  TSubclassOf<class AActor> LShoesActorClass;

	  /*----- General Value ----------*/
public:
	class APlayerController* pc;
	class ALSH_NetPlayerController* lsh_pc;
	class UCharacterMovementComponent* CharacterMovement;

	  /*---------- Enhanced Input ---------------*/
	  //Enhanced Input Component
	  UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Input)
	  class UMoveComp* MoveComp; 

	  //Context
	  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input)
	  class UInputMappingContext* IMC_Player;

	  //InputActions
	  UPROPERTY(EditAnywhere,Category=Input)
	  TArray<class UInputAction*> inputActions;

 	  public:
 	// hp - ����
 	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "StateWidget")//HP����ȭ
 	bool bIsHpZero = false;	
 
 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateWidget")
 	bool bIsHPShow = false;
 
 	bool btickStop = false;

	/*---------------------------- ���� ----------------------------*/
// �÷��̾� ���� : �г���, �޽�, �÷�
public:

	class ULSH_NetGameInstance* gi;
	
	// �г��� ����
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FString playerName = "BlueTrex";

	// �� ����
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FLinearColor playerColor = FLinearColor::White;

	// �޽� ����
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	int32 playerMeshNumber = 0;

// �÷��̾� ���� : ����, �Ȱ�, �Ź�
public:
	// ���� ����
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerHat;

	// �Ȱ� ����
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerGlasses;

	// �Ź� ����  
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerShoes;

	public:
	// �г��� ui component
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UJE_NicknameComponent* nickComp;*/

// �г��� textrendercomponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Nickname")
	class UTextRenderComponent* nicknameText;

//����
public:
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float initialCoin = 500.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float currentCoin = 0.0f;

//�÷� Ŀ����
public:
	class UMaterialInterface* CustomMat;
	class UMaterialInterface* InitialMat;
	class UMaterialInterface* currMat;
	class UMaterialInstanceDynamic* dynamicMat1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
	bool IsColor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
	bool IsColorCustom = false;

public:
	//Ŀ���� ������, Ŀ���� �÷� �� �÷��̾� ���� ���� �Լ�
	UFUNCTION()
	void InitializePlayer();

	// Ŀ���� �÷� �÷��̾� ���� ���� �Լ�(��Ƽĳ��Ʈ)
	UFUNCTION(BlueprintCallable)
	void SetColor();

	// Ŀ���� �÷� �ʱ� ����
	UFUNCTION()
	void CustomColor();

	// Ŀ���� ������ ���� �Լ�, ��������Ʈ�� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitialCustomMulti();

	// �÷��̾� ���� ���� �Լ�
	UFUNCTION(Server, Reliable)
	void ServerSetInitInfo(FPlayerCustomInfo initInfo);

	// �÷��̾� Ŀ���� ������ ���� �Լ�
	UFUNCTION(Server, Reliable)
	void ServerSetCustomItemInfo(FPlayerCustomItemInfo customItemInfo);

	// ����
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class UJE_SaveGame* MySaveGame;

	// Ŀ���� ������ ������ ���̺� ����
	FJE_CustomItemData* playerCustomData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomData")
	UDataTable* PlayerCustomTable;

	// Ŀ���� ������ ���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentHat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentGlasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentShoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class UMaterialInstanceDynamic* currentDynamicMat;

	// Ŀ���� ������ �±� ���� ����
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName HatTag;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName GlassesTag;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName ShoesTag;

	public:
	UFUNCTION()
	void GetCustomItemData();

	UFUNCTION()
	void SaveCustomItemData();

	UFUNCTION()
	void LoadCustomItemData();

// �޽� Ŀ����
public:

	// �޽� ��� ������ �迭
	TArray<FString> meshPathList = { TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlueTRex/SK_TRex.SK_TRex'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Raptor/Model/Raptor_HumanIK.Raptor_HumanIK'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Dinosaurus_Stegosaurus/Models/SK_Stegosaurus.SK_Stegosaurus'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"), };
	
	// �޽��� �´� material
	TArray<FString> matPathList = { TEXT("/Script/Engine.Material'/Game/4_SK/BlueTRex/MAT_TRex.MAT_TRex'"),
									TEXT("/Script/Engine.Material'/Game/4_SK/Raptor/Model/DromaMESH_DromaBodyM.DromaMESH_DromaBodyM'"),
									TEXT("/Script/Engine.Material'/Game/4_SK/Dinosaurus_Stegosaurus/Models/Materials/M_Stegosaurus_Green.M_Stegosaurus_Green'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"), };


	// �޽� ���� �Լ�
	UFUNCTION()
	void SetMesh();

	// �޽� �ʱ� ����
	UFUNCTION()
	void CustomMesh();
	/*------- LockOnSystem -----------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LockOnSystem)
	class AActor* LockOnTarget;

public:
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	bool IsSetPreset = false;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 currBuffskillNum;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 currSpecialskillNum;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	class UTexture2D* currplayerSpecialSkillImg;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	class UTexture2D* currplayerBuffSkillImg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<class UJE_BattleWidget> battlewidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
 	class UJE_BattleWidget* battleUI;
};
