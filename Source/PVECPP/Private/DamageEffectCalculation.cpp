// Fill out your copyright notice in the Description page of Project Settings.
#include "DamageEffectCalculation.h"
#include "PlayerAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"

// Declare the attributes to capture and define how we want to capture them from the Source and Target.
struct GDDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LowBaseAttackDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(HighBaseAttackDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackModifier);


	GDDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, LowBaseAttackDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, HighBaseAttackDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, AttackModifier, Source, false);


		// Capture the Target's Armor. Don't snapshot.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Health, Target, true);
	}
};

static const GDDamageStatics& DamageStatics()
{
	static GDDamageStatics DStatics;
	return DStatics;
}

UDamageEffectCalculation::UDamageEffectCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().AttackModifierDef);
	RelevantAttributesToCapture.Add(DamageStatics().LowBaseAttackDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().HighBaseAttackDamageDef);
}


void UDamageEffectCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Health = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, Health);

	float LowBaseAttackDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LowBaseAttackDamageDef, EvaluationParameters, LowBaseAttackDamage);

	float HighBaseAttackDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HighBaseAttackDamageDef, EvaluationParameters, HighBaseAttackDamage);

	float AttackModifier = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackModifierDef, EvaluationParameters, AttackModifier);

	float RandomRangeFloat = FMath::FRandRange(LowBaseAttackDamage, HighBaseAttackDamage);
	float Result = RandomRangeFloat * AttackModifier;
	Result = FMath::TruncToInt(Result);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthDef.AttributeToCapture, EGameplayModOp::Additive, -Result));

}
