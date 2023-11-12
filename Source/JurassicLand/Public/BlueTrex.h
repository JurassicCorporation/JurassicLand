// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "JE_CustomItemData.h"
#include "BlueTrex.generated.h"

UCLASS()
class JURASSICLAND_API ABlueTrex : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlueTrex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*-----Enhanced Input Value-----*/
	
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* IMC_TRex;
	UPROPERTY(EditAnywhere, Category = Input)
	TArray<class UInputAction*> inputActions;


	/*------ Enhanced Input Function -----*/
	void SetupPlayerEnhancedInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> InputActions);

	void TRexMove(const FInputActionValue& Val);
	void TRexLook(const FInputActionValue& Val);
	UFUNCTION(BlueprintNativeEvent)
	//UFUNCTION()
	void TRexTailAttack(const FInputActionValue& Val);
	//UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	//tailATK

	/*----- Character Component-----*/
public:
	UPROPERTY(EditAnywhere, Category= CharacterSettings, BlueprintReadWrite)
	class USkeletalMeshComponent* TRexBody;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= CharacterSettings)
	class UCameraComponent* TRexEye;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= CharacterSettings)
	class USpringArmComponent* TRexEyeArm;

	/*----- Damage System Value --------*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")//HP����ȭ
	float TRexHP = 50;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;//���� ����ȭ ���� �Լ�

	float TRexPower = 12;

	/*----- General Value ----------*/
public:
	class APlayerController* pc;
	class UCharacterMovementComponent* CharacterMovement;

	/*-------- Animation Value --------*/

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
 	bool TailAttack = false;

private:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
    class UAnimationAsset* TailAttackAnim;


public:
	// hp - ����
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")//HP����ȭ
	bool bIsHpZero = false;	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	//bool bIsHPShow = false;

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

	// Ŀ���� ������ ���� �Լ�, �������Ʈ�� ����
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
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/RaptorDinosaur/Model/Raptor_Cutscenes.Raptor_Cutscenes'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Dinosaurus_Stegosaurus/Models/SK_Stegosaurus.SK_Stegosaurus'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"), };
	
	// �޽��� �´� material
	TArray<FString> matPathList = { TEXT("/Script/Engine.Material'/Game/4_SK/BlueTRex/MAT_TRex.MAT_TRex'"),
									TEXT("/Script/Engine.Material'/Game/4_SK/RaptorDinosaur/Model/DromaMESH_DromaBodyM.DromaMESH_DromaBodyM'"),
									TEXT("/Script/Engine.Material'/Game/4_SK/Dinosaurus_Stegosaurus/Models/Materials/M_Stegosaurus_Green.M_Stegosaurus_Green'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"), };

	// �޽��� �´� �ִϸ��̼�
	TArray<FString> animPathList = { TEXT("/Script/Engine.AnimBlueprint'/Game/4_SK/BlueTRex/BluePrints/ABP_BlueTRex.ABP_BlueTRex'"),
									TEXT("/Script/Engine.AnimSequence'/Game/4_SK/RaptorDinosaur/Animations/RootMotion/Idle.Idle'"),
									TEXT("/Script/Engine.AnimSequence'/Game/4_SK/Dinosaurus_Stegosaurus/Animations/RootMotion/Stegosaurus_RM_Idle.Stegosaurus_RM_Idle'"),
									TEXT("/Script/Engine.AnimSequence'/Game/4_SK/Triceratops/Animations/Triceratops_Idle_Roar.Triceratops_Idle_Roar'")};
	class UAnimBlueprint* trexAnimClass;

	// �޽� ���� �Լ�
	UFUNCTION()
	void SetMesh();

	// �޽� �ʱ� ����
	UFUNCTION()
	void CustomMesh();

// ��ų ������
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

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float buffCool = 5.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float SpecialCool = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	bool BCoolTime = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	bool SCoolTime = false;

	// ��ų ����ϴ� Ű�� ���� ��Ÿ�� �ε���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 coolTimeIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<class UJE_BattleWidget> battlewidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
 	class UJE_BattleWidget* battleUI;

	

public:
	UFUNCTION()
	void SaveSkills();
	
	// ��ų ������ ���� �Լ�
	UFUNCTION(Server, Reliable)
	void ServerSetSkills(FPlayerSkillInfo skillInfo);

	// ��ų ��Ÿ�� �������� �Լ�
	UFUNCTION(BlueprintCallable)
	void getSkillCool();
};
 