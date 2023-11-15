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
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")//HP동기화
	float TRexHP = 50;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;//변수 동기화 위한 함수

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

/*---------------------------- 지은 ----------------------------*/
public:
	// hp - 지은
	//HP동기화
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsHpZero = false;	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	//bool bIsHPShow = false;

	bool btickStop = false;

// 플레이어 정보 : 닉네임, 메쉬, 컬러
public:

	class ULSH_NetGameInstance* gi;

	UPROPERTY()	
	class AJE_PlayerState* ps;
	
	// 닉네임 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FString playerName = "BlueTrex";

	// 색 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FLinearColor playerColor = FLinearColor::White;

	// 메쉬 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	int32 playerMeshNumber = 0;

// 플레이어 정보 : 모자, 안경, 신발
public:
	// 모자 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerHat;

	// 안경 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerGlasses;

	// 신발 변수  
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerShoes;

public:
	// 닉네임 ui component
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UJE_NicknameComponent* nickComp;*/

	// 닉네임 textrendercomponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Nickname")
	class UTextRenderComponent* nicknameText;

//코인
public:
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float initialCoin = 500.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float currentCoin = 0.0f;

//컬러 커스텀
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
	
	// 클라이언트가 서버에 playerstate 요청하는 코드
	UFUNCTION(Server, Reliable)
	void ServerGetplayerState();
	
	//커스텀 아이템, 커스텀 컬러 및 플레이어 정보 실행 함수
	UFUNCTION()
	void InitializePlayer();

	// 커스텀 컬러 플레이어 정보 설정 함수(멀티캐스트)
	UFUNCTION(BlueprintCallable)
	void SetColor();

	// 커스텀 컬러 초기 설정
	UFUNCTION()
	void CustomColor();

	// 커스텀 아이템 설정 함수, 블루프린트에 정의
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitialCustomMulti();

	// 플레이어 정보 설정 함수
	UFUNCTION(Server, Reliable)
	void ServerSetInitInfo();

	// 플레이어 커스텀 아이템 설정 함수
	UFUNCTION(Server, Reliable)
	void ServerSetCustomItemInfo();

// 저장
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class UJE_SaveGame* MySaveGame;

	// 커스텀 아이템 데이터 테이블 정보
	FJE_CustomItemData* playerCustomData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomData")
	UDataTable* PlayerCustomTable;

	// 커스텀 아이템 저장 변수들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentHat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentGlasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentShoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class UMaterialInstanceDynamic* currentDynamicMat;

	// 커스텀 액터의 태그 저장 변수
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

// 메쉬 커스텀
public:

	// 메쉬 경로 저장한 배열
	TArray<FString> meshPathList = { TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlueTRex/SK_TRex.SK_TRex'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/RaptorDinosaur/Model/Raptor_Cutscenes.Raptor_Cutscenes'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Dinosaurus_Stegosaurus/Models/SK_Stegosaurus.SK_Stegosaurus'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"), };
	
	// 메쉬에 맞는 material
	TArray<FString> matPathList = { TEXT("/Script/Engine.Material'/Game/4_SK/BlueTRex/MAT_TRex.MAT_TRex'"),
									TEXT("/Script/Engine.Material'/Game/4_SK/RaptorDinosaur/Model/DromaMESH_DromaBodyM.DromaMESH_DromaBodyM'"),
									TEXT("/Script/Engine.Material'/Game/4_SK/Dinosaurus_Stegosaurus/Models/Materials/M_Stegosaurus_Green.M_Stegosaurus_Green'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"), };

	// 메쉬에 맞는 애니메이션
	TArray<FString> animPathList = { TEXT("/Script/Engine.AnimBlueprint'/Game/4_SK/BlueTRex/BluePrints/ABP_BlueTRex.ABP_BlueTRex'"),
									TEXT("/Script/Engine.AnimSequence'/Game/4_SK/RaptorDinosaur/Animations/RootMotion/Idle.Idle'"),
									TEXT("/Script/Engine.AnimSequence'/Game/4_SK/Dinosaurus_Stegosaurus/Animations/RootMotion/Stegosaurus_RM_Idle.Stegosaurus_RM_Idle'"),
									TEXT("/Script/Engine.AnimSequence'/Game/4_SK/Triceratops/Animations/Triceratops_Idle_Roar.Triceratops_Idle_Roar'")};
	class UAnimBlueprint* trexAnimClass;

	// 메쉬 변경 함수
	UFUNCTION()
	void SetMesh();

	// 메쉬 초기 설정
	UFUNCTION()
	void CustomMesh();

// 스킬 프리셋
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

	// 스킬 사용하는 키에 따른 쿨타임 인덱스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 coolTimeIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<class UJE_BattleWidget> battlewidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
 	class UJE_BattleWidget* battleUI;

	

public:
	UFUNCTION()
	void SaveSkills();
	
	// 스킬 프리셋 설정 함수
	UFUNCTION(Server, Reliable)
	void ServerSetSkills(FPlayerSkillInfo skillInfo);

	// 스킬 쿨타임 가져오는 함수
	UFUNCTION(BlueprintCallable)
	void getSkillCool();
};
 