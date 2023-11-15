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

// 플레이어 정보 : 닉네임, 메쉬, 컬러
public:
	// 닉네임 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString pName = TEXT("GameInstance");

	// 색 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor pColor = FLinearColor::White;

	// 메쉬 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 pMeshNum = 0;

};

USTRUCT(BlueprintType)
struct FPCustomItemInfo
{
	GENERATED_USTRUCT_BODY()

// 플레이어 정보 : 모자, 안경, 신발
public:
	// 모자 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName pHatName = FName(TEXT("nothing"));

	// 안경 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName pGlassesName = FName(TEXT("nothing"));

	// 신발 변수  
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
