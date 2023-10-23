// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_NetGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

ULSH_NetGameInstance::ULSH_NetGameInstance()
{
	mySessionName = TEXT("netTester1");
}

void ULSH_NetGameInstance::Init()
{
	Super::Init();

	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		//Online Session Interface API ���ٿ� �ν��Ͻ� ��������
		sessionInterface = subsys->GetSessionInterface();

		//���� �̺�Ʈ�� �Լ� ���ε��ϱ�
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ULSH_NetGameInstance::OncreatedMySession);
		FTimerHandle createHandler;
		GetWorld()->GetTimerManager().SetTimer(createHandler, this, &ULSH_NetGameInstance::CreateMySession, 0.1, false);//1�� �ڿ� ����ǰ�
	}
}

void ULSH_NetGameInstance::CreateMySession()
{	
	FOnlineSessionSettings sessionSettings;//���Ǽ��� ����, ����ü
	//1. lan�������� dedicated�������� ����
	sessionSettings.bIsDedicated = false;//�������� ����
	sessionSettings.bIsLANMatch = true;//����İ� ��������� ���� > ������ ����
	//2. �˻������� ������ �����ϱ�
	sessionSettings.bShouldAdvertise = true;

	//3. �ڱ� ������ ���޵� �� �ְ� �����ϱ�
	sessionSettings.bUsesPresence = true;

	//4. �ٸ������� �߰� ���� ����ϱ�
	sessionSettings.bAllowJoinInProgress = true;
	sessionSettings.bAllowJoinViaPresence = true;//���� ���� ������ �ƴ� ģ�� ���� ���� ��

	//5. ���� ���� �ο��� �����Ѵ�
	sessionSettings.NumPublicConnections = 10;


	bool isSuccess = sessionInterface->CreateSession(0, FName("TestRoom"), sessionSettings);//���̸�, �漼��
	UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Failed"));


}

void ULSH_NetGameInstance::OncreatedMySession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		FString mapAdress = "/Game/LSH_WorkSpace/LSH_BattleMap";//�̵��� �� �ּ�
		bool travelResult = GetWorld()->ServerTravel(mapAdress+"?Listen", true);//�ּ�+���� ���� ��ü ���������ν� �̵�, �ɸ��� Ȥ�� �ۼַ�Ʈ ó���� ������ �ۼַ�Ʈ//����Ʈ������ ȣ��Ʈ�� ��� �����ϴ� > ������ �ְ� Ʈ������ �ϸ� �ڽ����� �پ� �ִ� ��� Ŭ���̾�Ʈ���� ��� ������ ���̵��Ѵ�. Ŭ���̾�ƮƮ������ �ڱ⸸ �̵��Ѵ�. ȣ��Ʈ�� �и� �� ������ �������� ������ �� ���. ����Ʈ������ �����忡 ����, Ŭ���̾�ƮƮ������ �÷��̾���Ʈ�ѷ��� ������
		UE_LOG(LogTemp, Warning, TEXT("travel Result : %s"), travelResult ? *FString("Success") : *FString("Failed"));

	}
}
