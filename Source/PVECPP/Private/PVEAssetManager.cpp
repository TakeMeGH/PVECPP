// Fill out your copyright notice in the Description page of Project Settings.


#include "PVEAssetManager.h"
#include "AbilitySystemGlobals.h"

void UPVEAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("HALO DUNIA"));
}