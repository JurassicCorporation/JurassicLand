// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_TypeListViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_TypeListViewWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	class ULSH_NetGameInstance* gi;

	class ABlueTrex* player;
	class ARaptor* raptorplayer;
	class ABasePlayer* baseplayer;

	class AJE_SkillModeBase* skillmode;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_type;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_type_1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_type_2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_type_3;

public:
	// 캐릭터 스폰 위치 액터
	class AJE_CharacterSpawActor* spawnLocActor;


public:
	UFUNCTION()
	void OnClickedType();

	UFUNCTION()
	void OnClickedType2();

	UFUNCTION()
	void OnClickedType3();

	UFUNCTION()
	void OnClickedType4();
};
