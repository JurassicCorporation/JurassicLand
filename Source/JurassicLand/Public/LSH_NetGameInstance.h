// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LSH_NetGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerCustomInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	FString dinoName = TEXT("GameInstance");
	UPROPERTY()
	int32 dinoMeshNum = 0;
	UPROPERTY()
	FLinearColor dinoColor = FLinearColor::White;

	FORCEINLINE void Set(FString name, int32 num, FLinearColor color)
	{
		dinoName = name;
		dinoMeshNum = num;
		dinoColor = color;
		
	}

};

USTRUCT(BlueprintType)
struct FPlayerCustomItemInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CustomData")
	FName HatTagInstance = FName(TEXT("nothing"));
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CustomData")
	FName GlassesTagInstance = FName(TEXT("nothing"));
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CustomData")
	FName ShoesTagInstance = FName(TEXT("nothing"));
};

USTRUCT(BlueprintType)
struct FPlayerSkillInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	int32 BuffskillNum = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	int32 SpecialskillNum = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	class UTexture2D* playerSpecialSkillImg = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	class UTexture2D* playerBuffSkillImg = nullptr;
};


UCLASS()
class JURASSICLAND_API ULSH_NetGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	ULSH_NetGameInstance();

	virtual void Init() override;

	UPROPERTY()
	FString myName;
	int32 sessionNum = 99;

	IOnlineSessionPtr sessionInterface;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;

public:
	// 지은
	FPlayerCustomInfo playerCustomInfo;
	UPROPERTY(BlueprintReadOnly)
	FPlayerCustomItemInfo playerCustomItemInfo;
	UPROPERTY(BlueprintReadOnly)
	FPlayerSkillInfo playerSkillInfo;
	bool IsColorChanged = false;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CustomData")
	FName HatTagInstance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CustomData")
	FName GlassesTagInstance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CustomData")
	FName ShoesTagInstance;*/


	void CreateMySession(FText userName);//세션만들기함수
	void OncreatedMySession(FName sessionName, bool bWasSuccessful);//세션이 만들어지고 난후 실행될 델리케이트 함수
	void FindOtherSession();//다른사람이만들어놓은세션검색함수
	void OnFindOtherSessions(bool bWasSyccessful);//세션 찾으면 바인딩 함수
	void JoinOtherSession();
	void OnJoinSelectedSession(FName sessionName, EOnJoinSessionCompleteResult::Type result);
	void OnTravlebattleMap();//게임 시작버튼 눌렀을 때 서버트래블

public:
	UPROPERTY()
	bool isEnd = false;
};
