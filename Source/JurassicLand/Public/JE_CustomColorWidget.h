// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_CustomColorWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_CustomColorWidget : public UUserWidget
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
	class UButton* btn_red;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_yellow;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_blue;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_green;

	FLinearColor currentColor = FLinearColor::White;

public:
	UFUNCTION()
	void OnRedClicked();

	UFUNCTION()
	void OnYellowClicked();

	UFUNCTION()
	void OnBlueClicked();

	UFUNCTION()
	void OnGreenClicked();
	
};
