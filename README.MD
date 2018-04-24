N64 Repro Reflashing (PAL)
----

The following list contains PAL ROM's along with the ability to change the CIC version of the ROM in order to flash & enjoy them on a reproduction cartridge with a different CIC version. The CIC version used by the ROM must match the (Ultra)CIC version used in the reproduction cartridge, otherwise the game won't boot.

As far as NTSC ROM's are concerned: some games might flicker on a PAL TV. One may fix this by changing the game to PAL mode by editing the ROM at offset 0x3E and changing the value from 0x45 (= NTSC) to 0x50 (= PAL).

- **motetIII:** if true, it's possible to use the N64 Header & Bootcode Utility "motetIII" (obs-mot3.zip) to change the used CIC version in the ROM to match with the CIC version of the reproduction cartridge (change ROM's CIC version to the one used in your repro cartridge). This method has the advantage that one won't have to reflash the ATtiny25.
- **UltraCIC swap:** if true, one may reflash the ATtiny25 on the reproduction cartridge to a different UltraCIC version in order to make the game work. 
- **Required flash memory size:** if true, this game can't be played on a reproduction cartridge with a different flash memory size (it won't boot / black screen). For instance some 16 MB games won't boot on a 64 MB repro despite using the correct CIC version.

| Title        | Tested ROM    | CIC   | motetIII | UltraCIC swap | Required flash memory size | Notes
| ------------- |:-------------:| :-----:| :-----: | :-----: | :-----: | :-----:
| Banjo-Kazooie | Banjo-Kazooie (E) (M3) [f2].z64 | CIC-NUS-7103 | Yes | - | &geq; 16 MB | Works
| Banjo-Tooie | Banjo-Tooie (E) (M4) [!].z64 | CIC-NUS-7105 | No | Yes | &geq; 32 MB |Works. Use 7105.
| Body Harvest | Body Harvest (E) (M3) [!].z64 | CIC-NUS-7101 | - | No | 16 MB | Requires a repro with no more than 16 MB flash memory. Otherwise won't boot.
| Bomberman 64 | Bomberman 64 (E) [!].z64 | CIC-NUS-7101 | - | No | 16 MB | Requires a repro with no more than 16 MB flash memory. Otherwise won't work.
| Bomberman 64 - The Second Attack! | Bomberman 64 - The Second Attack! (U) \[t1\]\[f1\] (PAL-NTSC).z64 | CIC-NUS-7101 | - | Yes | &geq; 16 MB | Works
| Castlevania | Castlevania (E) (M3) [!].z64 | CIC-NUS-7101 | Yes | - | &geq; 16 MB |Works
| Conker's Bad Fur Day | Conker's Bad Fur Day (E) [!].z64 | CIC-NUS-7105 | - | Yes | 64 MB |Works. Use 7105.
| Diddy Kong Racing | Diddy Kong Racing (E) (M3) (V1.1) \[f1] (Z64).z64 | CIC-NUS-7103 | No | No | 16 MB |Doesn't work
| Donkey Kong 64 | Donkey Kong 64 (E) \[f1] (Boot&Save).z64 | CIC-NUS-7105 | No | Yes | &geq; 32 MB | Works. Crack changes CIC to 7101.
| GoldenEye 007 | GoldenEye 007 (E) [!].z64 | CIC-NUS-7101 | - | No | 16 MB | Requires a repro with no more than 16 MB flash memory. Otherwise won't boot.
| Jet Force Gemini | Jet Force Gemini (E) (M4) [f1].z64 | CIC-NUS-7105 | - | Yes | &geq; 32 MB | Works. Use 7105.
| Kirby: The Crystal Shards | Kirby 64 - The Crystal Shards (E) [f1].z64 | CIC-NUS-7103 | Yes | - | &geq; 32 MB | Works
| LEGO Racers   | LEGO Racers (E) (M10) [!].z64 | CIC-NUS-7101 | Yes | - | &geq; 16 MB | Works
| Mace: The Dark Age | Mace - The Dark Age (E) \[!\].z64 | CIC-NUS-7101 | No | No | &geq; 16 MB | Untested.
| Mario Kart 64 | Mario Kart 64 (E) (V1.0) [!].z64 | CIC-NUS-7101 | No | No | 16 MB | Requires a repro with no more than 16 MB flash memory. Otherwise won't boot.
| Mario Party | Mario Party (E) (M3) [!].z64 | CIC-NUS-7101 | Yes | - | &geq; 32 MB | Works
| Mario Party 2 | Mario Party 2 (E) (M5) [!].z64 | CIC-NUS-7101 | No | No | &geq; 32 MB | Doesn't work
| Mario Party 3 | Mario Party 3 (E) (M4) [!].z64 | CIC-NUS-7101 | - | Yes | &geq; 32 MB | Works
| Mega Man 64 | Mega Man 64 (U) [t1]\[f1] (PAL-NTSC).z64 | CIC-NUS-7101 | - | Yes | &geq; 32 MB | Works, but lags slightly.
| Paper Mario | Paper Mario (E) (M4) [!].z64 | CIC-NUS-7103 | - | No | 64 MB | Doesn't work
| Perfect Dark | Perfect Dark (E) (M5) [!].z64 | CIC-NUS-7105 | - | Yes | &geq; 32 MB | Works. Use 7105.
| Pilotwings 64 | Pilotwings 64 (E) (M3) [!].z64 | CIC-NUS-7101 | No | No | 16 MB | Requires a repro with no more than 16 MB flash memory. Otherwise won't boot.| Rayman 2: The Great Escape | Rayman 2 - The Great Escape (E) (M5) \[f1] (NTSC).z64 | CIC-NUS-7101 | Yes | - | - | Works
| Resident Evil 2 | Resident Evil 2 (E) (M2) [!].z64 | CIC-NUS-7101 | Yes | - | 64 MB | Works
| Snowboard Kids | Snowboard Kids (E) [!].z64 | CIC-NUS-7101 | Yes | - | &geq; 16 MB | Works
| Snowboard Kids 2 | Snowboard Kids 2 (E) [!].z64 | CIC-NUS-7101 | Yes | - | &geq; 16 MB | Works
| South Park: Ralley | South Park Rally (E) [!].z64 | CIC-NUS-7101 | Yes | - | &geq; 16 MB | Works
| Star Wars: Shadows of the Empire | Star Wars - Shadows of the Empire (E) \[!\].z64 | CIC-NUS-7101 | - | - | 16 MB | Requires a repro with no more than 16 MB flash memory. Otherwise gets stuck at license text.
| Super Mario 64 | Super Mario 64 (E) (M3) [!].z64 | CIC-NUS-7101 | No | No | 16 MB | Requires a repro with no more than 16 MB flash memory. Otherwise won't boot.
| Super Smash Bros.      | Super Smash Bros. (E) (M3) [f1].z64       |   CIC-NUS-7103 | No | Yes | &geq; 32 MB | Works. The crack changes the CIC version to 7101.
| The Legend of Zelda: Majora's Mask | Legend of Zelda, The - Majora's Mask (E) (M4) (V1.0) \[f1\].z64 | CIC-NUS-7105 | ??? | ??? | &geq; 32 MB | Untested. The crack changes the CIC version to 7101.
| The Legend of Zelda: Ocarina of Time | Legend of Zelda, The - Ocarina of Time (E) (M3) (V1.1) \[!\].z64 | CIC-NUS-7105 | ??? | ??? | &geq; 32 MB | Untested.
| The Legend of Zelda: Ocarina of Time Master Quest | Legend of Zelda, The - Ocarina of Time - Master Quest (E) (GC) \[!\].z64 | CIC-NUS-7105 | ??? | ??? | &geq; 32 MB | Untested.
| Wave Race 64 | Wave Race 64 (E) (M2) \[!\].z64 | CIC-NUS-7101 | - | - | 16 MB | Requires a repro with no more than 16 MB flash memory. Otherwise gets stuck at Nintendo logo.
| Worms Armageddon | Worms - Armageddon (E) (M6) [!].z64 | CIC-NUS-7101 | Yes | - | &geq; 16 MB | Works