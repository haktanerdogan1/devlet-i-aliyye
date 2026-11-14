# Görev listesi

Denetçi bu dosyayı günceller. Biten görev `[x]` yapılır, yanına commit kısaltması yazılır.

## muhendis
- [ ] `DevletIAliyye.uproject`, `Source/DevletIAliyye.Target.cs`, `DevletIAliyyeEditor.Target.cs`, `DevletIAliyye.Build.cs` ve modül giriş dosyaları
- [ ] `DevletStatsSubsystem`'i .h/.cpp olarak ayır; tarayıcı prototipindeki bütün statları kapsa
- [ ] Üç kamera katmanı: `ADevletPlayerController` + kamera pawn'ı, 1/2/3/TAB ile yumuşak geçiş
- [ ] DataTable varlıklarını yükleyen `UDevletDataSubsystem` (görevler, karakterler)
- [ ] TPS Paşa karakteri (`ADevletPashaCharacter`) ve etkileşim bileşeni (E/F/R/T)

## dunya
- [ ] `ADevletBuilding` taban sınıfı: kademe, çağ kilidi, üretim yöntemi, modül yuvaları
- [ ] Sekiz bina ailesinin veri tablosu (`data/buildings.json`) — prototipteki BD dizisinden
- [ ] Üretim zinciri tick'i (`UDevletEconomySubsystem`)
- [ ] `ADevletDivision` ve basit cephe/dalga mantığı
- [ ] Teftiş akışı: panel düğmesi → TPS → kapıya yürüme → iki karar

## anlati
- [ ] `data/national_focus.json`: tarihsel yol + dört alternatif dal
- [ ] `data/encyclopedia.json`: birimler, silahlar, binalar (dönem kilidi ve doğrulama notlarıyla)
- [ ] `data/event_cards.json`: 10 olay kartı
- [ ] Kullanıcının 16 seferlik (C1–C16) numaralandırmasıyla `data/campaign_chapters.json` eşlemesi

## denetci
- [ ] `docs/DERLEME.md`: UE5 sürümü, projeyi açma, derleme, JSON'ları DataTable'a aktarma adımları
- [ ] Her turda dalları birleştir, bu listeyi güncelle
