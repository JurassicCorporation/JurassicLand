// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_CustomWholeWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_CustomWholeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	class ULSH_NetGameInstance* gi;
	class ABlueTrex* player;
	class AJE_PlayerState* ps;


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_load;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_save;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_backtomain;

public:
	UFUNCTION()
	void OnClickedLoad();

	UFUNCTION()
	void OnClickedSave();

	UFUNCTION()
	void OnClickedBacktomain();
};
