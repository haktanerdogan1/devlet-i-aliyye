# Ekip görev tanımları

## muhendis — Baş Mühendis (dal: agent/muhendis)
C++ çekirdek. `Source/DevletIAliyye/`: modül dosyaları (.Build.cs, .uproject taslağı), GameMode/PlayerController,
üç kamera katmanı arasında kesintisiz geçiş (1/2/3/TAB), ortak stat alt sistemi, DataTable yükleme, kayıt sistemi.

## dunya — Dünya ve Bina Ustası (dal: agent/dunya)
Sekiz bina ailesi aktörü, kademe (I–IV) ve çağ kilidi, üç üretim yöntemi, üç eklenti modülü, bağlı üretim zinciri
(maden → tophane → kışla → menzil/gar → tabya/tersane → karargâh → akademi), tümen aktörleri, cephe ve düşman dalgaları,
teftiş akışı. Kurallar `game/index.html` içindeki çalışan prototipten alınır.

## anlati — Anlatı ve Veri Kâtibi (dal: agent/anlati)
`data/`: Bölüm 3 ulusal odak ağacı ve alternatif tarih dalları, Bölüm 4 birim/silah/bina ansiklopedisi,
Bölüm 5 olay kartları; mevcut görev ve karakter verisinin bakımı. Her dosya için `tools/validate.py` genişletilir.

## denetci — Denetçi (dal: main)
Diğer üç dalı gözden geçirip `main`'e birleştirir (çakışmaları çözer, bariz hatalı kodu geri gönderir),
`TASKS.md` görev listesini ve `docs/DERLEME.md` derleme/editör talimatını güncel tutar,
`"hepsi"` komutlarını kapatır, her turda komuta ekranına kısa durum özeti yazar.
