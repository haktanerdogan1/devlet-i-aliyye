#!/usr/bin/env python3
"""DEVLET-İ ALİYYE veri doğrulayıcı.

Kullanım:  python3 tools/validate.py
Kontroller: JSON geçerliliği, benzersiz kimlikler, izinli stat adları,
görev <-> karakter çapraz referansları, Unlocks hedefleri, karakterin
faaliyet yıllarının görev yıllarıyla kesişmesi, her karakterde 3 seçenek.
"""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent / "data"

STATS = {
    "PP", "Stability", "WarSupport", "Manpower", "Treasury", "Debt",
    "FactoryEfficiency", "Organization", "Morale", "Supply", "Output",
    "FortLevel", "NavalReadiness", "ResearchSpeed", "MilitaryCapacity",
    "Eq_Infantry", "Eq_Artillery", "Eq_Naval",
    "ForeignPressure", "ForeignDependence", "DiscoveryRisk", "SabotageRisk",
    "CivilianCasualtyRisk", "BreakoutChance", "ConflictChance",
    "Encirclement", "ConvoyDisruption", "DelayDays",
}
ERAS = {"Era1": (1700, 1789), "Era2": (1789, 1860), "Era3": (1860, 1908), "Era4": (1908, 1925)}
LAYERS = {"HOI4", "AOE", "TPS"}
KEYS = {"E", "F", "R", "T", "G"}

errors = []


def err(msg):
    errors.append(msg)


def check_effects(owner, effects):
    for e in effects:
        if e.get("Stat") not in STATS:
            err(f"{owner}: bilinmeyen stat '{e.get('Stat')}'")
        if not isinstance(e.get("Value"), (int, float)):
            err(f"{owner}: Value sayı değil")


chapters = json.loads((ROOT / "campaign_chapters.json").read_text(encoding="utf-8"))
npcs = json.loads((ROOT / "tps_characters.json").read_text(encoding="utf-8"))

ch_by_name = {}
outcome_ids = set()
for c in chapters:
    n = c["Name"]
    if n in ch_by_name:
        err(f"{n}: yinelenen görev kimliği")
    ch_by_name[n] = c
    lo, hi = ERAS[c["Era"]]
    if not (lo <= c["StartYear"] <= c["EndYear"] <= hi + 1):
        # C05 ve C14 bilinçli olarak çağ sınırını az taşabilir; uyarı olarak bildir
        print(f"UYARI {n}: yıllar {c['StartYear']}-{c['EndYear']} çağ aralığı {lo}-{hi} dışına taşıyor")
    for s in c["Steps"]:
        if s["Layer"] not in LAYERS:
            err(f"{n}/{s['Id']}: geçersiz katman {s['Layer']}")
    if {s["Layer"] for s in c["Steps"]} != LAYERS:
        print(f"UYARI {n}: üç katmanın hepsi kullanılmıyor")
    if not any(o["IsHistorical"] for o in c["Outcomes"]):
        err(f"{n}: tarihsel sonuç işaretli Outcome yok")
    for o in c["Outcomes"]:
        outcome_ids.add(f"{n}.{o['Id']}")
        check_effects(f"{n}.{o['Id']}", o["Effects"])

npc_names = set()
for p in npcs:
    n = p["Name"]
    if n in npc_names:
        err(f"{n}: yinelenen karakter kimliği")
    npc_names.add(n)
    if p["InteractKey"] not in KEYS:
        err(f"{n}: geçersiz tuş {p['InteractKey']}")
    if len(p["Choices"]) != 3:
        err(f"{n}: {len(p['Choices'])} seçenek var, 3 olmalı")
    for ch in p["Chapters"]:
        c = ch_by_name.get(ch)
        if c is None:
            err(f"{n}: bilinmeyen görev {ch}")
            continue
        if n not in c["NPCs"]:
            err(f"{n}: {ch} görevinin NPCs listesinde yok")
        if p["ActiveTo"] < c["StartYear"] or p["ActiveFrom"] > c["EndYear"]:
            err(f"{n}: faaliyet yılları {ch} ile kesişmiyor (anakronizm)")
    for ch in p["Choices"]:
        check_effects(f"{n}.{ch['Id']}", ch["Effects"])
        if ch["Unlocks"] and ch["Unlocks"] not in outcome_ids:
            err(f"{n}.{ch['Id']}: Unlocks hedefi yok: {ch['Unlocks']}")

for c in chapters:
    for ref in c["NPCs"]:
        if ref not in npc_names:
            err(f"{c['Name']}: bilinmeyen karakter {ref}")

real = sum(1 for p in npcs if p["IsHistoricalPerson"])
print(f"{len(chapters)} görev, {len(npcs)} karakter ({real} gerçek şahsiyet), "
      f"{sum(len(p['Choices']) for p in npcs)} diyalog seçeneği")
for k in sorted(KEYS):
    print(f"  [{k}] {sum(1 for p in npcs if p['InteractKey'] == k)} karakter")
if errors:
    print(f"\n{len(errors)} HATA:")
    for e in errors:
        print("  -", e)
    sys.exit(1)
print("Tüm kontroller geçti.")
