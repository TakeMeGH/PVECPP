// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PVECPP_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "MaxHealth", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "LowBaseAttackDamage", ReplicatedUsing = OnRep_LowBaseAttackDamage)
	FGameplayAttributeData LowBaseAttackDamage;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, LowBaseAttackDamage)

	UPROPERTY(BlueprintReadOnly, Category = "HighBaseAttackDamage", ReplicatedUsing = OnRep_HighBaseAttackDamage)
	FGameplayAttributeData HighBaseAttackDamage;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, HighBaseAttackDamage)

	UPROPERTY(BlueprintReadOnly, Category = "AttackSpeed", ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, AttackSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "Defense", ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Defense)

	UPROPERTY(BlueprintReadOnly, Category = "AttackModifier", ReplicatedUsing = OnRep_AttackModifier)
	FGameplayAttributeData AttackModifier;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, AttackModifier)
	
	UPROPERTY(BlueprintReadOnly, Category = "MovementSpeed", ReplicatedUsing = OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MovementSpeed)


	UPROPERTY(BlueprintReadOnly, Category = "OutputDamage")
	FGameplayAttributeData OutputDamage;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, OutputDamage)

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_LowBaseAttackDamage(const FGameplayAttributeData& OldLowBaseAttackDamage);
	UFUNCTION()
	virtual void OnRep_HighBaseAttackDamage(const FGameplayAttributeData& OldHighBaseAttackDamage);
	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);
	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);
	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
	UFUNCTION()
	virtual void OnRep_AttackModifier(const FGameplayAttributeData& OldAttackModifier);






};
