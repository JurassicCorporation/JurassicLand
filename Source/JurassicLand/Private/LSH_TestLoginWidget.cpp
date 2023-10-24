// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_TestLoginWidget.h"
#include "Components/EditableText.h"
#include "LSH_NetGameInstance.h"

void ULSH_TestLoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
	gi = GetGameInstance<ULSH_NetGameInstance>();

	FTimerHandle createHandler;
	GetWorld()->GetTimerManager().SetTimer(createHandler, this, &ULSH_TestLoginWidget::FindSession, 0.1, false);

	FTimerHandle GravityTimerHandle;
	float GravityTime = 10;

	GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// �ڵ� ����

			if (gi->sessionNum >= 99||gi->sessionNum<=0)
			{
				//FTimerHandle createHandler2;

				//GetWorld()->GetTimerManager().SetTimer(createHandler2, this, &ULSH_TestLoginWidget::CreateSession, 3, false);//1�� �ڿ� ����ǰ�
				CreateSession();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("join session"));
				gi->JoinOtherSession();
			}
			// TimerHandle �ʱ�ȭ
			GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);
		}), GravityTime, false);	// �ݺ��Ϸ��� false�� true�� ����




}

void ULSH_TestLoginWidget::CreateSession()
{
	gi->CreateMySession(edit_MyName->GetText());
}

void ULSH_TestLoginWidget::FindSession()
{
	UE_LOG(LogTemp, Warning, TEXT("FindSession"));
	if (gi != nullptr)
	{
		gi->FindOtherSession();
	}
}
