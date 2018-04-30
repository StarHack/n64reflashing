/*
 * Super Mario 64 EEProm editor
 * @author https://github.com/StarHack/
 * Version: 1.0 (Apr 30, 2018)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BITMASK_BIT_1 0x1  // 00000001
#define BITMASK_BIT_2 0x2  // 00000010
#define BITMASK_BIT_3 0x4  // 00000100
#define BITMASK_BIT_4 0x8  // 00001000
#define BITMASK_BIT_5 0x10 // 00010000
#define BITMASK_BIT_6 0x20 // 00100000
#define BITMASK_BIT_7 0x40 // 01000000
#define BITMASK_BIT_8 0x80 // 10000000
#define ERROR_WRONG_USAGE -1
#define ERROR_INPUT_FILE_NOT_FOUND -2
#define ERROR_WRONG_FILE_SIZE -3

char stars[] = "X X X X X X";

void printUsage() {
  printf("Usage: sm64eep \"SUPER MARIO 64.eep\" OPTIONS\n\n");
  printf("Example options for reading/modifying the EEP file:\n");
  printf("--courses\n  (Print all course data)\n\n");
  printf("--courses 15 \"Y Y Y Y N N\" Y Y 50 \n  (Course #15: 4 stars, 100 coin bonus star, cannon open, 50 coins)\n\n");
  printf("--castle-stars\n  (Print all castle stars)\n\n");
  printf("--castle-stars 12 14\n  (Toggle castle stars #12 and #14)\n\n");
  printf("--switches\n  (Print all switch data)\n\n");
  printf("--switches 1 2\n  (Toggle switches #1 and #2)\n\n");
  printf("--doors\n  (Print all unlocked doors)\n\n");
  printf("--doors 1 2\n  (Toggle doors #1 and #2)\n\n");
  printf("--others\n  (Print all other settings)\n\n");
  printf("--others 1 2\n  (Toggle other settings #1 and #2)\n\n");
  printf("--slot A\n  (Use save slot A (default), B, C or D)\n\n");
  printf("--sound stereo\n  (Use stereo, mono, headset)\n\n");
}

char* extractLevelStars(unsigned char input) {
  if(input & BITMASK_BIT_1)
    stars[0] = 'Y';
  else
    stars[0] = 'N';
  if(input & BITMASK_BIT_2)
    stars[2] = 'Y';
  else
    stars[2] = 'N';
  if(input & BITMASK_BIT_3)
    stars[4] = 'Y';
  else
    stars[4] = 'N';
  if(input & BITMASK_BIT_4)
    stars[6] = 'Y';
  else
    stars[6] = 'N';
  if(input & BITMASK_BIT_5)
    stars[8] = 'Y';
  else
    stars[8] = 'N';
  if(input & BITMASK_BIT_6)
    stars[10] = 'Y';
  else
    stars[10] = 'N';
    
  return stars;
}

char extractFlag(unsigned char input, unsigned char flag) {
  if(input & flag)
    return 'Y';
  else
    return 'N';
}

char extractBonusStar(unsigned char input) {
  if(input & BITMASK_BIT_7)
    return 'Y';
  else
    return 'N';
}

char extractCannonOpen(unsigned char input) {
  if(input & BITMASK_BIT_8)
    return 'Y';
  else
    return 'N';
}

int main(int argc, const char *argv[]) {
  if(argc < 3) {
    printUsage();
    return ERROR_WRONG_USAGE;
  }
  
  const char* inputFile = argv[1];

  FILE* fi = fopen(inputFile, "r");
  if(!fi) {
    printUsage();
    return ERROR_INPUT_FILE_NOT_FOUND;
  }

  fseek(fi, 0L, SEEK_END);
  long inputLength = ftell(fi);
  fseek(fi, 0L, SEEK_SET);

  if(inputLength != 512) {
    printf("Input file is expected to be 512 bytes!\n");
    return ERROR_WRONG_FILE_SIZE;
  }

  unsigned char* eep = (unsigned char*)malloc(inputLength);
  fread(eep, inputLength, sizeof(char), fi);
  fclose(fi);
  
  int readCourses = 0;
  int readCastleStars = 0;
  int readSwitches = 0;
  int readDoors = 0;
  int readOthers = 0;
  int readSound = 0;

  int saveSlot = 0;

  for(int i=2; i<argc; i++) {
    if(strstr(argv[i], "--slot") != NULL && i+1 < argc) {
      char slot = *argv[++i];
      switch(slot) {
        case 'B':
          saveSlot = 1;
          break;
        case 'C':
          saveSlot = 2;
          break;
        case 'D':
          saveSlot = 3;
          break;
        default:
          saveSlot = 0;
          break;
      }
      break;
    }
  }

  for(int i=2; i<argc; i++) {
    if(strstr(argv[i], "--courses") != NULL) {
      if(i+5  < argc && strstr(argv[i+1], "--") == NULL) {
        int course = atoi(argv[++i]);
        const char* flags = argv[++i];
        char bonusStar = *argv[++i];
        char cannon = *argv[++i];
        unsigned char coins = (unsigned char)atoi(argv[++i]);

        if(course < 1 || course > 15) {
          printUsage();
          return ERROR_WRONG_USAGE;
        }

        // set level stars
        for(unsigned int i=0; i<7; i++) {
          if(*(flags + (i*2)) == 'Y')
            eep[0xC + (course - 1) + (saveSlot * 0x70)] |= (1UL << i);
          else
            eep[0xC + (course - 1) + (saveSlot * 0x70)] &= ~(1UL << i);
        }

        // set bonus star
        if(bonusStar == 'Y')
          eep[0xC + (course - 1) + (saveSlot * 0x70)] |= (1UL << 7);
        else
          eep[0xC + (course - 1) + (saveSlot * 0x70)] &= ~(1UL << 7);
        
        // levels with cannons
        if(course != 5 && course != 6 && course != 7 && course != 9 && course != 14) {
          if(cannon == 'Y')
            eep[0xC + (course - 1) + 1 + (saveSlot * 0x70)] |= (1UL << 7);
          else
            eep[0xC + (course - 1) + 1 + (saveSlot * 0x70)] &= ~(1UL << 7);
        }

        // coins
        eep[0x25 + (course - 1) + (saveSlot * 0x70)] = coins;
      }

      readCourses = 1;
    }
    if(strstr(argv[i], "--castle-stars") != NULL) {
      while(i+1  < argc && strstr(argv[i+1], "--") == NULL) {
        int castleStar = atoi(argv[++i]);
        if(castleStar >= 1 && castleStar <= 15) {
          switch(castleStar) {
            case 1:
              eep[0x1E + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 2:
              eep[0x1E + (saveSlot * 0x70)] ^= (1UL << 1);
              break;
            case 3:
              eep[0x23 + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 4:
              eep[0x20 + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 5:
              eep[0x1F + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 6:
              eep[0x21 + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 7:
              eep[0x8 + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 8:
              eep[0x8 + (saveSlot * 0x70)] ^= (1UL << 1);
              break;
            case 9:
              eep[0x8 + (saveSlot * 0x70)] ^= (1UL << 2);
              break;
            case 10:
              eep[0x8 + (saveSlot * 0x70)] ^= (1UL << 3);
              break;
            case 11:
              eep[0x8 + (saveSlot * 0x70)] ^= (1UL << 4);
              break;
            case 12:
              eep[0x1B + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 13:
              eep[0x1C + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 14:
              eep[0x1D + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 15:
              eep[0x22 + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            default:
              break;
          }
        }
      }

      readCastleStars = 1;
    }
    if(strstr(argv[i], "--switches") != NULL) {
      if(i+1  < argc && strstr(argv[i+1], "--") == NULL) {
        while(i+1  < argc && strstr(argv[i+1], "--") == NULL) {
          int switchN = atoi(argv[++i]);
          if(switchN >= 1 && switchN <= 3) {
            eep[0xB + (saveSlot * 0x70)] ^= (1UL << switchN);
          }
        }
      }

      readSwitches = 1;
    }
    if(strstr(argv[i], "--doors") != NULL) {
      if(i+1  < argc && strstr(argv[i+1], "--") == NULL) {
        while(i+1  < argc && strstr(argv[i+1], "--") == NULL) {
          int door = atoi(argv[++i]);
          if(door >= 1 && door <= 8) {
            switch(door) {
              case 1:
                eep[0xA + (saveSlot * 0x70)] ^= (1UL << 3);
                break;
              case 2:
                eep[0xA + (saveSlot * 0x70)] ^= (1UL << 5);
                break;
              case 3:
                eep[0xA + (saveSlot * 0x70)] ^= (1UL << 4);
                break;
              case 4:
                eep[0xA + (saveSlot * 0x70)] ^= (1UL << 2);
                break;
              case 5:
                eep[0xA + (saveSlot * 0x70)] ^= (1UL << 6);
                break;
              case 6:
                eep[0xA + (saveSlot * 0x70)] ^= (1UL << 7);
                break;
              case 7:
                eep[0xA + (saveSlot * 0x70)] ^= (1UL << 0);
                break;
              case 8:
                eep[0x9 + (saveSlot * 0x70)] ^= (1UL << 4);
                break;
            }
          }
        }
      }

      readDoors = 1;
    }
    if(strstr(argv[i], "--others") != NULL) {
      if(i+1  < argc && strstr(argv[i+1], "--") == NULL) {
        while(i+1  < argc && strstr(argv[i+1], "--") == NULL) {
          int other = atoi(argv[++i]);
          switch(other) {
            case 1:
              eep[0xB + (saveSlot * 0x70)] ^= (1UL << 4);
              break;
            case 2:
              eep[0xB + (saveSlot * 0x70)] ^= (1UL << 5);
              break;
            case 3:
              eep[0xB + (saveSlot * 0x70)] ^= (1UL << 6);
              break;
            case 4:
              eep[0xB + (saveSlot * 0x70)] ^= (1UL << 7);
              break;
            case 5:
              eep[0xA + (saveSlot * 0x70)] ^= (1UL << 1);
              break;
            case 6:
              eep[0x9 + (saveSlot * 0x70)] ^= (1UL << 1);
              break;
            case 7:
              eep[0x9 + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
            case 8:
              eep[0x9 + (saveSlot * 0x70)] ^= (1UL << 2);
              break;
            case 9:
              eep[0x23 + (saveSlot * 0x70)] ^= (1UL << 7);
              break;
            case 10:
              eep[0x37 + (saveSlot * 0x70)] ^= (1UL << 0);
              break;
          }
        }
      }
      readOthers = 1;
    }
    if(strstr(argv[i], "--sound") != NULL) {
      if(i+1  < argc && strstr(argv[i+1], "--") == NULL) {
        const char* sound = argv[++i];
        if(strstr(sound, "stereo") != NULL)
          eep[0x1D1] = 0x0;
        else if(strstr(sound, "mono") != NULL)
          eep[0x1D1] = 0x1;
        else if(strstr(sound, "headset") != NULL)
          eep[0x1D1] = 0x2;
      }
      readSound = 1;
    }
  }

  if(readCourses) {
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Course                   | Stars (1-6) | 100 Coin Star | Cannon open | Coins |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| 01: Bob-omb Battlefield  | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0xC + (saveSlot * 0x70)]), extractBonusStar(eep[0xC + (saveSlot * 0x70)]), extractCannonOpen(eep[0xD + (saveSlot * 0x70)]), 3, eep[0x25 + (saveSlot * 0x70)]);
    printf("| 02: Whomp's Fortress     | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0xD + (saveSlot * 0x70)]), extractBonusStar(eep[0xD + (saveSlot * 0x70)]), extractCannonOpen(eep[0xE + (saveSlot * 0x70)]), 3, eep[0x26 + (saveSlot * 0x70)]);
    printf("| 03: Jolly Roger Bay      | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0xE + (saveSlot * 0x70)]), extractBonusStar(eep[0xE + (saveSlot * 0x70)]), extractCannonOpen(eep[0xF + (saveSlot * 0x70)]), 3, eep[0x27 + (saveSlot * 0x70)]);
    printf("| 04: Cool, Cool Mountain  | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0xF + (saveSlot * 0x70)]), extractBonusStar(eep[0xF + (saveSlot * 0x70)]), extractCannonOpen(eep[0x10 + (saveSlot * 0x70)]), 3, eep[0x28 + (saveSlot * 0x70)]);
    printf("| 05: Big Boo's Haunt      | %s |       %c       |      -      |  %*d  |\n", extractLevelStars(eep[0x10 + (saveSlot * 0x70)]), extractBonusStar(eep[0x10 + (saveSlot * 0x70)]), 3, eep[0x29 + (saveSlot * 0x70)]);
    printf("| 06: Hazy Maze Cave       | %s |       %c       |      -      |  %*d  |\n", extractLevelStars(eep[0x11 + (saveSlot * 0x70)]), extractBonusStar(eep[0x11 + (saveSlot * 0x70)]), 3, eep[0x2A + (saveSlot * 0x70)]);
    printf("| 07: Lethal Lava Land     | %s |       %c       |      -      |  %*d  |\n", extractLevelStars(eep[0x12 + (saveSlot * 0x70)]), extractBonusStar(eep[0x12 + (saveSlot * 0x70)]), 3, eep[0x2B + (saveSlot * 0x70)]);
    printf("| 08: Shifting Sand Land   | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0x13 + (saveSlot * 0x70)]), extractBonusStar(eep[0x13 + (saveSlot * 0x70)]), extractCannonOpen(eep[0x14 + (saveSlot * 0x70)]), 3, eep[0x2C + (saveSlot * 0x70)]);
    printf("| 09: Dire, Dire Docks     | %s |       %c       |      -      |  %*d  |\n", extractLevelStars(eep[0x14 + (saveSlot * 0x70)]), extractBonusStar(eep[0x14 + (saveSlot * 0x70)]), 3, eep[0x2D + (saveSlot * 0x70)]);
    printf("| 10: Snowman's Land       | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0x15 + (saveSlot * 0x70)]), extractBonusStar(eep[0x15 + (saveSlot * 0x70)]), extractCannonOpen(eep[0x16 + (saveSlot * 0x70)]), 3, eep[0x2E + (saveSlot * 0x70)]);
    printf("| 11: Wet-Dry World        | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0x16 + (saveSlot * 0x70)]), extractBonusStar(eep[0x16 + (saveSlot * 0x70)]), extractCannonOpen(eep[0x17 + (saveSlot * 0x70)]), 3, eep[0x2F + (saveSlot * 0x70)]);
    printf("| 12: Tall, Tall Mountain  | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0x17 + (saveSlot * 0x70)]), extractBonusStar(eep[0x17 + (saveSlot * 0x70)]), extractCannonOpen(eep[0x18 + (saveSlot * 0x70)]), 3, eep[0x30 + (saveSlot * 0x70)]);
    printf("| 13: Tiny-Huge Island     | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0x18 + (saveSlot * 0x70)]), extractBonusStar(eep[0x18 + (saveSlot * 0x70)]), extractCannonOpen(eep[0x19 + (saveSlot * 0x70)]), 3, eep[0x31 + (saveSlot * 0x70)]);
    printf("| 14: Tick Tock Clock      | %s |       %c       |      -      |  %*d  |\n", extractLevelStars(eep[0x19 + (saveSlot * 0x70)]), extractBonusStar(eep[0x19 + (saveSlot * 0x70)]), 3, eep[0x32 + (saveSlot * 0x70)]);
    printf("| 15: Rainbow Ride         | %s |       %c       |      %c      |  %*d  |\n", extractLevelStars(eep[0x1A + (saveSlot * 0x70)]), extractBonusStar(eep[0x1A + (saveSlot * 0x70)]), extractCannonOpen(eep[0x1B + (saveSlot * 0x70)]), 3, eep[0x33 + (saveSlot * 0x70)]);
  }
  if(readCastleStars) {
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Castle Stars                                                                 |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| 1: Princess Slide [%c]                                                        |\n", extractFlag(eep[0x1E + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 2: Princess Slide Under 21 Seconds [%c]                                       |\n", extractFlag(eep[0x1E + (saveSlot * 0x70)], BITMASK_BIT_2));
    printf("| 3: Jolly Aquarium [%c]                                                        |\n", extractFlag(eep[0x23 + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 4: Red Switch Course [%c]                                                     |\n", extractFlag(eep[0x20 + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 5: Green Switch Course [%c]                                                   |\n", extractFlag(eep[0x1F + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 6: Blue Switch Course [%c]                                                    |\n", extractFlag(eep[0x21 + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 7: Toad By Hazy Maze [%c]                                                     |\n", extractFlag(eep[0x8 + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 8: Toad Across From Tall, Tall Mountain [%c]                                  |\n", extractFlag(eep[0x8 + (saveSlot * 0x70)], BITMASK_BIT_2));
    printf("| 9: Toad By Tick Tock Clock [%c]                                               |\n", extractFlag(eep[0x8 + (saveSlot * 0x70)], BITMASK_BIT_3));
    printf("| 10: Rabbit 1 [%c]                                                             |\n", extractFlag(eep[0x8 + (saveSlot * 0x70)], BITMASK_BIT_4));
    printf("| 11: Rabbit 2 [%c]                                                             |\n", extractFlag(eep[0x8 + (saveSlot * 0x70)], BITMASK_BIT_5));
    printf("| 12: Bowser 1 [%c]                                                             |\n", extractFlag(eep[0x1B + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 13: Bowser 2 [%c]                                                             |\n", extractFlag(eep[0x1C + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 14: Bowser 3 [%c]                                                             |\n", extractFlag(eep[0x1D + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 15: Rainbow Secret [%c]                                                       |\n", extractFlag(eep[0x22 + (saveSlot * 0x70)], BITMASK_BIT_1));
  }
  if(readSwitches) {
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Switches                                                                     |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| 1: Red Switch [%c]                                                            |\n", extractFlag(eep[0xB], BITMASK_BIT_2));
    printf("| 2: Green Switch [%c]                                                          |\n", extractFlag(eep[0xB], BITMASK_BIT_3));
    printf("| 3: Blue Switch [%c]                                                           |\n", extractFlag(eep[0xB], BITMASK_BIT_4));
  }
  if(readDoors) {
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Doors                                                                        |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| 1: Whomp's Fortress [%c]                                                      |\n", extractFlag(eep[0xA + (saveSlot * 0x70)], BITMASK_BIT_4));
    printf("| 2: Jolly Roger Bay [%c]                                                       |\n", extractFlag(eep[0xA + (saveSlot * 0x70)], BITMASK_BIT_6));
    printf("| 3: Cool, Cool Mountain [%c]                                                   |\n", extractFlag(eep[0xA + (saveSlot * 0x70)], BITMASK_BIT_5));
    printf("| 4: Princess Slide [%c]                                                        |\n", extractFlag(eep[0xA + (saveSlot * 0x70)], BITMASK_BIT_3));
    printf("| 5: Bowser 1 [%c]                                                              |\n", extractFlag(eep[0xA + (saveSlot * 0x70)], BITMASK_BIT_7));
    printf("| 6: Dire, Dire Docks / Bowser 2 [%c]                                           |\n", extractFlag(eep[0xA + (saveSlot * 0x70)], BITMASK_BIT_8));
    printf("| 7: Bowser 2 Water Pushed Back [%c]                                            |\n", extractFlag(eep[0xA + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("| 8: Tick Tock Clock Area [%c]                                                  |\n", extractFlag(eep[0x9 + (saveSlot * 0x70)], BITMASK_BIT_5));
  }
  if(readOthers) {
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Others                                                                       |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|  1: Have Key To Basement [%c]                                                 |\n", extractFlag(eep[0xB + (saveSlot * 0x70)], BITMASK_BIT_5));
    printf("|  2: Have Key To 2nd Floor [%c]                                                |\n", extractFlag(eep[0xB + (saveSlot * 0x70)], BITMASK_BIT_6));
    printf("|  3: Basement Unlocked [%c]                                                    |\n", extractFlag(eep[0xB + (saveSlot * 0x70)], BITMASK_BIT_7));
    printf("|  4: 2nd Floor Unlocked [%c]                                                   |\n", extractFlag(eep[0xB + (saveSlot * 0x70)], BITMASK_BIT_8));
    printf("|  5: Moat Drained [%c]                                                         |\n", extractFlag(eep[0xA + (saveSlot * 0x70)], BITMASK_BIT_2));
    printf("|  6: Mario's Cap Lost: Shifting Sand Land [%c]                                 |\n", extractFlag(eep[0x9 + (saveSlot * 0x70)], BITMASK_BIT_2));
    printf("|  7: Mario's Cap Lost: Snowman's Land [%c]                                     |\n", extractFlag(eep[0x9 + (saveSlot * 0x70)], BITMASK_BIT_1));
    printf("|  8: Mario's Cap Lost: Tall, Tall Mountain [%c]                                |\n", extractFlag(eep[0x9 + (saveSlot * 0x70)], BITMASK_BIT_3));
    printf("|  9: Cannon Open In Rainbow Secret [%c]                                        |\n", extractFlag(eep[0x23 + (saveSlot * 0x70)], BITMASK_BIT_8));
    printf("| 10: Slot Marked As NEW [%c]                                                   |\n", extractFlag(eep[0x37 + (saveSlot * 0x70)], BITMASK_BIT_1));
  }
  if(readSound) {
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Sound                                                                        |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("| Stereo [%c]                                                                  |\n", eep[0x1D1] == 0x0 ? 'Y' : 'N');
    printf("| Mono [%c]                                                                    |\n", eep[0x1D1] == 0x1 ? 'Y' : 'N');
    printf("| Headset [%c]                                                                 |\n", eep[0x1D1] == 0x2 ? 'Y' : 'N');
  }

  printf("+------------------------------------------------------------------------------+\n");


  FILE* fo = fopen(inputFile, "w");
  fwrite(eep, inputLength, 1, fo);
  fclose(fo);

  return 0;
  
}
