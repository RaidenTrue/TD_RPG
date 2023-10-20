// Copyright by Savvas JRD - LTD Cyprus


#include "Input/RpgInputConfig.h"

const UInputAction* URpgInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FRpgInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputCOnfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
