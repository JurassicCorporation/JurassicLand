// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JE_PlayerState.generated.h"

/**
 * 
 */
 USTRUCT(BlueprintType)
struct FPCustomInfo
{
	GENERATED_USTRUCT_BODY()

// �÷��̾� ���� : �г���, �޽�, �÷�
public:
	// �г��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString pName = TEXT("GameInstance");

	// �� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor pColor = FLinearColor::White;

	// �޽� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 pMeshNum = 0;

};

USTRUCT(BlueprintType)
struct FPCustomItemInfo
{
	GENERATED_USTRUCT_BODY()

// �÷��̾� ���� : ����, �Ȱ�, �Ź�
public:
	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName pHatName = FName(TEXT("nothing"));

	// �Ȱ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName pGlassesName = FName(TEXT("nothing"));

	// �Ź� ����  
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName pShoesName = FName(TEXT("nothing"));
};

UCLASS()
class JURASSICLAND_API AJE_PlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	class ULSH_NetGameInstance* gi;
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = Player)
	FPCustomInfo pCustomInfo;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = Player)
	FPCustomItemInfo pCustomItemInfo;

public:
	UFUNCTION(Server, Reliable)
	void SetdinoName(const FString& myName);

	UFUNCTION(Server, Reliable)
	void InitialInfo();

	UFUNCTION(Server, Reliable)
	void SetInstanceCustomInfo();

	UFUNCTION(Server, Reliable)
	void SetInstanceCustomItemInfo();
	
};
