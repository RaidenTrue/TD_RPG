#pragma once

#include "GameplayEffectTypes.h"
#include "RpgAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FRpgGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	/* Returns the Actual Struct, used for Serialization, SubClasses must Override this. */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/* Custom Serialization, SubClasses must Override this. */
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);

	bool IsCriticalHit() const { return bIsCriticalHit; }

	bool IsBlockedHit() const { return bIsBlockedHit; }

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }

protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

};
