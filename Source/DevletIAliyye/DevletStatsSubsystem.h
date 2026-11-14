// DEVLET-İ ALİYYE — üç katmanın ortak istatistik deposu.
// TPS diyalog seçimi, AoE görevi veya HoI4 kararı aynı ApplyEffects çağrısını kullanır;
// böylece "sokakta alınan karar" harita ve şehir katmanına aynı anda yansır.
// NOT: Bu oturumda derlenmedi.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DevletDataTypes.h"
#include "DevletStatsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDAOnStatChanged, FName, Stat, float, OldValue, float, NewValue);

UCLASS()
class UDevletStatsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** HoI4 arayüzü, AoE üretim sistemi ve TPS HUD bu olaya abone olur. */
	UPROPERTY(BlueprintAssignable) FDAOnStatChanged OnStatChanged;

	UFUNCTION(BlueprintPure, Category = "Devlet|Stats")
	float GetStat(FName Stat) const
	{
		const float* Found = Stats.Find(Stat);
		return Found ? *Found : 0.f;
	}

	UFUNCTION(BlueprintCallable, Category = "Devlet|Stats")
	void ApplyEffects(const TArray<FDAEffect>& Effects)
	{
		for (const FDAEffect& Effect : Effects)
		{
			const float Old = GetStat(Effect.Stat);
			float New = Old + Effect.Value;
			if (IsPercentStat(Effect.Stat))
			{
				New = FMath::Clamp(New, 0.f, 100.f);
			}
			Stats.Add(Effect.Stat, New);
			OnStatChanged.Broadcast(Effect.Stat, Old, New);
		}
	}

	/** TPS diyalog penceresinden çağrılır. Unlocks alanını çağıran taraf görev sistemine iletir. */
	UFUNCTION(BlueprintCallable, Category = "Devlet|Dialogue")
	void ApplyDialogueChoice(const FDADialogueChoice& Choice)
	{
		ApplyEffects(Choice.Effects);
	}

	/** Karakterin verilen oyun yılında sahnede görünüp görünmeyeceği (anakronizm kilidi). */
	UFUNCTION(BlueprintPure, Category = "Devlet|Dialogue")
	static bool IsCharacterActive(const FDATPSCharacterRow& Row, int32 Year)
	{
		return Year >= Row.ActiveFrom && Year <= Row.ActiveTo;
	}

private:
	static bool IsPercentStat(FName Stat)
	{
		static const TSet<FName> Percent = {
			"Stability", "WarSupport", "FactoryEfficiency", "Organization", "Morale", "Supply",
			"NavalReadiness", "ForeignPressure", "ForeignDependence", "DiscoveryRisk",
			"SabotageRisk", "CivilianCasualtyRisk", "BreakoutChance", "ConflictChance", "Encirclement"
		};
		return Percent.Contains(Stat);
	}

	UPROPERTY() TMap<FName, float> Stats;
};
