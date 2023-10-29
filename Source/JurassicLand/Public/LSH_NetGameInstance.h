// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LSH_NetGameInstance.generated.h"

/**
 * 
 */
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

	void CreateMySession(FText userName);//���Ǹ�����Լ�
	void OncreatedMySession(FName sessionName, bool bWasSuccessful);//������ ��������� ���� ����� ��������Ʈ �Լ�
	void FindOtherSession();//�ٸ�����̸����������ǰ˻��Լ�
	void OnFindOtherSessions(bool bWasSyccessful);//���� ã���� ���ε� �Լ�
	void JoinOtherSession();
	void OnJoinSelectedSession(FName sessionName, EOnJoinSessionCompleteResult::Type result);
	void OnTravlebattleMap();//���� ���۹�ư ������ �� ����Ʈ����

public:
	UPROPERTY()
	bool isEnd = false;
};
