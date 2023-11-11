// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_BattleWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_BattleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class ULSH_NetGameInstance* gi;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	class ABlueTrex* player;
	class AJE_BattleInController* pc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = MySettings)
	class UWidgetSwitcher* ws_Battle;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_skill_foot;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_toMain;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_battleloading;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_battleStart;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_skill_roar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_skill_tail;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_skill_foot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_battleresult;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_toMain;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UImage* img_specialskill;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UImage* img_buffskill;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UProgressBar* pb_coolTime1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UProgressBar* pb_coolTime2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UProgressBar* pb_coolTime3;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UProgressBar* pb_coolTimeq;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UProgressBar* pb_coolTimee;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UImage* img_player_win;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UImage* img_player_lose;

	UPROPERTY(VisibleAnywhere, Transient, meta = (BindWidgetAnim), Category = MySettings)
	class UWidgetAnimation* startText;

	FTimerHandle initHandler;
	FTimerHandle CoinHandler;
	
	UPROPERTY(BlueprintReadOnly)
	bool ischange = false;

	UPROPERTY(BlueprintReadOnly)
	bool bisMouse = false;

	UPROPERTY()
	float bcoolTime = 0.f;

	UPROPERTY()
	float scoolTime = 0.f;

public:	
	UFUNCTION()
	void LoadingUI();

	UFUNCTION()
	void StartUIAnim();

	UFUNCTION()
	void CoinUI();

	UFUNCTION() 
	void OnClickedToMain();

	// ��ų ��Ÿ�� �Լ�
	UFUNCTION(BlueprintCallable)
	void SetSkillCool();

	
};
