sm64eep
----

This tool can read and modify Super Mario 64 save files. The editor requires a 512 byte EEProm image of the save game.

```
sm64eep $ ./sm64eep "SUPER MARIO 64.EEP" --courses --castle-stars --switches --doors --others --sound
+------------------------------------------------------------------------------+
| Course                   | Stars (1-6) | 100 Coin Star | Cannon open | Coins |
+------------------------------------------------------------------------------+
| 01: Bob-omb Battlefield  | N N N N N N |       N       |      N      |    0  |
| 02: Whomp's Fortress     | N N N N N N |       N       |      N      |    0  |
| 03: Jolly Roger Bay      | N N N N N N |       N       |      N      |    0  |
| 04: Cool, Cool Mountain  | N N N N N N |       N       |      N      |    0  |
| 05: Big Boo's Haunt      | N N N N N N |       N       |      -      |    0  |
| 06: Hazy Maze Cave       | N N N N N N |       N       |      -      |    0  |
| 07: Lethal Lava Land     | N N N N N N |       N       |      -      |    0  |
| 08: Shifting Sand Land   | N N N N N N |       N       |      N      |    0  |
| 09: Dire, Dire Docks     | N N N N N N |       N       |      -      |    0  |
| 10: Snowman's Land       | N N N N N N |       N       |      N      |    0  |
| 11: Wet-Dry World        | N N N N N N |       N       |      N      |    0  |
| 12: Tall, Tall Mountain  | N N N N N N |       N       |      N      |    0  |
| 13: Tiny-Huge Island     | N N N N N N |       N       |      N      |    0  |
| 14: Tick Tock Clock      | N N N N N N |       N       |      -      |    0  |
| 15: Rainbow Ride         | N N N N N N |       N       |      N      |    0  |
+------------------------------------------------------------------------------+
| Castle Stars                                                                 |
+------------------------------------------------------------------------------+
| 1: Princess Slide [N]                                                        |
| 2: Princess Slide Under 21 Seconds [N]                                       |
| 3: Jolly Aquarium [N]                                                        |
| 4: Red Switch Course [N]                                                     |
| 5: Green Switch Course [N]                                                   |
| 6: Blue Switch Course [N]                                                    |
| 7: Toad By Hazy Maze [N]                                                     |
| 8: Toad Across From Tall, Tall Mountain [N]                                  |
| 9: Toad By Tick Tock Clock [N]                                               |
| 10: Rabbit 1 [N]                                                             |
| 11: Rabbit 2 [N]                                                             |
| 12: Bowser 1 [N]                                                             |
| 13: Bowser 2 [N]                                                             |
| 14: Bowser 3 [N]                                                             |
| 15: Rainbow Secret [N]                                                       |
+------------------------------------------------------------------------------+
| Switches                                                                     |
+------------------------------------------------------------------------------+
| 1: Red Switch [N]                                                            |
| 2: Green Switch [N]                                                          |
| 3: Blue Switch [N]                                                           |
+------------------------------------------------------------------------------+
| Doors                                                                        |
+------------------------------------------------------------------------------+
| 1: Whomp's Fortress [N]                                                      |
| 2: Jolly Roger Bay [N]                                                       |
| 3: Cool, Cool Mountain [N]                                                   |
| 4: Princess Slide [N]                                                        |
| 5: Bowser 1 [N]                                                              |
| 6: Dire, Dire Docks / Bowser 2 [N]                                           |
| 7: Bowser 2 Water Pushed Back [N]                                            |
| 8: Tick Tock Clock Area [N]                                                  |
+------------------------------------------------------------------------------+
| Others                                                                       |
+------------------------------------------------------------------------------+
|  1: Have Key To Basement [N]                                                 |
|  2: Have Key To 2nd Floor [N]                                                |
|  3: Basement Unlocked [N]                                                    |
|  4: 2nd Floor Unlocked [N]                                                   |
|  5: Moat Drained [N]                                                         |
|  6: Mario's Cap Lost: Shifting Sand Land [N]                                 |
|  7: Mario's Cap Lost: Snowman's Land [N]                                     |
|  8: Mario's Cap Lost: Tall, Tall Mountain [N]                                |
|  9: Cannon Open In Rainbow Secret [N]                                        |
| 10: Slot Marked As NEW [N]                                                   |
+------------------------------------------------------------------------------+
| Sound                                                                        |
+------------------------------------------------------------------------------+
| Stereo [Y]                                                                  |
| Mono [N]                                                                    |
| Headset [N]                                                                 |
+------------------------------------------------------------------------------+
```

Modifying a save game:
---

**Unlock 6 stars in first level (Bob-ombs):**

`./sm64eep "SUPER MARIO 64.EEP" --courses 1 "Y Y Y Y Y Y" N N 0`

**Unlock 6 stars + 100 coin star in first level (Bob-ombs):**

`./sm64eep "SUPER MARIO 64.EEP" --courses 1 "Y Y Y Y Y Y" Y N 0`

**Unlock 6 stars + 100 coin star + cannon in first level (Bob-ombs):**

`./sm64eep "SUPER MARIO 64.EEP" --courses 1 "Y Y Y Y Y Y" Y Y 0`

**Unlock 6 stars + 100 coin star + cannon + 100 coins in first level (Bob-ombs):**

`./sm64eep "SUPER MARIO 64.EEP" --courses 1 "Y Y Y Y Y Y" Y Y 100`

**Toggle castle stars 12 and 14:**

`./sm64eep "SUPER MARIO 64.EEP" --castle-stars 12 14`

**Toggle switches 1 and 2:**

`./sm64eep "SUPER MARIO 64.EEP" --switches 1 2`

**Toggle doors 1 and 2:**

`./sm64eep "SUPER MARIO 64.EEP" --doors 1 2`

**Toggle other settings 1 and 2:**

`./sm64eep "SUPER MARIO 64.EEP" --others 1 2`

**Toggle other settings 1 and 2 with save slot B:**

`./sm64eep "SUPER MARIO 64.EEP" --others 1 2 --slot B`

**Change sound to headset:**

`./sm64eep "SUPER MARIO 64.EEP" --sound headset`

Building:
---

**macOS:**

`llvm-gcc sm64eep.c -o sm64eep`

**Linux:**

`gcc sm64eep.c -o sm64eep`

**Windows:** (use MinGW or similar)

`gcc.exe sm64eep.c -o sm64eep`

