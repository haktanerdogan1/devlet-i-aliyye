# DEVLET-İ ALİYYE — Kampanya ve TPS Diyalog Veritabanı (Bölüm 1 ve 2)

Bu klasör, oyunun **anlatı veri katmanını** içerir: dört çağın kampanya görevleri ve şehir içi (TPS) karakter diyalogları, Unreal Engine 5 DataTable'a doğrudan aktarılabilir JSON olarak.

## İçerik

| Dosya | Ne içerir |
|---|---|
| `data/campaign_chapters.json` | 21 kampanya görevi (I. Çağ 6, II. Çağ 4, III. Çağ 5, IV. Çağ 6) |
| `data/tps_characters.json` | 26 karakter (25 gerçek şahsiyet + 1 temsilî usta), her birinde 3 seçenek |
| `Source/DevletIAliyye/DevletDataTypes.h` | JSON'la birebir eşleşen DataTable satır yapıları |
| `Source/DevletIAliyye/DevletStatsSubsystem.h` | Üç katmanın ortak stat deposu ve `ApplyEffects` |
| `tools/validate.py` | Veri bütünlüğü ve anakronizm denetimi |

## UE5'e aktarma

1. İki `.h` dosyasını projenin `Source/<Modül>/` klasörüne koyup derleyin.
2. Content Browser → Import → `campaign_chapters.json` → Row Type: `DACampaignChapterRow`.
3. Aynı şekilde `tps_characters.json` → Row Type: `DATPSCharacterRow`.
4. TPS diyalog widget'ı seçimde `UDevletStatsSubsystem::ApplyDialogueChoice` çağırır; HoI4 ve AoE arayüzleri `OnStatChanged` olayını dinler.

C++ dosyaları bu ortamda derlenmedi (burada Unreal Engine yok); ilk derlemede küçük düzeltme gerekebilir.

## Veri kuralları

- **Tarih / kurgu ayrımı:** Her `Outcome` ve her diyalog seçeneği `IsHistorical` / `IsAlternate` ile işaretlidir. Arayüz alternatifleri "Alternatif Tarih" rozetiyle göstermelidir.
- **Anakronizm kilidi:** Karakter yalnız `ActiveFrom`–`ActiveTo` yıllarında görünür; `Appearance.Forbidden` modelde kullanılmayacak ögeleri sayar (ör. 1826 sahnesinde fes yok, Plevne'de Mavzer yok).
- **Diyaloglar özgündür:** Hiçbir replik tarihî alıntı değildir; dönem üslubuna göre yazılmıştır.
- **Sayılar oyun değeridir:** Stat ve ekipman miktarları dengeleme önerisidir, tarihî nicel veri değildir.
- **Katman etiketi:** Her görev adımı `HOI4`, `AOE` veya `TPS` katmanına atanmıştır.

## Yayın öncesi doğrulanacaklar

Tarihsel çerçeve genel kabul gören bilgilere dayanır, ancak bu turda kaynak taraması yapılmadı. Emin olunmayan noktalar her görevin `AccuracyNotes` alanında tek tek yazılıdır. Özellikle:

- `Sources` içinde `Url` alanı boş olan TDV İslâm Ansiklopedisi madde adları: maddenin varlığı ve adresi teyit edilmeli.
- Kesin gün tarihleri (Aziziye baskını, Nusret'in mayın gecesi, kaptan-ı deryalık yılları, ilk buharlı gemi).
- Silah model yılları ve sipariş adetleri — bilerek sayı verilmedi.
- C21 (İmalat-ı Harbiye): atölye ve kişi adları ATASE / MKE kurum tarihleriyle doldurulmalı.
- C20, NPC23 ve NPC25: 1915 tehciri ve 1918 Bakü olayları gibi ağır konulara temas eder; tarih danışmanı incelemesi şarttır.
- Bütün portre ve kıyafet tarifleri fotoğraf/gravür arşivleriyle sanat doğrulamasından geçmeli.

## Taslaktan farklar

- Görevler kronolojik sıraya kondu (Lale Devri, Humbarahane'den önce).
- Eklenen görevler: Koca Ragıp Paşa (C04), Cezayirli Gazi Hasan Paşa / Limni (C05), Mavzer–Krupp–Goltz (C13), Hareket Ordusu (C16); Çanakkale ayrı görev oldu (C19).
- Eklenen karakterler: Müteferrika, Damat İbrahim Paşa, Cezayirli Gazi Hasan Paşa, Hobart Paşa, Nene Hatun, Goltz Paşa, Meissner Paşa, Edhem Paşa, Cevat Paşa.
- Nuri Killigil, İmalat-ı Harbiye ustası olarak değil, gerçek 1918 görevinde (Kafkas İslâm Ordusu) yer alıyor. İmalat-ı Harbiye sahnesi adı verilmeyen temsilî bir ustayla kuruldu.
- C17 Trablusgarp'ta TPS karakteri yok.

## Kapsam dışı (sonraki teslimatlar)

Bölüm 3 (Ulusal Odak Ağacı), Bölüm 4 (birim/silah/bina ansiklopedisi), Bölüm 5 (olay kartları) ve oyunun kendisi (harita, AoE inşa/savaş, TPS karakter kontrolü, 3D varlıklar).
