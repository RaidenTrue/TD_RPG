// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Aura/RpgLogChannels.h"

FRpgAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FRpgAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogRpg, Error, TEXT("Can't find Info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FRpgAbilityInfo();
}
