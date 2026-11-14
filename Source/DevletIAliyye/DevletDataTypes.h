// DEVLET-İ ALİYYE — veri tablosu satır tipleri.
// data/campaign_chapters.json  -> DataTable (Row Struct: FDACampaignChapterRow)
// data/tps_characters.json     -> DataTable (Row Struct: FDATPSCharacterRow)
// JSON'daki "Name" alanı satır adı (RowName) olur; diğer alan adları aşağıdaki
// UPROPERTY adlarıyla birebir aynıdır.
//
// NOT: Bu dosya UE 5.x için yazıldı fakat bu oturumda derlenmedi; projeye
// eklerken modül API makrosunu (DEVLETIALIYYE_API) kendi modül adınıza göre düzeltin.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DevletDataTypes.generated.h"

UENUM(BlueprintType)
enum class EDAEra : uint8
{
	Era1 UMETA(DisplayName = "I. Barut ve İmparatorluk (1700-1789)"),
	Era2 UMETA(DisplayName = "II. Nizam ve Sanayileşme (1789-1860)"),
	Era3 UMETA(DisplayName = "III. Demiryolu, Krupp ve Zırhlılar (1860-1908)"),
	Era4 UMETA(DisplayName = "IV. Cihan Harbi ve İstiklal (1908-1925)")
};

/** Görev adımının oynandığı oyun katmanı. */
UENUM(BlueprintType)
enum class EDALayer : uint8
{
	HOI4 UMETA(DisplayName = "Büyük Strateji / Harita"),
	AOE  UMETA(DisplayName = "Şehir İnşası / Taktik Savaş"),
	TPS  UMETA(DisplayName = "Şehir İçi Gezinti")
};

/** TPS modunda etkileşim tuşu = bina/rol kategorisi. */
UENUM(BlueprintType)
enum class EDAInteractKey : uint8
{
	E UMETA(DisplayName = "[E] Başmühendis / Fabrika"),
	F UMETA(DisplayName = "[F] Nezaret / Harita Masası"),
	R UMETA(DisplayName = "[R] Kışla / Asker Denetimi"),
	T UMETA(DisplayName = "[T] Gar / Lojistik"),
	G UMETA(DisplayName = "[G] Donanma")
};

/** Tek bir mekanik etki. Stat adları tools/validate.py içindeki STATS listesiyle sınırlıdır. */
USTRUCT(BlueprintType)
struct FDAEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Stat;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float Value = 0.f;
};

USTRUCT(BlueprintType)
struct FDASource
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Url;
};

USTRUCT(BlueprintType)
struct FDACampaignStep
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EDALayer Layer = EDALayer::HOI4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Text;
};

USTRUCT(BlueprintType)
struct FDAChapterEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Id;
	/** Tasarım notu olarak tetik koşulu; oyun mantığına Blueprint/C++ ile bağlanır. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Trigger;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Text;
};

USTRUCT(BlueprintType)
struct FDAChapterOutcome
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Label;
	/** false ise arayüzde "Alternatif Tarih" rozeti gösterilmelidir. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool IsHistorical = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FDAEffect> Effects;
};

USTRUCT(BlueprintType)
struct FDACampaignChapterRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) EDAEra Era = EDAEra::Era1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 StartYear = 1700;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 EndYear = 1700;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FString> Locations;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true)) FText HistoricalContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText PlayerRole;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FDACampaignStep> Steps;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FText> PrimaryObjectives;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true)) FText HistoricalOutcome;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true)) FText WhatIf;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FDAChapterEvent> Events;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FDAChapterOutcome> Outcomes;
	/** tps_characters tablosundaki satır adları. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FName> NPCs;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FDASource> Sources;
	/** Yalnız geliştirici içindir; oyuncuya gösterilmez. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FString> AccuracyNotes;
};

USTRUCT(BlueprintType)
struct FDANPCAppearance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Headwear;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Clothing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString FacialHair;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FString> Props;
	/** Anakronizm listesi: bu karakterin modelinde KULLANILMAYACAK ögeler. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FString> Forbidden;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString ArtRefNote;
};

USTRUCT(BlueprintType)
struct FDADialogueChoice
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Text;
	/** Seçimden sonra karakterin verdiği cevap. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Reply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool IsAlternate = false;
	/** "<GörevSatırAdı>.<OutcomeId>" biçiminde; boş olabilir. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Unlocks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FDAEffect> Effects;
};

USTRUCT(BlueprintType)
struct FDATPSCharacterRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText FullName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EDAEra Era = EDAEra::Era1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FName> Chapters;
	/** Karakter yalnız bu yıllar arasında (dahil) sahnede görünür. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 ActiveFrom = 1700;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 ActiveTo = 1700;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EDAInteractKey InteractKey = EDAInteractKey::F;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FText Location;
	/** false ise arayüzde "temsilî karakter" notu gösterilmelidir. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool IsHistoricalPerson = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FDANPCAppearance Appearance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Personality;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true)) FText Greeting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true)) FText Prompt;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FDADialogueChoice> Choices;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true)) FString HistoricalNote;
};
